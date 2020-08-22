#ifndef __HTTP_CLIENT__HTTP_JSON_CONTENT__
#define __HTTP_CLIENT__HTTP_JSON_CONTENT__
#include "HttpContentInterface.h"
#include <QJsonDocument>

class HttpJsonContent final: public HttpContentInterface
{
public:
	explicit HttpJsonContent(QJsonDocument  json);
	QByteArray content() override;
	QByteArray contentType() override;

private:
	QJsonDocument m_jsonDoc;
};

#endif
