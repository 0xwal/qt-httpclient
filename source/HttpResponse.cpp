#include "HttpResponse.h"



HttpResponse::HttpResponse(QNetworkReply* reply) : m_reply(reply)
{

}

QByteArray HttpResponse::statusText() const
{
	return m_reply->attribute(QNetworkRequest::Attribute::HttpReasonPhraseAttribute).toByteArray();
}

qint16 HttpResponse::statusCode() const
{
	return static_cast<qint16>(m_reply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt());
}

QVariant HttpResponse::redirection() const
{
	return m_reply->attribute(QNetworkRequest::Attribute::RedirectionTargetAttribute);
}

QList<QNetworkCookie> HttpResponse::cookies() const
{
	return m_reply->header(QNetworkRequest::KnownHeaders::SetCookieHeader).value<QList<QNetworkCookie>>();
}

QNetworkCookie HttpResponse::cookie(const QByteArray& name) const
{
	QList<QNetworkCookie> allCookies = this->cookies();
	for (const QNetworkCookie& cookie : allCookies) {
		if (cookie.name() == name)
			return cookie;
	}
	return QNetworkCookie(Q_NULLPTR, Q_NULLPTR);
}

QList<QNetworkReply::RawHeaderPair> HttpResponse::headers() const
{
	return m_reply->rawHeaderPairs();
}

QByteArray HttpResponse::header(const QByteArray& name) const
{
	return m_reply->rawHeader(name);
}

QJsonDocument HttpResponse::json() const
{
	return QJsonDocument::fromJson(m_reply->readAll());
}

QByteArray HttpResponse::body() const
{
	return m_reply->readAll();
}

bool HttpResponse::hasError() const
{
	return m_reply->error() != QNetworkReply::NetworkError::NoError;
}

QNetworkReply::NetworkError HttpResponse::networkError() const
{
	return m_reply->error();
}

QString HttpResponse::errorMessage() const
{
	return m_reply->errorString();
}