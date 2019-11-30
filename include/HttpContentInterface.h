#ifndef __HTTP_CLIENT__HTTP_CONTENT_INTERFACE__
#define __HTTP_CLIENT__HTTP_CONTENT_INTERFACE__

#include<QByteArray>

class HttpContentInterface
{
public:
	virtual QByteArray content() = 0;
	virtual QByteArray contentType() = 0;

	virtual ~HttpContentInterface() = default;

private:
	QByteArray m_content;
	QByteArray m_contentType;
};


#endif
