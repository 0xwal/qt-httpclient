#include <QtCore/QTimer>
#include "HttpClient.h"

HttpClient::HttpClient(QObject* parent) :
        QObject(parent),
        m_globalRequestOptions(new HttpGlobalRequestOptions)
{
}

HttpClient::~HttpClient()
{
    delete m_globalRequestOptions;
}

HttpClient* HttpClient::global()
{
    static auto* httpClient = new HttpClient;
    return httpClient;
}

void HttpClient::setGlobalHeaders(const QList<QNetworkReply::RawHeaderPair>& headers) const
{
    m_globalRequestOptions->setHeaders(headers);
}

void HttpClient::setGlobalCookies(const QList<QNetworkCookie>& cookies) const
{
    m_globalRequestOptions->setCookies(cookies);
}

void HttpClient::setGlobalQueries(const QList<QueryPairs>& queries) const
{
    m_globalRequestOptions->setQueries(queries);
}

void HttpClient::setGlobalTimeout(quint32 timeoutInMS)
{
    m_globalRequestOptions->setTimeout(timeoutInMS);
}

RESPONSE_RETURN_TYPE HttpClient::get(QString url, HttpRequest* request)
{
    return setUp("GET", url, request);
}

RESPONSE_RETURN_TYPE HttpClient::post(const QString& url, HttpRequest* request)
{
    return setUp("POST", url, request);
}

std::unique_ptr<HttpResponse> HttpClient::put(const QString& url, HttpRequest* request)
{
    return setUp("PUT", url, request);
}

std::unique_ptr<HttpResponse> HttpClient::del(const QString& url, HttpRequest* request)
{
    return setUp("DELETE", url, request);
}

std::unique_ptr<HttpResponse> HttpClient::patch(const QString& url, HttpRequest* request)
{
    return setUp("PATCH", url, request);
}

void HttpClient::setRequestHeaders(const QList<QNetworkReply::RawHeaderPair>& headers)
{
    for (auto& header: headers)
    {
        m_qNetworkRequest.setRawHeader(header.first, header.second);
    }
}

void HttpClient::setRequestCookies(const QList<QNetworkCookie>& cookies)
{
    QStringList& cookiesList = m_cookiesList;
    for (auto& cookie : cookies)
    {
        cookiesList.append(QString("%1=%2").arg(QString(cookie.name()), QString(cookie.value())));
    }
}

void HttpClient::setRequestQueries(const QList<QueryPairs>& queries)
{
    for (auto& query : queries)
    {
        m_qUrlQuery.addQueryItem(query.first, query.second);
    }
}

void HttpClient::applyGlobalRequestOptions()
{
    const auto headers = m_globalRequestOptions->headers();
    if (!headers.isEmpty())
    {
        setRequestHeaders(headers);
    }

    const auto cookies = m_globalRequestOptions->cookies();
    if (!cookies.isEmpty())
    {
        setRequestCookies(cookies);
    }

    const auto queries = m_globalRequestOptions->queries();
    if (!queries.isEmpty())
    {
        setRequestQueries(queries);
    }
}

QByteArray HttpClient::setUpContent(HttpContentInterface* content)
{
    if (content == Q_NULLPTR)
    {
        return Q_NULLPTR;
    }

    if (content->content().isNull())
    {
        return Q_NULLPTR;
    }

    if (!content->contentType().isNull())
    {
        m_qNetworkRequest.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, content->contentType());
    }

    return content->content();

}

RESPONSE_RETURN_TYPE HttpClient::setUp(const QByteArray& method, const QString& url, HttpRequest* request)
{
    bool isRequestWasNull = request == nullptr;
    if (request == nullptr)
    {
        request = new HttpRequest;
    }

    request->setUrl(QUrl(url));
    m_qNetworkRequest = QNetworkRequest();
    m_qUrl = QUrl();
    m_qUrlQuery = QUrlQuery();

    m_qUrl = request->url();
    m_qUrlQuery.setQuery(m_qUrl.query());

    applyGlobalRequestOptions();
    const auto headers = request->headers();
    setRequestHeaders(headers);

    const auto queries = request->queries();
    setRequestQueries(queries);

    const auto cookies = request->cookies();
    setRequestCookies(cookies);

    m_qUrl.setQuery(m_qUrlQuery);

    if (request->proxy() != nullptr)
    {
        QNetworkProxy* proxy = request->proxy();
        proxy->setType(QNetworkProxy::ProxyType::HttpProxy);
        m_qNetworkAccessManager.setProxy(*proxy);
    }

    m_qNetworkRequest.setUrl(m_qUrl);
    m_qNetworkRequest.setRawHeader("Cookie", m_cookiesList.join("; ").toUtf8());
    m_qNetworkRequest.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, HTTPCLIENT_DEFAULT_USER_AGENT + version());

    QEventLoop loop;
    connect(&m_qNetworkAccessManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);


    const QByteArray content = setUpContent(request->body());
    emit beforeRequest(request);


    QNetworkReply* reply = m_qNetworkAccessManager.sendCustomRequest(m_qNetworkRequest, method, content);

    QTimer timer;
    quint32 timeout;
    if ((timeout = request->timeout()) > 0 || (timeout = m_globalRequestOptions->timeout()) > 0)
    {
#ifdef QT_DEBUG
        qDebug() << "HTTPCLIENT: " "Setting up the timeout" << timeout;
#endif
        connect(&timer, &QTimer::timeout, [&] {
            reply->abort();
            reply->close();
            loop.quit();
        });
        timer.start(timeout);
    }

    loop.exec(QEventLoop::ProcessEventsFlag::ExcludeUserInputEvents);

    RESPONSE_RETURN_TYPE response(std::make_unique<HttpResponse>(reply));
    emit afterRequest(response.get());

    if (isRequestWasNull)
    {
        delete request;
    }
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
