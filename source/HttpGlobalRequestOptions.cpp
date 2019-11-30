#include "HttpGlobalRequestOptions.h"


QList<QueryPairs> HttpGlobalRequestOptions::queries() const
{
    return m_queries;
}

void HttpGlobalRequestOptions::setQueries(const QList<QueryPairs> &queries)
{
    m_queries = queries;
}

QList<QNetworkCookie> HttpGlobalRequestOptions::cookies() const
{
    return m_cookies;
}

void HttpGlobalRequestOptions::setCookies(const QList<QNetworkCookie> &cookies)
{
    m_cookies = cookies;
}

QList<QNetworkReply::RawHeaderPair> HttpGlobalRequestOptions::headers() const
{
    return m_headers;
}

void HttpGlobalRequestOptions::setHeaders(const QList<QNetworkReply::RawHeaderPair> &headers)
{
    m_headers = headers;
}
