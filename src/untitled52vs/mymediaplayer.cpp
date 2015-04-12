#include "mymediaplayer.h"

MyMediaPlayer::MyMediaPlayer() :
    QThread()
{

    if (HIWORD(BASS_FX_GetVersion())!=BASSVERSION // check the main version
        || LOWORD(BASS_FX_GetVersion())<0x100)
            qDebug() << "Версия не соподает, текущая:  " << BASS_FX_GetVersion();

    _stream = 0;
    _duration = 0;
    _timerProgressPlay = new QTimer;
    _fileAdressChar = 0;
    _formatTags = new char[150];

    for(int i = 0; i < 50; ++i)
        _hfx[i] = 0;

}

void MyMediaPlayer::run()
{

    if(_timerProgressPlay->isActive())
        _timerProgressPlay->stop();

    if(_timerProgressPlay)
    {
        disconnect(_timerProgressPlay, SIGNAL(timeout()), this, SLOT(slotSendSignalProgressPlay()));
        delete _timerProgressPlay;
    }

    _timerProgressPlay = new QTimer;

    connect(_timerProgressPlay, SIGNAL(timeout()), SLOT(slotSendSignalProgressPlay()));
    play();
    _timerProgressPlay->start(40);
    exec();
}

QWORD MyMediaPlayer::getLength()
{
    return BASS_ChannelGetLength(_stream, BASS_POS_BYTE);
}

QWORD MyMediaPlayer::position()
{
    return  BASS_ChannelGetPosition(_stream, BASS_POS_BYTE);
}

QString MyMediaPlayer::getAdressFile()
{
    return _fileAdress;
}

const HSTREAM *MyMediaPlayer::getStrean()
{
    HSTREAM *p = &_stream;
    return p;
}

QMap<QString, QString> MyMediaPlayer::getTags()
{
    QMap<QString, QString> map;
    map["%TITL"] = _tagTrack.title;
    map["%ARTI"] = _tagTrack.autor;
    map["%ALBM"] =  _tagTrack.album;
    map["%GNRE"] = _tagTrack.genre;
    map["%YEAR" ] = _tagTrack.year;
    return map;
}

QMap<QString, QString> MyMediaPlayer::audioTegReader(QString fileadress)
{
    QMap<QString, QString> audioTeg;
    bool ok = BASS_Init (-1, 44100, 0 , NULL, NULL);
    if ( false == ok || true == ok)
    {
        HSTREAM stream;
        QByteArray barray = fileadress.toLocal8Bit().data();
        char *mfile = barray.data();
        for(int i = 0; mfile[i] != '\0'; ++i)
        {
            if(mfile[i] == '\\')
                mfile[i] = '/';
        }
        if( fileadress.mid(fileadress.size()-5) == ".flac" || fileadress.mid(fileadress.size()-5) == ".FLAC") //Creates a sample stream from an FLAC
            stream =   BASS_FLAC_StreamCreateFile(FALSE, mfile, 0, 0, 0);
        else if (fileadress.mid(fileadress.size()-4) == ".wma" || fileadress.mid(fileadress.size()-4) == ".WMA") // Creates a sample stream from an WMA
            stream = BASS_WMA_StreamCreateFile(FALSE, mfile, 0, 0, 0);
        else if(fileadress.mid(0, 7) == "http://" || fileadress.mid(0, 8) == "https://" || fileadress.mid(0, 6) == "ftp://")
        {
            audioTeg["Artist"] = "";
            audioTeg["Title"] = "";
            audioTeg["Length"] = "";
            return audioTeg;
        }
        else
            stream = BASS_StreamCreateFile(FALSE, mfile, 0, 0, 0);         //Creates a sample stream from an MP3, MP2, MP1, OGG, WAV, AIFF
        fileadress.clear();
        fileadress.append(TAGS_Read( stream, "%UTF8(%ARTI)- %UTF8(%TITL)" ));
        audioTeg["Artist"] = QString(TAGS_Read(stream, "%UTF8(%ARTI)"));
        audioTeg["Title"] = QString(TAGS_Read(stream, "%UTF8(%TITL)"));
        audioTeg["Length"] = QString::number(BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE)));
    }
    return audioTeg;
}

