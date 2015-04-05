#ifndef ARTISTINFOWIKI_H
#define ARTISTINFOWIKI_H

#include <QMainWindow>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QTimer>
#include <QEventLoop>
#include <QtXml/QtXml>
#include <QStack>
#include <QDebug>


namespace Ui {
class ArtistInfoWiki;
}

class ArtistInfoWiki : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArtistInfoWiki(QString artist, QWidget *parent = 0);
    ~ArtistInfoWiki();
public slots:
    void get();
    void setArtist(const QString artist);
private slots:
    void searchArtist();
private:
    Ui::ArtistInfoWiki *ui;
    QString m_artist;
    QString m_urlWikpediaRU;
    QString m_urlWikpediaEN;
    QStringList *m_searchCriteriaRU;
    QStringList *m_searchCriteriaEN;
    QNetworkAccessManager *m_netAccessManager;
    QNetworkReply *m_netReply;
    QByteArray m_wikipediaData;
};

#endif // ARTISTINFOWIKI_H
