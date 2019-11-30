#include "HttpQueryContent.h"

HttpQueryContent::HttpQueryContent(const QUrlQuery& query) : m_urlQuery(query) {}

QByteArray HttpQueryContent::content()
{
	return m_urlQuery.toString(QUrl::ComponentFormattingOption::FullyEncoded).toUtf8();
}


QByteArray HttpQueryContent::contentType()
{
	return "application/x-www-form-urlencoded";
}