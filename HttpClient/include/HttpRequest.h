#ifndef __HTTP_CLIENT__HTTP_REQUEST__
#define __HTTP_CLIENT__HTTP_REQUEST__

#include "HttpContentInterface.h"
#include <QUrl>
#include <QNetworkReply>
#include "HttpUtils.h"
#include <QNetworkCookie>
#include <QNetworkProxy>

class HttpRequest
{

public:
    [[nodiscard]] QList<QNetworkReply::RawHeaderPair> headers() const;

    void setHeaders(const QList<QNetworkReply::RawHeaderPair>& headers);

    [[nodiscard]] QList<QueryPairs> queries() const;

    void setQueries(const QList<QueryPairs>& queries);

    [[nodiscard]] QList<QNetworkCookie> cookies() const;

    void setCookies(const QList<QNetworkCookie>& cookies);

    [[nodiscard]] QUrl url() const;

    void setUrl(const QUrl& url);


    [[nodiscard]] HttpContentInterface* body() const;

    void setBody(HttpContentInterface* body);

    [[nodiscard]] quint32 timeout() const;

    void setTimeout(quint32 timoutInMS);

    [[nodiscard]] QNetworkProxy* proxy() const;

    void setProxy(QNetworkProxy* networkProxy);

private:
    QList<QNetworkReply::RawHeaderPair> m_headers;
    QList<QNetworkCookie> m_cookies;
    QList<QueryPairs> m_queries;

    QUrl m_url;

    HttpContentInterface* m_body{};
    quint32 m_timeout{};
    QNetworkProxy* m_qNetworkProxy{};
};


#endif
