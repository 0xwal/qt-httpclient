#include "HttpRequest.h"

QList<QNetworkReply::RawHeaderPair> HttpRequest::headers() const
{
    return m_headers;
}

void HttpRequest::setHeaders(const QList<QNetworkReply::RawHeaderPair> &headers)
{
    m_headers = headers;
}


QList<QueryPairs> HttpRequest::queries() const
{
    return m_queries;
}

void HttpRequest::setQueries(const QList<QueryPairs> &queries)
{
    m_queries = queries;
}


QUrl HttpRequest::url() const
{
    return m_url;
}

void HttpRequest::setUrl(const QUrl &url)
{
    m_url = url;
}

HttpContentInterface *HttpRequest::body() const
{
    return m_body;
}

void HttpRequest::setBody(HttpContentInterface *body)
{
    m_body = body;
}

QList<QNetworkCookie> HttpRequest::cookies() const
{
    return m_cookies;
}

void HttpRequest::setCookies(const QList<QNetworkCookie> &cookies)
{
    m_cookies = cookies;
}

quint32 HttpRequest::timeout() const
{
    return m_timeout;
}

void HttpRequest::setTimeout(quint32 timoutInMS)
{
    m_timeout = timoutInMS;
}
