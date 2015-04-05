#ifndef VKAUTH_H
#define VKAUTH_H

#include <QWidget>
#include <QDialog>
#include <QtWebKitWidgets/QWebView>
#include <QUrlQuery>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QEventLoop>
#include <QTimer>
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>

namespace Ui {
class VKAuth;
}

class VKAuth : public QDialog
{
    Q_OBJECT

public:
    explicit VKAuth(QWidget *parent = 0);
    ~VKAuth();
    QByteArray GET(QUrl url);
public slots:
    void slotCheckUrl(QUrl url);
    void slotGetAudioList();
    void slotProgressShow(int progress);
signals:
    void signalAuthSocces();
private:
    Ui::VKAuth *ui;
    QString m_token;


};

#endif // VKAUTH_H
