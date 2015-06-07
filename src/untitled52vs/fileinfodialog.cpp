#include "fileinfodialog.h"
#include "ui_fileinfodialog.h"


FileInfoDialog::FileInfoDialog(QString adress, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileInfoDialog)
{
    ui->setupUi(this);

    fileInfo = new QFileInfo(adress);
    setWindowTitle(tr("Информация о ") + fileInfo->fileName());

    ui->labelDir->setText(fileInfo->absoluteFilePath());
   ui->labelDateSet->setText(QString::number(fileInfo->created().date().day()) +
                                           "." + QString::number(fileInfo->created().date().month()) +
                                           "." + QString::number(fileInfo->created().date().year()));
   ui->labelNameFile->setText(fileInfo->fileName());

   if(fileInfo->size() < 1024)
       ui->labelSizeFile->setText(QString::number(fileInfo->size()) + tr(" Байт"));
   else if(fileInfo->size() >= 1024 && fileInfo->size() < 1024 * 1024)
       ui->labelSizeFile->setText(QString::number((float) fileInfo->size() / 1024) + tr("  КБайт"));
   else if(fileInfo->size() >= 1024*1024 && fileInfo->size() < 1024*1024*1024)
       ui->labelSizeFile->setText(QString::number( ( float) ( fileInfo->size() / 1024 / 1024 ) ) + tr(" МБайт"));
  else if(fileInfo->size() >= 1024*1024*1024 && fileInfo->size() < 1024*1024*1024*1024)
       ui->labelSizeFile->setText(QString::number((float) fileInfo->size() /1024 /1024 / 1024) + tr(" ГБайт"));
   else ui->labelSizeFile->setText(QString::number((float) fileInfo->size() /1024 /1024 / 1024 / 1024) + tr(" ТБайт"));

   mediaPlayer = new QMediaPlayer(this);
   mediaPlayer->setMedia(QUrl::fromLocalFile(adress));
   mediaPlayer->setMuted(true);
   mediaPlayer->play();
   connect(mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(metaDataExtractor(QMediaPlayer::MediaStatus)));
}

FileInfoDialog::~FileInfoDialog()
{
    delete ui;
}

void FileInfoDialog::metaDataExtractor(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::BufferedMedia)
    {
        mediaPlayer->stop();
        ui->lineEditAlbum->setText(mediaPlayer->metaData("AlbumTitle").toString());
        ui->lineEditArtist->setText(mediaPlayer->metaData("Author").toString());
        ui->lineEditGenre->setText(mediaPlayer->metaData("Genre").toString());
        ui->lineEditTrackName->setText(mediaPlayer->metaData("Title").toString());
        ui->lineEditYear->setText(mediaPlayer->metaData("Year").toString());
        ui->lineEditCopyright->setText(mediaPlayer->metaData("Copyright").toString());
        ui->lineEditPublisher->setText(mediaPlayer->metaData("Publisher").toString());
        ui->labelCodec->setText(mediaPlayer->metaData("AudioCodec").toString());
       ui->labelBirate->setText(mediaPlayer->metaData("AudioBitRate").toString() + tr(" bit"));
       ui->labelChannelCount->setText(mediaPlayer->metaData("ChannelCount").toString());
       ui->labelSampleRate->setText(mediaPlayer->metaData("SampleRate").toString() + " Hz");
    }
    else return;
}
