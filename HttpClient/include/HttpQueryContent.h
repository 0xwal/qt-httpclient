#ifndef __HTTP_CLIENT__HTTP_QUERY_CONTENT__
#define __HTTP_CLIENT__HTTP_QUERY_CONTENT__
#include "HttpContentInterface.h"
#include <QUrlQuery>

class HttpQueryContent : public HttpContentInterface
{
public:
	explicit HttpQueryContent(const QUrlQuery& query);
	
	QByteArray content() override;
	QByteArray contentType() override;

private:
	QUrlQuery m_urlQuery;
};

#endif
