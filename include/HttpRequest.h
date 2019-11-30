#ifndef __HTTP_CLIENT__HTTP_REQUEST__
#define __HTTP_CLIENT__HTTP_REQUEST__

#include "HttpContentInterface.h"
#include <QUrl>
#include <QNetworkReply>
#include "HttpUtils.h"
#include <QNetworkCookie>

class HttpRequest {

public:


	QList<QNetworkReply::RawHeaderPair> headers() const;
	void setHeaders(const QList<QNetworkReply::RawHeaderPair>& headers);

	QList<QueryPairs> queries() const;
	void setQueries(const QList<QueryPairs>& queries);

	QList<QNetworkCookie> cookies() const;
	void setCookies(const QList<QNetworkCookie>& cookies);



	QUrl url() const;
	void setUrl(const QUrl& url);


	HttpContentInterface* body() const;
	void setBody(HttpContentInterface* body);

private:
	QList<QNetworkReply::RawHeaderPair> m_headers;
	QList<QNetworkCookie> m_cookies;
	QList<QueryPairs> m_queries;

	QUrl m_url;

	HttpContentInterface* m_body = nullptr;

};


#endif