QVector<unsigned short> MyMediaPlayer::getFFTData(int size)
{
    const int MAXIMUM = 256;
    unsigned short buffer[MAXIMUM];
    BASS_ChannelGetData(_stream, buffer ,BASS_DATA_FFT256);
    QVector<unsigned short> vector(MAXIMUM);
    for(int i = 0; i < MAXIMUM; ++i)
        vector[i] = buffer[i];
    return vector;
}


void MyMediaPlayer::play()
{
    //_timerProgressPlay = new QTimer(this);
    qDebug() << "play func ";
        BASS_Free();
        if (BASS_Init (-1, 44100, 0 , NULL, NULL))
        {
            qDebug() << "Началася запуск ";
            QByteArray barray = _fileAdress.toLocal8Bit().data();
            char *mfile = barray.data();
            for(int i = 0; mfile[i] != '\0'; ++i)
            {
                if(mfile[i] == '\\')
                    mfile[i] = '/';
            }

            if( _fileAdress.mid(_fileAdress.size()-5) == ".flac" || _fileAdress.mid(_fileAdress.size()-5) == ".FLAC") //Creates a sample stream from an FLAC
                _stream =   BASS_FLAC_StreamCreateFile(FALSE, mfile, 0, 0, 0);
            else if (_fileAdress.mid(_fileAdress.size()-4) == ".wma" || _fileAdress.mid(_fileAdress.size()-4) == ".WMA") // Creates a sample stream from an WMA
                _stream = BASS_WMA_StreamCreateFile(FALSE, mfile, 0, 0, 0);
            else if(_fileAdress.mid(0, 7) == "http://" || _fileAdress.mid(0, 8) == "https://" || _fileAdress.mid(0, 6) == "ftp://")
            {
                slotPlayURL();
                emit signalBufferengMediaStream(BUFFERENGBEGIN); //соосбщение о начале буферация
            }
            else
            _stream = BASS_StreamCreateFile(FALSE, mfile, 0, 0, 0);         //Creates a sample stream from an MP3, MP2, MP1, OGG, WAV, AIFF

            readTags(); //Четение тегов

            for(int i = 0; i <= EQ14000INDEX; ++i) //Если есть эффект тогда установить
                if(_hfx[i])
                    setEffect(i);

            BASS_ChannelPlay(_stream,TRUE);
            emit signalBufferengMediaStream(BUFFERENGEND); //соосбщение о конце буферации


            _length = getLength(); //Присваемаем длину трека
            emit signalGetLenght(_length);
            emit signalPlayPause(PLAY);

            if(_timerProgressPlay->isActive())
                _timerProgressPlay->stop();
             connect(_timerProgressPlay, SIGNAL(timeout()), SLOT(slotSendSignalProgressPlay()));
             _timerProgressPlay->start(40);

        }

}

void MyMediaPlayer::play(const QString fileadress)
{
    //-------------------------------------------------------------------------
    //ЗДЕСЬ ВОЗМОЖНО ЕСТЬ КОСЯК !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    _fileAdress = fileadress;
    QByteArray ba =  fileadress.toLocal8Bit();
    if(_fileAdressChar != 0)
        delete [] _fileAdressChar;
    _fileAdressChar = new char[ba.size()+1];
    strcpy(_fileAdressChar, ba.data());
    //ЗДЕСЬ ВОЗМОЖНО ЕСТЬ КОСЯК !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //-------------------------------------------------------------------------
    play();
}

void MyMediaPlayer::setFileAdress(const QString fileadress)
{
    //-------------------------------------------------------------------------
    //ЗДЕСЬ ВОЗМОЖНО ЕСТЬ КОСЯК !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    _fileAdress = fileadress;
    QByteArray ba =  fileadress.toLocal8Bit();
    if(_fileAdressChar != 0)
        delete [] _fileAdressChar;
    _fileAdressChar = new char[ba.size()+1];
    strcpy(_fileAdressChar, ba.data());
    //ЗДЕСЬ ВОЗМОЖНО ЕСТЬ КОСЯК !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //-------------------------------------------------------------------------
}

