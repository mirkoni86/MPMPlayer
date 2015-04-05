#include "vkauth.h"
#include "ui_vkauth.h"

VKAuth::VKAuth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VKAuth)
{
    ui->setupUi(this);
    connect(ui->webView, SIGNAL(loadProgress(int)), SLOT(slotProgressShow(int)));
    ui->webView->load(QUrl("https://oauth.vk.com/authorize?client_id=4519506&scope=offline,audio&"
                                           "redirect_uri=https://oauth.vk.com/blank.html&display=page&"
                                           "v=5.26&response_type=token"));

    connect(ui->webView, SIGNAL(urlChanged(QUrl)), SLOT(slotCheckUrl(QUrl)));
    connect(this, SIGNAL(signalAuthSocces()), SLOT(slotGetAudioList()));
}

VKAuth::~VKAuth()
{
    delete ui;
}

void VKAuth::slotCheckUrl(QUrl url)
{
    url = url.toString().replace("#", "?");
    QUrlQuery urlQuary(url);
    QString token( urlQuary.queryItemValue("access_token" ) );

    if(token.isEmpty())
        return;

    m_token = token;
    qDebug() << "token: " + token;

    emit signalAuthSocces();
}

void VKAuth::slotGetAudioList()
{
    QUrl current("https://api.vk.com/method/audio.get.xml");
    QUrlQuery currentItem(current);
    currentItem.addQueryItem("v", "5.26");
    currentItem.addQueryItem("access_token", m_token);
    qDebug() << "toString: " << current.toString() + currentItem.toString();
    QByteArray answer = GET(current.toString() + "?"+ currentItem.toString());
    qDebug() << answer;
    QFile xmlFile("./tmp/vkontakteAudioList.xml");
    if( !xmlFile.open(QIODevice::ReadOnly | QIODevice::WriteOnly) )
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось открыть vkontakteAudioList.xml \n"
                                                                          "Возможно файл занят другим приложением"));
    xmlFile.write(answer);
    xmlFile.close();
    //xmlParser("vkontakteSource.xml");
}

void VKAuth::slotProgressShow(int progress)
{
    ui->progressBar->setValue(progress);
//    if(progress == 100)
//        ui->progressBar->hide();
}

QByteArray VKAuth::GET(QUrl url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(url));
    QEventLoop wait;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(60000, &wait, SLOT(quit()));
    wait.exec();
    QByteArray answer  = reply->readAll();
    reply->deleteLater();
    return answer;
}
