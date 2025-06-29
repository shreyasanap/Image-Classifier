#include "backend.h"
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>

Backend::Backend(QObject *parent) : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &Backend::handleReply);
}

QString Backend::imagePath() const {
    return m_imagePath;
}

void Backend::setImagePath(const QString &path) {
    if (path != m_imagePath) {
        m_imagePath = path;
        emit imagePathChanged();
    }
}

QString Backend::result() const {
    return m_result;
}

void Backend::classifyImage() {
    qDebug() << "Classifying image:" << m_imagePath;

    QFileInfo fileInfo(m_imagePath);
    if (!fileInfo.exists()) {
        m_result = "File does not exist!";
        emit resultChanged();
        return;
    }

    QFile *file = new QFile(m_imagePath);
    if (!file->open(QIODevice::ReadOnly)) {
        m_result = "Unable to open file!";
        emit resultChanged();
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"file\"; filename=\"" + fileInfo.fileName() + "\""));
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // file will be deleted with multiPart

    multiPart->append(imagePart);

    QUrl url("http://127.0.0.1:8000/classify/");
    QNetworkRequest request(url);

    m_networkManager.post(request, multiPart);
}

void Backend::handleReply(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        m_result = "Network error: " + reply->errorString();
    } else {
        QByteArray response = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(response);
        if (json.isObject() && json.object().contains("result")) {
            m_result = json.object()["result"].toString();
        } else {
            m_result = "Invalid response from server.";
        }
    }
    emit resultChanged();
    reply->deleteLater();
}