void MyMediaPlayer::pausePlay()
{
    if(BASS_ChannelIsActive(_stream) == BASS_ACTIVE_PLAYING)
    {
        _duration = BASS_ChannelGetPosition(_stream, BASS_POS_BYTE);
        BASS_ChannelPause(_stream);
        emit signalPlayPause(PAUSE);
    }
    else if(BASS_ChannelIsActive(_stream) == BASS_ACTIVE_PAUSED)
    {
        BASS_ChannelPlay(_stream, TRUE);
        BASS_ChannelSetPosition(_stream, _duration, BASS_POS_BYTE);
        emit signalPlayPause(PLAY);
    }
}

void MyMediaPlayer::stop()
{
    BASS_Stop();
    emit signalPlayPause(STOP);
}

void MyMediaPlayer::setPosition(int pos)
{
    _duration = pos;
    BASS_ChannelSetPosition(_stream, _duration, BASS_POS_BYTE);
}

void MyMediaPlayer::setVolume(float vol)
{
    BASS_SetVolume(vol);
}

void MyMediaPlayer::setMute()
{

}

//Установка эфектов
void MyMediaPlayer::setEffect(BASS_BFX_CHORUS effect)
{
    qDebug() << "----------------------------------------------------------------";
    qDebug() <<  effect.fDryMix << " " << effect.fFeedback << " " << effect.fMaxSweep << " " << effect.fMinSweep << " " << effect.fRate << " " << effect.fWetMix << " " << effect.lChannel;
    if(BASS_FXGetParameters(_hfx[CHORUSINDEX],  &_chorus))
    {
        BASS_ChannelRemoveFX(_stream, _hfx[CHORUSINDEX]);
        qDebug() << " BASS_ChannelRemoveFX(_stream, _hfx[0]); ";
        errorCodeShow();
    }


    _hfx[CHORUSINDEX] =  BASS_ChannelSetFX(_stream, BASS_FX_BFX_CHORUS, 1);
    qDebug() << "BASS_ChannelSetFX(_stream, BASS_FX_BFX_CHORUS, 1); ";
    errorCodeShow();
    BASS_FXGetParameters(_hfx[CHORUSINDEX], &_chorus);
    qDebug() << "BASS_FXGetParameters(_hfx[0], _chorus)";
    errorCodeShow();
    _chorus.fDryMix = effect.fDryMix;
    _chorus.fFeedback = effect.fFeedback;
    _chorus.fMaxSweep = effect.fMaxSweep;
    _chorus.fMinSweep = effect.fMinSweep;
    _chorus.fRate = effect.fRate;
    _chorus.fWetMix = effect.fWetMix;
    _chorus.lChannel = effect.lChannel;
    BASS_FXSetParameters(_hfx[CHORUSINDEX], &_chorus);
   qDebug() << "BASS_FXSetParameters(_hfx[0], &_chorus);";
   errorCodeShow();
}

void MyMediaPlayer::setEffect(BASS_BFX_FREEVERB effect)
{
    qDebug() << "----------------------------------------------------------------";
    qDebug() << "REVERBINDEX: " << FREVERBINDEX ;
    if(BASS_FXGetParameters(_hfx[FREVERBINDEX],  &_reverb))
    {
        BASS_ChannelRemoveFX(_stream, _hfx[FREVERBINDEX]);
        qDebug() << " BASS_ChannelRemoveFX(_stream, _hfx[1]); ";
        errorCodeShow();
    }


    _hfx[FREVERBINDEX] =  BASS_ChannelSetFX(_stream, BASS_FX_BFX_FREEVERB, 1);
    qDebug() << "BASS_ChannelSetFX(_stream, BASS_BFX_FREEVERB, 1); ";
    errorCodeShow();
    BASS_FXGetParameters(_hfx[FREVERBINDEX], &_reverb);
    qDebug() << "BASS_FXGetParameters(_hfx[1], &_chorus);";
     errorCodeShow();
    _reverb.fDamp = effect.fDamp;
    _reverb.fDryMix = effect.fDryMix;
    _reverb.fRoomSize = effect.fRoomSize;
    _reverb.fWetMix = effect.fWetMix;
    _reverb.lChannel = effect.lChannel;
    _reverb.lMode = effect.lMode;
    BASS_FXSetParameters(_hfx[FREVERBINDEX], &_reverb);
   qDebug() << "BASS_FXSetParameters(_hfx[1], &_chorus);";
   errorCodeShow();
}

