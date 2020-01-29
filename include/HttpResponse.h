#ifndef   __HTTP_CLIENT__HTTP_RESPONSE
#define   __HTTP_CLIENT__HTTP_RESPONSE

#include <QNetworkReply>
#include <QNetworkCookie>
#include <QJsonDocument>
#include <QRandomGenerator>

class HttpResponse
{
public:
	explicit HttpResponse(QNetworkReply* reply);
	~HttpResponse();

	QByteArray statusText() const;
	qint16 statusCode() const;

	QVariant redirection() const;

	QList<QNetworkCookie> cookies() const;
	QNetworkCookie cookie(const QByteArray& name) const;

	QList<QNetworkReply::RawHeaderPair> headers() const;
	QByteArray header(const QByteArray& name) const;

	QJsonDocument json() const;

	QByteArray body() const;

	bool hasError() const;
	QNetworkReply::NetworkError networkError() const;
	QString errorMessage() const;


private:
	QNetworkReply* m_reply{};
    mutable QByteArray m_body;
};



#endif
