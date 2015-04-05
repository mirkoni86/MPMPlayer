#include "artistinfowiki.h"
#include "ui_artistinfowiki.h"

ArtistInfoWiki::ArtistInfoWiki(QString artist,  QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArtistInfoWiki), m_artist(artist)
{
    ui->setupUi(this);
    m_searchCriteriaRU= new QStringList;
    m_searchCriteriaEN = new QStringList;
    m_urlWikpediaRU = "http://ru.wikipedia.org/w/api.php?action=opensearch&search=";
    m_urlWikpediaEN = "http://en.wikipedia.org/w/api.php?action=opensearch&search=";
    m_netAccessManager = new QNetworkAccessManager(this);
    m_netReply = NULL;
    *m_searchCriteriaRU << "музыка" << "исполнитель" <<  "исполнительница" <<  "певец" << "певица" << "группа" << "артист" << "музыкант"
                                       << "рэпер" << "диджей" << "рокер"  << "гитарист" << "барабанщик" << "бард" << "певчий"
                                       << "хорист" << "пионист" << "вокалист" << "продюсер" << " дирижер"<< "гусляр"<< "поэт"  << "басист" << "гейша"
                                       << "джазмен" << "дорожная команда" << "капельмейстер" << "качу" <<  "майко" << "менестрель" << "музыкальный менеджер"
                                       << "мультиинструменталист" << "регент" << "тапер" << "токаор" << "хангеку" << "хормейстер" << "солист";

    *m_searchCriteriaEN << "music" << "singer" << "vocalist" << "bard" << "melodist" <<  "songster"  << "minstrel";

}

ArtistInfoWiki::~ArtistInfoWiki()
{
    delete ui;
}

void ArtistInfoWiki::get()
{
    if(m_netReply)
        m_netReply = NULL;

    qDebug() << "asasassasassa: " << m_artist;
    QNetworkRequest request(QUrl( m_urlWikpediaRU + m_artist + "&prop=info&format=xml&inprop=url" ));
    qDebug() << request.url();
    QByteArray byteArray;
    m_netReply = m_netAccessManager->post(request, byteArray);
    QEventLoop el;
    connect(m_netAccessManager, SIGNAL(finished(QNetworkReply*)), &el, SLOT(quit()));
    QTimer::singleShot(60000, &el, SLOT(quit()));
    el.exec();

   m_wikipediaData.clear();
   m_wikipediaData.append(m_netReply->readAll());

    searchArtist(); //Начинается анализ полученных данных
    m_netReply->deleteLater();
}

void ArtistInfoWiki::setArtist(const QString artist)
{
    m_artist = artist;
}

void ArtistInfoWiki::searchArtist()
{
    QXmlStreamReader xmlStreamReader(m_wikipediaData);

    while (!xmlStreamReader.atEnd())
    {
        QString text, description, url;
        if(xmlStreamReader.isStartElement())
        {
            if(xmlStreamReader.name() == "Text" )
            {
                text.clear();
                text.append(xmlStreamReader.readElementText());
                xmlStreamReader.readNext();
            }
            if(xmlStreamReader.name() == "Url")
            {
                url.clear();
                url.append(xmlStreamReader.readElementText());
                xmlStreamReader.readNext();
            }
            if(xmlStreamReader.name() == "Description")
            {
                description.clear();
                description.append(xmlStreamReader.readElementText());
                xmlStreamReader.readNext();
            }
            for(int i = 0, j = 0; i < m_searchCriteriaRU->length(); ++i)
            {
                if(text.lastIndexOf( m_searchCriteriaRU->at(i))  != -1)
                    ++j;
                if(description.lastIndexOf(m_searchCriteriaRU->at(i))  != -1 )
                    ++j;

                if(j > 1 )
                {
                    qDebug() << text << " " << description << " " << url;
                    ui->webViewArtistInfo->load(QUrl(url));
                    return;
                }
            }

        }
        xmlStreamReader.readNext();
    }
}