void MyMediaPlayer::setEffect(BASS_BFX_DISTORTION effect)
{
    qDebug() << "----------------------------------------------------------------";
    qDebug() << effect.fDrive << " " << effect.fDryMix << " " << effect.fWetMix << " " << effect.fFeedback << " " << effect.fVolume << " " << effect.lChannel;
    if(BASS_FXGetParameters(_hfx[DISTORTIONINDEX],  &_distortion))
    {
        BASS_ChannelRemoveFX(_stream, _hfx[DISTORTIONINDEX]);
        qDebug() << " BASS_ChannelRemoveFX(_stream, _hfx[2]); ";
        errorCodeShow();
    }


    _hfx[DISTORTIONINDEX] =  BASS_ChannelSetFX(_stream, BASS_FX_BFX_DISTORTION, 1);
    qDebug() << "BASS_ChannelSetFX(_stream, BASS_FX_BFX_DISTORTION , 1); ";
    errorCodeShow();
    BASS_FXGetParameters(_hfx[DISTORTIONINDEX], &_distortion);
    qDebug() << "BASS_FXGetParameters(_hfx[2], &_distortion);";
     errorCodeShow();
    _distortion.fDrive = effect.fDrive;
    _distortion.fDryMix = effect.fDryMix;
    _distortion.fFeedback = effect.fFeedback;
    _distortion.fVolume = effect.fVolume;
    _distortion.fWetMix = effect.fWetMix;
    _distortion.lChannel = effect.lChannel;

    BASS_FXSetParameters(_hfx[DISTORTIONINDEX], &_distortion);
   qDebug() << "BASS_FXSetParameters(_hfx[2], &_distortion);";
   errorCodeShow();
}

void MyMediaPlayer::setEffect(BASS_BFX_PHASER effect)
{
    qDebug() << "----------------------------------------------------------------";
    qDebug() << effect.fDryMix << " " << effect.fWetMix << " " << effect.fFeedback << " " << effect.fRate << " " << effect.fRange << " " << effect.fFreq << " " << effect.lChannel ;
    if(BASS_FXGetParameters(_hfx[PHASERINDEX],  &_phaser))
    {
        BASS_ChannelRemoveFX(_stream, _hfx[PHASERINDEX]);
        qDebug() << " BASS_ChannelRemoveFX(_stream, _hfx[PHASERINDEX]); ";
        errorCodeShow();
    }


    _hfx[PHASERINDEX] =  BASS_ChannelSetFX(_stream, BASS_FX_BFX_PHASER, 1);
    qDebug() << "BASS_ChannelSetFX(_stream, BASS_BFX_PHASER, 1); ";
    errorCodeShow();
    BASS_FXGetParameters(_hfx[PHASERINDEX], &_phaser);
    qDebug() << "BASS_FXGetParameters(_hfx[PHASERINDEX], &_phaser);";
     errorCodeShow();

     _phaser.fDryMix = effect.fDryMix;
     _phaser.fFeedback = effect.fFeedback;
     _phaser.fFreq = effect.fFreq;
     _phaser.fRange = effect.fRange;
     _phaser.fRate = effect.fRate;
     _phaser.fWetMix = effect.fWetMix;
     _phaser.lChannel = effect.lChannel;
    BASS_FXSetParameters(_hfx[PHASERINDEX], &_phaser);
   qDebug() << "BASS_FXSetParameters(_hfx[PHASERINDEX], &_phase);";
   errorCodeShow();
}

