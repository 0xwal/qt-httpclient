#include "HttpClient.h"

HttpClient::HttpClient(QObject *parent) :
        QObject(parent),
        m_reply(Q_NULLPTR),
        m_globalRequestOptions(new HttpGlobalRequestOptions)
{
}

HttpClient::~HttpClient()
{
    delete m_globalRequestOptions;
}

HttpClient *HttpClient::global()
{
    static auto *httpClient = new HttpClient;
    return httpClient;
}


void HttpClient::setGlobalHeaders(const QList<QNetworkReply::RawHeaderPair> &headers) const
{
    m_globalRequestOptions->setHeaders(headers);
}

void HttpClient::setGlobalCookies(const QList<QNetworkCookie> &cookies) const
{
    m_globalRequestOptions->setCookies(cookies);
}

void HttpClient::setGlobalQueries(const QList<QueryPairs> &queries) const
{
    m_globalRequestOptions->setQueries(queries);
}


RESPONSE_RETURN_TYPE HttpClient::get(const QString &url, HttpRequest &request)
{
    request.setUrl(QUrl(url));
    return setUp("GET", request);
}

RESPONSE_RETURN_TYPE HttpClient::post(const QString &url, HttpRequest &request)
{
    request.setUrl(QUrl(url));
    return setUp("POST", request);
}

std::unique_ptr<HttpResponse> HttpClient::put(const QString &url, HttpRequest &request)
{
    request.setUrl(QUrl(url));
    return setUp("PUT", request);
}

std::unique_ptr<HttpResponse> HttpClient::del(const QString &url, HttpRequest &request)
{
    request.setUrl(QUrl(url));
    return setUp("DELETE", request);
}

std::unique_ptr<HttpResponse> HttpClient::patch(const QString &url, HttpRequest &request)
{
    request.setUrl(QUrl(url));
    return setUp("PATCH", request);
}

void HttpClient::setRequestHeaders(const QList<QNetworkReply::RawHeaderPair> &headers)
{
    for (auto &header: headers) {
        m_request.setRawHeader(header.first, header.second);
    }
}

void HttpClient::setRequestCookies(const QList<QNetworkCookie> &cookies)
{
    QStringList &cookiesList = m_cookiesList;
    for (auto &cookie : cookies) {
        cookiesList.append(QString("%1=%2").arg(QString(cookie.name()), QString(cookie.value())));
    }
}

void HttpClient::setRequestQueries(const QList<QueryPairs> &queries)
{
    for (auto &query : queries) {
        m_urlQuery.addQueryItem(query.first, query.second);
    }
}

void HttpClient::applyGlobalRequestOptions()
{
    const auto headers = m_globalRequestOptions->headers();
    if (!headers.isEmpty())
        setRequestHeaders(headers);

    const auto cookies = m_globalRequestOptions->cookies();
    if (!cookies.isEmpty())
        setRequestCookies(cookies);

    const auto queries = m_globalRequestOptions->queries();
    if (!queries.isEmpty())
        setRequestQueries(queries);
}

QByteArray HttpClient::setUpContent(HttpContentInterface *content)
{
    if (content == Q_NULLPTR)
        return Q_NULLPTR;

    if (content->content().isNull())
        return Q_NULLPTR;

    if (!content->contentType().isNull())
        m_request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, content->contentType());

    return content->content();

}

RESPONSE_RETURN_TYPE HttpClient::setUp(const QByteArray &method, const HttpRequest &request)
{
    m_request = QNetworkRequest();
    m_url = QUrl();
    m_urlQuery = QUrlQuery();

    m_url = request.url();
    m_urlQuery.setQuery(m_url.query());

    applyGlobalRequestOptions();
    const auto headers = request.headers();
    setRequestHeaders(headers);

    const auto queries = request.queries();
    setRequestQueries(queries);

    const auto cookies = request.cookies();
    setRequestCookies(cookies);

    m_url.setQuery(m_urlQuery);


    m_request.setUrl(m_url);
    m_request.setRawHeader("Cookie", m_cookiesList.join("; ").toUtf8());

    QEventLoop loop;

    connect(&m_accessManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    const QByteArray content = setUpContent(request.body());
    emit beforeRequest(request);
    QNetworkReply *reply = m_accessManager.sendCustomRequest(m_request, method, content);
    loop.exec();

    RESPONSE_RETURN_TYPE response(std::make_unique<HttpResponse>(reply));
    emit afterRequest();
    return response;

}

QString HttpClient::version()
{
#ifdef HTTPCLIENT_VERSION
    return QString(HTTPCLIENT_VERSION);
#else
    return QString("");
#endif
}
