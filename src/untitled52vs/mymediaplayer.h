#ifndef MYMEDIAPLAYER_H
#define MYMEDIAPLAYER_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QFileInfo>
#include <QByteArray>
#include <QVector>
#include <QMap>
#include  <QThread>
#include <QtConcurrent/QtConcurrent>
#include <cstring>
#include "bass.h"
#include "bassflac.h"
#include "basswma.h"
#include "bass_fx.h"
#include "tags.h"



class MyMediaPlayer : public QThread
{
    Q_OBJECT

public:
    explicit MyMediaPlayer();
    void run(); //Запускает поток
     enum Status{STOP = BASS_ACTIVE_STOPPED, PLAY = BASS_ACTIVE_PLAYING, PAUSE = BASS_ACTIVE_PAUSED};
     //Константы перечисления 0-7 отвечают за эффекты, 8- 17 это константы для экволайзера
     enum IndexEffect{CHORUSINDEX, FREVERBINDEX, DISTORTIONINDEX, PHASERINDEX, AUTOWAHINDEX, DAMPINDEX, PITCHINDEX, ECHO4INDEX,
                                  EQ80INDEX, EQ170INDEX, EQ310INDEX, EQ600INDEX, EQ1000INDEX, EQ3000INDEX, EQ6000INDEX, EQ10000INDEX, EQ12000INDEX, EQ14000INDEX};
     enum BufferengMedia{BUFFERENGBEGIN, BUFFERENGEND}; //Начало и конец буфферации

    QWORD getLength();
    QWORD position();
    QString getAdressFile();
    const HSTREAM* getStrean();
    QMap<QString, QString> getTags();
    static QMap<QString, QString> audioTegReader(QString fileadress);
    QVector<unsigned short> getFFTData(int size = 256);
signals:
    void signalDurationChange(QWORD pos);
    void signalGetLenght(QWORD slen);
    void signalPlayPause(int type);
    void signalBufferengMediaStream(int); //Сообщает о начале или конце буверации потокового аудио

public slots:
    void play();
    void play(const QString fileadress);
    void setFileAdress(const QString fileadress);
    void pausePlay();
    void stop();
    void setPosition(int pos);
    void setVolume(float vol);
    void setMute();
    void setEffect(BASS_BFX_CHORUS effect);
    void setEffect(BASS_BFX_FREEVERB effect);
    void setEffect(BASS_BFX_DISTORTION effect);
    void setEffect(BASS_BFX_PHASER effect);
    void setEffect(BASS_BFX_AUTOWAH effect);
    void setEffect(BASS_BFX_DAMP effect);
    void setEffect(BASS_BFX_PITCHSHIFT effect);
    void setEffect(BASS_BFX_ECHO4 effect);
    void setEffect(int index);
    void setEQ(int index, BASS_DX8_PARAMEQ paramEq);
    void removeEffect(int indexEffect);


private slots:
        void slotSendSignalProgressPlay();
        void slotPlayURL();
private:
   void errorCodeShow();
   void readTags();
    HSTREAM        _stream;
    HFX                 _hfx[50];
    QString        _fileAdress;
    char            *_fileAdressChar;
    char   *_formatTags;
    int                _FlagPausePlay;
    QWORD        _length;
    QWORD        _duration;
    BASS_CHANNELINFO _channelInfo;
    QTimer         *_timerProgressPlay;
    struct TagTrack
    {
        QString title;
        QString autor;
        QString album;
        QString genre;
        QString year;
    } _tagTrack;

    struct EqualizerDX8
    {
         BASS_DX8_PARAMEQ fq80;
         BASS_DX8_PARAMEQ fq170;
         BASS_DX8_PARAMEQ fq310;
         BASS_DX8_PARAMEQ fq600;
         BASS_DX8_PARAMEQ fq1000;
         BASS_DX8_PARAMEQ fq3000;
         BASS_DX8_PARAMEQ fq6000;
         BASS_DX8_PARAMEQ fq10000;
         BASS_DX8_PARAMEQ fq12000;
         BASS_DX8_PARAMEQ fq14000;
    } _eqDX8;
    //----------------------------------------------------
    BASS_BFX_CHORUS _chorus;
    BASS_BFX_FREEVERB _reverb;
    BASS_BFX_DISTORTION _distortion;
    BASS_BFX_PHASER _phaser;
    BASS_BFX_AUTOWAH _autowah;
    BASS_BFX_DAMP _damp;
    BASS_BFX_PITCHSHIFT _pitch;
    BASS_BFX_ECHO4 _echo4;
    static const int NIGHT_INDEX_EQ = 8;
    BASS_DX8_PARAMEQ _eq[10];
};

#endif // MYMEDIAPLAYER_H