void MyMediaPlayer::setEffect(BASS_BFX_AUTOWAH effect)
{
    qDebug() << "-------------------------------------------------------------------------------";
    qDebug() << effect.fDryMix << " " << effect.fWetMix << " " << effect.fFeedback << " " << effect.fRate << " " << effect.fRange << " " << effect.lChannel;
    if(BASS_FXGetParameters(_hfx[AUTOWAHINDEX], &_autowah))
    {
        BASS_ChannelRemoveFX(_stream, _hfx[AUTOWAHINDEX]);
        qDebug() << " BASS_ChannelRemoveFX(_stream, _hfx[AUTOWAHINDEX]); ";
        errorCodeShow();
    }
    _hfx[AUTOWAHINDEX] = BASS_ChannelSetFX(_stream, BASS_FX_BFX_AUTOWAH, 1);

    qDebug() << "BASS_ChannelSetFX(_stream, BASS_BFX_PHASER, 1); ";
    errorCodeShow();
    BASS_FXGetParameters(_hfx[AUTOWAHINDEX], &_autowah);
    qDebug() << "BASS_FXGetParameters(_hfx[AUTOWAHINDEX], &_autowah);";
     errorCodeShow();

     _autowah.fDryMix = effect.fDryMix;
     _autowah.fFeedback = effect.fFeedback;
     _autowah.fFreq = effect.fFreq;
     _autowah.fRange = effect.fRange;
     _autowah.fRate = effect.fRate;
     _autowah.fWetMix = effect.fWetMix;
     _autowah.lChannel = effect.lChannel;
     BASS_FXSetParameters(_hfx[AUTOWAHINDEX], &_autowah);
     qDebug() << "BASS_FXSetParameters(_hfx[AUTOWAHINDEX], &_autowah);";
     errorCodeShow();


}

void MyMediaPlayer::setEffect(BASS_BFX_DAMP effect)
{
    qDebug() << "----------------------------------------------------------------";
    qDebug() << effect.fTarget << " " << effect.fQuiet << " " << effect.fRate << " " << effect.fGain << " " << effect.fDelay << " " << effect.lChannel ;
    if(BASS_FXGetParameters(_hfx[DAMPINDEX],  &_damp))
    {
        BASS_ChannelRemoveFX(_stream, _hfx[DAMPINDEX]);
        qDebug() << " BASS_ChannelRemoveFX(_stream, _hfx[5]); ";
        errorCodeShow();
    }

    _hfx[DAMPINDEX] =  BASS_ChannelSetFX(_stream, BASS_FX_BFX_DAMP, 1);
    qDebug() << "BASS_ChannelSetFX(_stream, BASS_FX_BFX_DAMP, 1); ";
    errorCodeShow();
    BASS_FXGetParameters(_hfx[DAMPINDEX], &_damp);
    qDebug() << "BASS_FXGetParameters(_hfx[DAMPINDEX], &_damp);";
     errorCodeShow();
     _damp.fTarget = effect.fTarget;
     _damp.fQuiet = effect.fQuiet;
     _damp.fDelay = effect.fDelay;
     _damp.fGain = effect.fGain;
     _damp.fRate = effect.fRate;
     _damp.lChannel = effect.lChannel;
    BASS_FXSetParameters(_hfx[DAMPINDEX], &_damp);
   qDebug() << "BASS_FXSetParameters(_hfx[DAMPINDEX], &_damp);";
   errorCodeShow();
}

