 #include "tracklistformat.h"
#include "ui_tracklistformat.h"
#include <QMediaService>
#include <QUrl>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QSize>
TrackListFormat::TrackListFormat(QString str, QSize sz, QWidget *parent) :
    QWidget(parent), ui(new Ui::TrackListFormat), fileAdress(&str)
{
    ui->setupUi(this);
    setBaseSize(sz.width(), sz.height());
    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setMedia(QUrl::fromLocalFile(*fileAdress));
    ui->labelAuthor->setText( QVariant( mediaPlayer->metaData("Author") ).toString() );
    ui->labelTitle->setText( QVariant( mediaPlayer->metaData("Title") ).toString() );
    if(ui->labelTitle->text() == "")
         ui->labelTitle->setText(*fileAdress);
    long long int lSec = QVariant( mediaPlayer->metaData("Duration") ).toInt();
    int iMin = lSec / 1000 % 60;
    int iSec = lSec / 1000 - iMin * 60;
    QString sSec = (iSec < 10) ? QString::number(0) + QString::number(iSec) : QString::number(iSec);
     ui->labelDuration->setText(QString::number(iMin) + ":" + sSec);
}
TrackListFormat::TrackListFormat()
{

}

TrackListFormat::~TrackListFormat()
{
    delete ui;
}
