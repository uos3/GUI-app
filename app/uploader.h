#ifndef UPLOADER_H
#define UPLOADER_H

#include <vector>
#include <tuple>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>


class Uploader : public QObject {
	Q_OBJECT
public:
	// Constructors
	Uploader(QString target = "http://localhost:8080");

	// Methods
	void upload(std::vector<std::tuple<QString, QString>> body);
	void upload();

	// Getters / Setters
	QString getTarget();
	void setTarget (QString target);

public slots:
	void replyFinished (QNetworkReply* reply);

private:
	// Members
	QNetworkAccessManager* manager;
	QString target;
};

#endif // UPLOADER_H