void MyMediaPlayer::setEffect(BASS_BFX_PITCHSHIFT effect)
{
    qDebug() << "----------------------------------------------------------------";
    qDebug() << effect.fPitchShift << " " << effect.fSemitones << " " << effect.lFFTsize << " " << effect.lOsamp << " " << effect.lChannel;
    if(BASS_FXGetParameters(_hfx[PITCHINDEX],  &_pitch))
    {
        BASS_ChannelRemoveFX(_stream, _hfx[PITCHINDEX]);
        qDebug() << " BASS_ChannelRemoveFX(_stream, _hfx[PITCHINDEX]); ";
        errorCodeShow();
    }

    _hfx[PITCHINDEX] =  BASS_ChannelSetFX(_stream, BASS_FX_BFX_PITCHSHIFT, 1);
    qDebug() << "BASS_ChannelSetFX(_stream, BASS_FX_BFX_PITCHSHIFT, 1); ";
    errorCodeShow();
    BASS_FXGetParameters(_hfx[PITCHINDEX], &_pitch);
    qDebug() << "BASS_FXGetParameters(_hfx[PITCHINDEX], &_pitch);";
     errorCodeShow();
     _pitch.fPitchShift = effect.fPitchShift;
     _pitch.fSemitones = effect.fSemitones;
     _pitch.lChannel = effect.lChannel;
     _pitch.lFFTsize = effect.lFFTsize;
     _pitch.lOsamp = effect.lOsamp;
    BASS_FXSetParameters(_hfx[PITCHINDEX], &_pitch);
   qDebug() << "BASS_FXSetParameters(_hfx[PITCHINDEX], &_pitch);";
   errorCodeShow();
}

void MyMediaPlayer::setEffect(BASS_BFX_ECHO4 effect)
{
    if(BASS_FXGetParameters(_hfx[ECHO4INDEX],  &_echo4))
        BASS_ChannelRemoveFX(_stream, _hfx[ECHO4INDEX]);

    _hfx[ECHO4INDEX] =  BASS_ChannelSetFX(_stream, BASS_FX_BFX_ECHO4, 1);
    BASS_FXGetParameters(_hfx[ECHO4INDEX], &_echo4);
     _echo4.bStereo = effect.bStereo;
     _echo4.fDelay = effect.fDelay;
     _echo4.fDryMix = effect.fDryMix;
     _echo4.fFeedback = effect.fFeedback;
     _echo4.fWetMix = effect.fWetMix;
     _echo4.lChannel = effect.lChannel;
     BASS_FXSetParameters(_hfx[ECHO4INDEX], &_echo4);
}

void MyMediaPlayer::setEffect(int index)
{
    if(index < CHORUSINDEX || index > EQ14000INDEX)
        return;

    switch (index) {
    case CHORUSINDEX:
        setEffect(_chorus);
        break;
    case FREVERBINDEX:
        setEffect(_reverb);
        break;
    case DISTORTIONINDEX:
        setEffect(_distortion);
        break;
    case PHASERINDEX:
        setEffect(_phaser);
        break;
    case AUTOWAHINDEX:
        setEffect(_autowah);
        break;
    case DAMPINDEX:
        setEffect(_damp);
        break;
    case PITCHINDEX:
        setEffect(_pitch);
        break;
    case ECHO4INDEX:
        setEffect(_echo4);
        break;
    default:
        setEQ(index, _eq[index - NIGHT_INDEX_EQ]);
    }
}

void MyMediaPlayer::setEQ(int index, BASS_DX8_PARAMEQ paramEq)
{

    if(BASS_FXGetParameters(_hfx[index], &_eq[index - NIGHT_INDEX_EQ]))
    {
        BASS_ChannelRemoveFX(_stream, _hfx[index]);
    }

    _hfx[index] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 1);
    BASS_FXGetParameters(_hfx[index], &_eq[index - NIGHT_INDEX_EQ]);
    _eq[index - NIGHT_INDEX_EQ].fBandwidth = paramEq.fBandwidth;
    _eq[index - NIGHT_INDEX_EQ].fCenter = paramEq.fCenter;
    _eq[index - NIGHT_INDEX_EQ].fGain = paramEq.fGain;

    BASS_FXSetParameters(_hfx[index], &_eq[index -  NIGHT_INDEX_EQ]);

}

