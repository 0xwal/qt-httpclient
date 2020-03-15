#include "HttpJsonContent.h"


HttpJsonContent::HttpJsonContent(const QJsonDocument& json) : m_jsonDoc(json)
{}

QByteArray HttpJsonContent::content()
{
	return m_jsonDoc.toJson(QJsonDocument::JsonFormat::Compact);
}

QByteArray HttpJsonContent::contentType()
{
	return "application/json";
}
