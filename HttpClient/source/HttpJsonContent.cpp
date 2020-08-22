#include "HttpJsonContent.h"

#include <utility>


HttpJsonContent::HttpJsonContent(QJsonDocument  json) : m_jsonDoc(std::move(json))
{}

QByteArray HttpJsonContent::content()
{
	return m_jsonDoc.toJson(QJsonDocument::JsonFormat::Compact);
}

QByteArray HttpJsonContent::contentType()
{
	return "application/json";
}
