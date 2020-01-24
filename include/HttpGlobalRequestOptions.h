#ifndef GLOBAL_HTTP_REQUEST_OPTIONS
#define GLOBAL_HTTP_REQUEST_OPTIONS

#include <QList>
#include <QNetworkCookie>
#include <QNetworkReply>
#include "HttpUtils.h"

class HttpGlobalRequestOptions
{
public:

	QList<QueryPairs> queries() const;
	void setQueries(const QList<QueryPairs>& queries);

	QList<QNetworkCookie> cookies() const;
	void setCookies(const QList<QNetworkCookie>& cookies);

	QList<QNetworkReply::RawHeaderPair> headers() const;
	void setHeaders(const QList<QNetworkReply::RawHeaderPair>& headers);

    quint32 timeout() const;
    void setTimeout(quint32 timeoutInMS);

private:
	QList<QNetworkReply::RawHeaderPair> m_headers;
	QList<QNetworkCookie> m_cookies;
	QList<QueryPairs> m_queries;
	quint32 m_timeout;
};


#endif
