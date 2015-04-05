#ifndef MYID3TEGEXTRACTOR_H
#define MYID3TEGEXTRACTOR_H
#include <QObject>
#include <QFile>
#include <QByteArray>
#include <QBitArray>
#include <QDebug>
#include <QMessageBox>
class MyId3TegExtractor : public QObject
{
    Q_OBJECT
public:
     MyId3TegExtractor(const QString str, QObject *parent = 0);

     struct
     {
         bool okID3v1; //Если тег ID3v1 есть в файле тогда истина
         QString title;
         QString autor;
         QString album;
         QString year;
         QString comment;
         QString flagNumberTrack;
         QString numberTrack;
         QString genre;
     } ID3v1;

     struct
     {
         QString title;
         QString autor;
         QString album;
         QString year;
         QString comment;
         QString flagNumberTrack;
         QString numberTrack;
         QString genre;
     } ID3v2;
private:
     void searchTypeID3();
     void extractorID3v1();
     void extractorID3v1p();
     void extractorID3v2();
     QString genreList(int nIndex);
     QString toUnicod(int latter);

     QFile *audioFiile;
     QByteArray *byteArrAudioFile;
};

#endif // MYID3TEGEXTRACTOR_H
