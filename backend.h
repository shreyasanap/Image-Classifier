#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHttpMultiPart>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    QString imagePath() const;
    void setImagePath(const QString &path);
    QString result() const;

    Q_INVOKABLE void classifyImage();

signals:
    void imagePathChanged();
    void resultChanged();

private slots:
    void handleReply(QNetworkReply *reply);

private:
    QString m_imagePath;
    QString m_result;
    QNetworkAccessManager m_networkManager;
};

#endif // BACKEND_H