void MyMediaPlayer::removeEffect(int indexEffect)
{
    switch (indexEffect) {
    case CHORUSINDEX:
        if(BASS_FXGetParameters(_hfx[CHORUSINDEX],  &_chorus))
        {
            BASS_ChannelRemoveFX(_stream, _hfx[CHORUSINDEX]);
            _hfx[CHORUSINDEX] = 0;
        }
        break;
    case FREVERBINDEX:
        if(BASS_FXGetParameters(_hfx[FREVERBINDEX],  &_reverb))
        {
            BASS_ChannelRemoveFX(_stream, _hfx[FREVERBINDEX]);
            _hfx[FREVERBINDEX] = 0;
        }
        break;
    case DISTORTIONINDEX:
        if(BASS_FXGetParameters(_hfx[DISTORTIONINDEX],  &_distortion))
        {
            BASS_ChannelRemoveFX(_stream, _hfx[DISTORTIONINDEX]);
            _hfx[DISTORTIONINDEX] = 0;
        }
        break;
    case PHASERINDEX:
        if(BASS_FXGetParameters(_hfx[PHASERINDEX],  &_phaser))
        {
            BASS_ChannelRemoveFX(_stream, _hfx[PHASERINDEX]);
            _hfx[PHASERINDEX] = 0;
        }
        break;
    case AUTOWAHINDEX:
        if(BASS_FXGetParameters(_hfx[AUTOWAHINDEX], &_autowah))
        {
            BASS_ChannelRemoveFX(_stream, _hfx[AUTOWAHINDEX]);
            _hfx[AUTOWAHINDEX] = 0;
        }
        break;
    case DAMPINDEX:
        if(BASS_FXGetParameters(_hfx[DAMPINDEX], &_damp))
        {
            BASS_ChannelRemoveFX(_stream, _hfx[DAMPINDEX]);
            _hfx[DAMPINDEX] = 0;
        }
        break;
    case PITCHINDEX:
        if(BASS_FXGetParameters(_hfx[PITCHINDEX], &_pitch))
        {
            BASS_ChannelRemoveFX(_stream, _hfx[PITCHINDEX]);
            _hfx[PITCHINDEX] = 0;
        }
        break;
    case ECHO4INDEX:
        if(BASS_FXGetParameters(_hfx[ECHO4INDEX], &_echo4))
        {
            BASS_ChannelRemoveFX(_stream, _hfx[ECHO4INDEX]);
            _hfx[ECHO4INDEX] = 0;
        break;
        }
    }
}

void MyMediaPlayer::slotSendSignalProgressPlay()
{
//    if(_duration >= _length)
//        _timerProgressPlay->stop();

    _duration = BASS_ChannelGetPosition(_stream, BASS_POS_BYTE);
    getFFTData();
    emit signalDurationChange(_duration);
}

void MyMediaPlayer::slotPlayURL()
{
    _stream = BASS_StreamCreateURL(_fileAdressChar, 0, 0, NULL, 0);
}

void MyMediaPlayer::errorCodeShow()
{
    int errorCode = BASS_ErrorGetCode();
    switch (errorCode) {
    case 0:
        qDebug() << "MyMediaPlayer ERROR: " << "NO ERROR";
        break;
    case BASS_ERROR_HANDLE:
        qDebug() << "MyMediaPlayer ERROR: BASS_ERROR_HANDLE";
        break;
    case BASS_ERROR_ILLPARAM:
        qDebug() << "MyMediaPlayer ERROR: BASS_ERROR_ILLPARAM";
        break;
    case BASS_ERROR_FORMAT:
        qDebug() << "MyMediaPlayer BASS_ERROR_FORMAT";
    case BASS_ERROR_MEM:
        qDebug() << "MyMediaPlayer BASS_ERROR_MEM";
        break;
    default:
        qDebug() << "MyMediaPlayer ERROR: UNKNOWN code: " << errorCode;

        };


}

void MyMediaPlayer::readTags()
{
    _tagTrack.album.clear();
    _tagTrack.autor.clear();
    _tagTrack.genre.clear();
    _tagTrack.title.clear();
    _tagTrack.year.clear();
    _tagTrack.album.append(TAGS_Read( _stream, "%UTF8(%ALBM)"));
    _tagTrack.title.append(TAGS_Read( _stream, "%UTF8(%TITL)" ));
    _tagTrack.autor.append(TAGS_Read( _stream, "%UTF8(%ARTI)" ));
    _tagTrack.genre.append(TAGS_Read( _stream, "%UTF8(%GNRE)" ));
    _tagTrack.year.append(TAGS_Read( _stream, "%UTF8(%YEAR)" ));

}
