#ifndef __HTTP_CLIENT__
#define __HTTP_CLIENT__

#include <QObject>
#include <QEventLoop>

#include <QUrlQuery>

#include <memory>

#include "HttpGlobalRequestOptions.h"
#include "HttpResponse.h"
#include "HttpUtils.h"
#include "HttpRequest.h"


#define HTTPCLIENT_DEFAULT_USER_AGENT "HttpClient "

class HttpClient final : public QObject
{
    Q_OBJECT
#define RESPONSE_RETURN_TYPE std::unique_ptr<HttpResponse>
public:
    explicit HttpClient(QObject *parent = nullptr);
    ~HttpClient() override;

    static HttpClient *global();
    static QString version();

    void setGlobalHeaders(const QList<QNetworkReply::RawHeaderPair> &headers) const;
    void setGlobalCookies(const QList<QNetworkCookie> &cookies) const;
    void setGlobalQueries(const QList<QueryPairs> &queries) const;
    void setGlobalTimeout(quint32 timeoutInMS);

    RESPONSE_RETURN_TYPE get(const QString& url, HttpRequest& request);

	RESPONSE_RETURN_TYPE post(const QString& url, HttpRequest& request);

	RESPONSE_RETURN_TYPE put(const QString& url, HttpRequest& request);

	RESPONSE_RETURN_TYPE del(const QString& url, HttpRequest& request);

	RESPONSE_RETURN_TYPE patch(const QString& url, HttpRequest& request);

signals:
	void beforeRequest(const HttpRequest& request);
	void afterRequest(HttpResponse* reply);

private:
    QNetworkAccessManager m_accessManager;
    QNetworkRequest m_request;

    QUrl m_url;
	QUrlQuery m_urlQuery;
    HttpGlobalRequestOptions* m_globalRequestOptions{};
	QStringList m_cookiesList;

    void setRequestHeaders(const QList<QNetworkReply::RawHeaderPair> &headers);
    void setRequestCookies(const QList<QNetworkCookie> &cookies);
    void setRequestQueries(const QList<QueryPairs> &queries);

	QByteArray setUpContent(HttpContentInterface* content);

    void applyGlobalRequestOptions();

    RESPONSE_RETURN_TYPE setUp(const QByteArray& method, const HttpRequest& request);
};






#endif
