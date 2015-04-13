#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(0);
   setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    m_streamMediaPlayer    = new DWORD;
    m_bassMediaPlayer       = new MyMediaPlayer();
    m_fileAdress                = new QString;
    m_fileDirectors             = new QString;
    m_fileListAdress           = new QStringList;
    //-----------------------------------------------------------------------------------------
    m_trackLM                   = new TrackListMeneger(this);
    m_playlistMeneger       = new PlaylistMeneger(ui->tabWidget, this);
    //-----------------------------------------------------------------------------------------
    m_ContextMenuTabWidget = new ContextMenuTabWidget(ui->tabWidget->tabBar() ,this);
    m_ContextMenuOpenFile = new ContextMenuOpenFile(ui->toolButtonOpenList);
    m_audioEffectWindow = new AudioEffectWindow(this);
    //FFT Визуализатор
    m_fftvisualWidget = new FFTVisualWidget(this);
    ui->verticalLayoutFFTVisual->addWidget(m_fftvisualWidget);

    m_bufferengWindow = new BufferengWindow(this); //Окно отоброжающее ход буфферации

    m_trackLM->setPointTabWidget(ui->tabWidget);
    ui->horizontalSliderProgressPlay;


    m_qiPositionPlay           = 0;
    m_BASSPositionPlay      = 0;
    m_bFlagPausePlay         = 0;
    m_iIndexFileListPosition = 0;
    m_iReplayType              = 0;


    ui->pushButonAlbumImage->setIcon(QIcon(":/new/prefix1/image/CD-icon.png"));
    ui->pushButonAlbumImage->setIconSize(ui->pushButonAlbumImage->size());

    //-----------------------------------------------------------------------------------------------------------------
    //Управление контекстным меню для ui->tabwidget
    ui->tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tabWidget, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotSetTabItemContextMenu(QPoint)));
    connect(ui->tabWidget->tabBar(), SIGNAL(tabBarClicked(int)), m_ContextMenuTabWidget, SLOT(slotSetIndexClickedTabBar(int)));
    //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    //connect(ui->tabWidget->tabBar(), SIGNAL(tabCloseRequested(int)), m_trackLM, SLOT(slotRemoveTabWidgetElement(int)));
    connect(ui->tabWidget->tabBar(), SIGNAL(tabCloseRequested(int)), m_playlistMeneger, SLOT(slotRemovePlaylist(int)));
    //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    //connect(ui->tabWidget->tabBar(), SIGNAL(tabMoved(int,int)), m_trackLM, SLOT(slotSwapPlaylist(int,int)));
    //В НОВОЙ РЕАЛАИЗАЦИИ СВЭП НЕ НУЖЕН
    //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    connect(m_ContextMenuTabWidget, SIGNAL(signalRemoveTabElement(int)), m_trackLM, SLOT(slotRemoveTabWidgetElement(int)));
    connect(m_ContextMenuTabWidget, SIGNAL(signalRemoveTabElement(int)), m_playlistMeneger, SLOT(slotRemovePlaylist(int)));
    //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    connect(m_ContextMenuTabWidget, SIGNAL(signalRenameTabElement(int)), m_trackLM, SLOT(slotRenameTabWidgetElement(int)));
    connect(m_ContextMenuTabWidget, SIGNAL(signalRenameTabElement(int)), m_playlistMeneger, SLOT(slotRenamePlaylist(int)));
    connect(m_ContextMenuTabWidget, SIGNAL(signalAddTabElement()), SLOT(slotOpenPlaylist()));

    //-----------------------------------------------------------------------------------------------------------------
    //Упровление сигналами и слотами для меню окрытия файлов

    connect(m_ContextMenuOpenFile, SIGNAL(signalOpenFile()), SLOT(slotOpenPlaylist()));
    connect(m_ContextMenuOpenFile, SIGNAL(signalOpenFolder()), SLOT(slotOpenFolderFileList()));
    connect(m_ContextMenuOpenFile, SIGNAL(signalOpenVkontakte()), SLOT(slotOpenVKPlaylist()));


    //------------------------------------------------------------------------------------------------------------------
    //Соединение сигналов и слотов

    connect(ui->toolButtonOpenList, SIGNAL(clicked()), SLOT(slotShowMenuOpenFile()));
    connect(ui->pushButtonPlay, SIGNAL(clicked()), SLOT(slotPlayFile()));
    connect(ui->pushButtonPause, SIGNAL(clicked()), SLOT(slotStopFile()));
    connect(ui->pushButtonPreviousFile, SIGNAL(clicked()), SLOT(slotPreviousFile()));
    connect(ui->pushButtonNextFile, SIGNAL(clicked()), SLOT(slotNextFile()));
    connect(ui->pushButtonMutedSet, SIGNAL(clicked()), SLOT(slotSetMute()));
    connect(ui->pushButtonReplayType, SIGNAL(clicked()), SLOT(slotSetReplayType()));
    connect(ui->pushButtonABReparation, SIGNAL(clicked()), SLOT(slotReparationAB()));
    connect(ui->pushButtonWindowClose,SIGNAL(clicked()), SLOT(close()));
    connect(&m_mediaPlayer, SIGNAL(positionChanged(qint64)) , SLOT(slotReplayReparationAB(qint64)));
    connect(&m_mediaPlayer, SIGNAL(positionChanged(qint64)), SLOT(slotReplayPlayList(qint64)));
    connect(&m_mediaPlayer, SIGNAL(positionChanged(qint64)),  SLOT(slotPositionProgress(qint64)));
   connect(&m_mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(metaTegInfo()));
   connect(&m_mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(slotSetColorElemetListWidget(QMediaPlayer::MediaStatus)));
   connect(&m_mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(slotInvalidPlayngFile(QMediaPlayer::MediaStatus)));
    connect(ui->horizontalSliderProgressPlay, SIGNAL(sliderMoved(int)), SLOT(slotPositionProgresMousePress(int)));
    ui->horizontalSliderVolume->setMaximum(100);
    connect(ui->horizontalSliderVolume, SIGNAL(valueChanged(int)), SLOT(slotVolumeSound(int)));
    //connect(ui->listWidgetPlaylystView, SIGNAL(activated(QModelIndex)), SLOT(slotPlayFileList(QModelIndex)));
    //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), m_trackLM, SLOT(setChenTabPos(int)));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), m_playlistMeneger, SLOT(slotSetCurrentPlaylist(int)));
    //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    connect(m_trackLM, SIGNAL(signalItemPosition(QModelIndex,QStringList)), SLOT(slotPlayFileList(QModelIndex,QStringList)));
    connect(m_playlistMeneger, SIGNAL(signalClickItemPlaylistWidget(QModelIndex,QStringList)),
                                                    SLOT(slotPlayFileList(QModelIndex,QStringList)));
    connect(ui->pushButtonShowWindowAudioEffect, SIGNAL(clicked()), SLOT(slotShowWindowAudioEffect()));

    //MyMediaPlayer BASS
    connect(m_bassMediaPlayer, SIGNAL(signalGetLenght(QWORD)), SLOT(slotSetProgressPlayMax(QWORD)));
    connect(m_bassMediaPlayer, SIGNAL(signalDurationChange(QWORD)), SLOT(slotPositionProgress(QWORD)));
    connect(m_bassMediaPlayer, SIGNAL(signalPlayPause(int)), SLOT(slotChangeStatusPlayer(int)));
    connect(m_bassMediaPlayer, SIGNAL(signalPlayPause(int)), SLOT(slotShowWindowBuffereng(int)));

    //AudioEffectWindow
    connect(m_audioEffectWindow, SIGNAL(signalRemoveEffect(int)), m_bassMediaPlayer, SLOT(removeEffect(int)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeSlider(BASS_BFX_CHORUS)), m_bassMediaPlayer, SLOT(setEffect(BASS_BFX_CHORUS)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeSlider(BASS_BFX_FREEVERB)), m_bassMediaPlayer, SLOT(setEffect(BASS_BFX_FREEVERB)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeSlider(BASS_BFX_DISTORTION)), m_bassMediaPlayer, SLOT(setEffect(BASS_BFX_DISTORTION)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeSlider(BASS_BFX_PHASER)), m_bassMediaPlayer, SLOT(setEffect(BASS_BFX_PHASER)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeSlider(BASS_BFX_AUTOWAH)), m_bassMediaPlayer, SLOT(setEffect(BASS_BFX_AUTOWAH)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeSlider(BASS_BFX_DAMP)), m_bassMediaPlayer, SLOT(setEffect(BASS_BFX_DAMP)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeSlider(BASS_BFX_PITCHSHIFT)), m_bassMediaPlayer, SLOT(setEffect(BASS_BFX_PITCHSHIFT)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeSlider(BASS_BFX_ECHO4)), m_bassMediaPlayer, SLOT(setEffect(BASS_BFX_ECHO4)));
    connect(m_audioEffectWindow, SIGNAL(signalChangeEq(int, BASS_DX8_PARAMEQ)), m_bassMediaPlayer, SLOT(setEQ(int,BASS_DX8_PARAMEQ)));


    slotSetStartSettings();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOpenFile() //СЛОТ
{
    QString path = "";
    m_fileAdress->clear();
    m_fileAdress->append(QFileDialog::getOpenFileName(this, tr("Open File"), path, tr("MP3 files (*.mp3);;All files (*.*)")));
    m_fileDirectors->clear();
    m_fileDirectors->append(path);
    m_bFlagPausePlay = 0;
    qDebug () << *m_fileAdress << " " << *m_fileDirectors << endl;

}
void MainWindow::slotOpenPlaylist() //СЛОТ
{
    /*          --СЛОТ ПРЕДНАЗНАЧЕН ДЛЯ ОТКРЫТИЯ ПЛЕЙЛИСТА--
        Если не выбан не один файл тогда не выпонять не чего и выходим
        из слота.
        В функцию addList объекта m_trackLM передается лист адресов файлов и
        название плейлиста.
        На ui->tabWidget устанавливается QListWidget возращенный из
        m_trackLM->retList() с названием плейлиста.
        Объект m_fileListAdress очищается и в него передается лист адрессов из m_trackLM.
        */
//    QSettings settings("conf/player.ini", QSettings::IniFormat);
//    QString path = "";
//    m_fileListAdress->clear();
//    m_fileListAdress->append(QFileDialog::getOpenFileNames(this, tr("Open File"), path, tr("Audio Files (*.mp3 *.flac *.wav *.wma *.amr *.m4a *.m4r);;All files (*.*)")));
//    if(m_fileListAdress->size() == 0)
//        return;
//    m_fileDirectors->clear();
//    m_fileDirectors->append(path);
//    m_trackLM->addList(*m_fileListAdress, tr("Playlist ") + QString::number(m_trackLM->realSize()));
//    ui->tabWidget->addTab(m_trackLM->retList(), tr("Playlist ") + QString::number(m_trackLM->realSize()));
//    //m_windowPlaylist->addPlaylist(m_trackLM->retList(), tr("Playlist ") + QString::number(m_trackLM->realSize()));
//    m_fileListAdress->clear();
//    m_fileListAdress->append(m_trackLM->retStringList());

//    m_bFlagPausePlay = 0;

    QStringList tempList;
    tempList.append(QFileDialog::getOpenFileNames(this, tr("Open File"), "D:\\Музыка", tr("Audio Files (*.mp3 *.flac *.wav *.wma *.amr *.m4a *.m4r);;All files (*.*)")));
    if( ! tempList.size() )
        return;

    DialogRenamePlaylist dialogName(ui->tabWidget, 0, 0);
    dialogName.exec();
    QString namePlaylist = dialogName.newName();

    m_playlistMeneger->addPlaylist(tempList, namePlaylist);
    ui->tabWidget->addTab(m_playlistMeneger->getPlaylistWidget(namePlaylist), namePlaylist);
    m_fileListAdress->clear();
    m_fileListAdress->append(*m_playlistMeneger->getPlaylist(namePlaylist));
}

void MainWindow::slotOpenFolderFileList()
{
//    QSettings settings("conf/player.ini", QSettings::IniFormat);
//    QString path = "";
//    m_fileListAdress->clear();
//    m_fileListAdress->append(QFileDialog::getExistingDirectory(\this, tr("Open File"), path, tr("Audio Files (*.mp3 *.flac *.wav *.wma *.amr *.m4a *.m4r);;All files (*.*)")));
//    if(m_fileListAdress->size() == 0)
//        return;
//    m_fileDirectors->clear();
//    m_fileDirectors->append(path);
//    m_trackLM->addList(*m_fileListAdress, tr("Playlist ") + QString::number(m_trackLM->realSize()));
//    ui->tabWidget->addTab(m_trackLM->retList(), tr("Playlist ") + QString::number(m_trackLM->realSize()));
//    m_fileListAdress->clear();
    //    m_fileListAdress->append(m_trackLM->retStringList());
}

void MainWindow::slotOpenVKPlaylist()
{
    VKAuth *vk = new VKAuth(this);
    vk->exec();

    QFile* xmlFile = new QFile("./tmp/vkontakteAudioList.xml");
    if(!xmlFile->open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось открыть vkontakteAudioList.xml \n"
                                                                          "Возможно файл занят другим приложением"));
        return;
    }
    m_fileListAdress->clear();

    QXmlStreamReader xmlReader(xmlFile);
    while (!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name() == "url" )
                  m_fileListAdress->append( xmlReader.readElementText() );
        }
        xmlReader.readNext();
    }
    xmlFile->close();

    if(m_fileListAdress->size() == 0)
        return;

    m_trackLM->addList(*m_fileListAdress, tr("Playlist ") + QString::number(m_trackLM->realSize()));
    ui->tabWidget->addTab(m_trackLM->retList(), tr("Playlist ") + QString::number(m_trackLM->realSize()));
    m_fileListAdress->clear();
    m_fileListAdress->append(m_trackLM->retStringList());

    QFile *fdeb = new QFile("./tmp/1.txt");
    fdeb->open(QIODevice::WriteOnly | QIODevice::ReadOnly);
    for(int i = 0; i < m_fileListAdress->size(); ++i)
        fdeb->write(m_fileListAdress->at(i).toUtf8() + '\n');
    fdeb->close();

}
void MainWindow::slotPlayFile() //СЛОТ
{
    m_bassMediaPlayer->pausePlay();
}

void MainWindow::slotPlayFileBASS(QString file)
{
//    if(m_bassMediaPlayer->isRunning())
//        m_bassMediaPlayer->quit(); //Если поток запущен, то завершить

//    m_bassMediaPlayer->setFileAdress(file);
//    m_bassMediaPlayer->start(); //запуск потока

    m_bassMediaPlayer->setFileAdress(file);
    m_bassMediaPlayer->play();
}
void MainWindow::slotPlayFileList(QModelIndex x) //СЛОТ
{
//    QString a = m_fileListAdress->at(x.row());
//    m_iIndexFileListPosition = x.row();
//    m_fileAdress->clear();
//    m_fileAdress->append(a);
//    m_mediaPlayer.setMedia(QUrl::fromLocalFile(a));
//    m_mediaPlayer.play();
//     m_bFlagPausePlay = 1;
//    ui->pushButtonPlay->setText("||");
}

void MainWindow::slotPlayFileList(QModelIndex x, QStringList str) //СЛОТ
{
//    if(m_bassMediaPlayer->isRunning()) //если поток существует, то выйте из потокак
//        m_bassMediaPlayer->quit();

//    m_bassMediaPlayer->setFileAdress(str.at(x.row()));
//    m_iIndexFileListPosition = x.row();
//    m_bassMediaPlayer->start(); //Запуск потока

        m_bassMediaPlayer->setFileAdress(str.at(x.row()));
        m_iIndexFileListPosition = x.row();
        m_bassMediaPlayer->play();
}

void MainWindow::slotPlayFileListBASS(QModelIndex x)
{

}

void MainWindow::slotPlayFileListBASS(QModelIndex x, QStringList str)
{
//    if (!BASS_Init (-1, 44100, 0 , NULL, NULL))
//    {
//        BASS_ChannelStop(*m_streamMediaPlayer);
//        QByteArray barray = QString(str.at(x.row())).toLocal8Bit().data();
//        char *mfile = barray.data();
//        for(int i = 0; mfile[i] != '\0'; i++)
//        {
//            if(mfile[i] == '\\')
//                mfile[i] = '/';
//            qDebug() << "char to int " << i << ": " << (int)  mfile[i] << " " << mfile[i];
//        }
//        qDebug() << mfile << endl;
//        //qDebug() << "size() : " << a.size() << " count() : " << a.count();
//        DWORD stream; /* дескриптор потока */
//        *m_streamMediaPlayer = BASS_StreamCreateFile(FALSE, mfile, 0, 0, 0);
//        BASS_ChannelPlay(*m_streamMediaPlayer,TRUE);

//        qDebug() << "lengh: " << BASS_ChannelBytes2Seconds(*m_streamMediaPlayer, BASS_ChannelGetLength(*m_streamMediaPlayer, BASS_POS_BYTE));
//        qDebug() << "bassPosition: " << BASS_ChannelBytes2Seconds(*m_streamMediaPlayer, BASS_ChannelGetPosition(*m_streamMediaPlayer,  BASS_POS_BYTE));
//        ui->horizontalSliderProgressPlay->setMaximum(BASS_ChannelGetLength(*m_streamMediaPlayer, BASS_POS_BYTE));
//        QTimer *timer = new QTimer(this);
//        connect(timer, SIGNAL(timeout()), SLOT(slotPositionProgress()));
//        timer->start(500);

//    }

}

void MainWindow::slotStopFile() //SLOT
{
   m_qiPositionPlay =  0;
   m_bFlagPausePlay = 0;;
   m_mediaPlayer.stop();
   m_bassMediaPlayer->stop();
}
void MainWindow::slotPositionProgress(qint64 x) //СЛОТ
{
    ui->horizontalSliderProgressPlay->setMaximum(m_mediaPlayer.duration());
    ui->horizontalSliderProgressPlay->setValue(x);

   int m = x / 1000 / 60;
   int s = (x / 1000) % 60;
    ui->labelTimeCome->clear();
    if(s > 9)
        ui->labelTimeCome->setText(QString::number(m) + ":" + QString::number(s));
    else
        ui->labelTimeCome->setText(QString::number(m) + ":0" + QString::number(s));
}

void MainWindow::slotPositionProgress(QWORD x)
{
    ui->horizontalSliderProgressPlay->setValue( x );
    slotReplayPlayList(x);
     double come = BASS_ChannelBytes2Seconds(*m_bassMediaPlayer->getStrean(), x);
    int m = come / 60;
    int s = come - (60 * m);
    ui->labelTimeCome->clear();
    if(s > 9)
        ui->labelTimeCome->setText(QString::number(m) + ":" + QString::number(s));
    else
        ui->labelTimeCome->setText(QString::number(m) + ":0" + QString::number(s));

    double cons = BASS_ChannelBytes2Seconds(*m_bassMediaPlayer->getStrean(), m_bassMediaPlayer->getLength());
    int consm = cons / 60;
    int conss = cons - (60 * consm);
    if(conss > 9)
        ui->labelTimeConst->setText(QString::number(consm) + ":" + QString::number(conss));
    else
        ui->labelTimeConst->setText(QString::number(consm) + ":0" + QString::number(conss));

    metaTegInfo();

    m_fftvisualWidget->setData(m_bassMediaPlayer->getFFTData());


}
void MainWindow::slotPositionProgresMousePress(int x) //СЛОТ
{
    //m_mediaPlayer.setPosition(x);
    m_bassMediaPlayer->setPosition(x);
}
void MainWindow::slotVolumeSound(int x) //СЛОТ
{
    ui->labelSoundVolume->clear();
    ui->labelSoundVolume->setText(QString::number(x) + "%");
    m_mediaPlayer.setVolume(x);
    m_bassMediaPlayer->setVolume((float) x / 100);
    QSettings settings("conf/Player.ini", QSettings::IniFormat);
    settings.setValue("SOUND/volume", x);
}

void MainWindow::metaTegInfo() //СЛОТ
{
        ui->labelMusicName->setText("<b>" + m_bassMediaPlayer->getTags().value("%TITL") + "</b>");
        ui->labelMusicAutor->setText("<b>" + m_bassMediaPlayer->getTags().value("%ARTI") + "</b>");
        ui->labelMusicAlbum->setText(m_bassMediaPlayer->getTags().value("%ALBM"));
        ui->labelMusicGenre->setText(m_bassMediaPlayer->getTags().value("%GNRE"));
        ui->labelMusicYear->setText(m_bassMediaPlayer->getTags().value("%YEAR") );
}

void MainWindow::slotReparationAB() //СЛОТ
{
   if(m_reparationFragment.status() == 0)
   {
        m_reparationFragment.setPlay(1);
        m_reparationFragment.setA(m_mediaPlayer.position());
        ui->pushButtonABReparation->setText("A");
   }
   else if(m_reparationFragment.status() == 1)
   {
       m_reparationFragment.setPlay(2);
       m_reparationFragment.setB(m_mediaPlayer.position());
       m_mediaPlayer.setPosition(m_reparationFragment.retA());
       ui->pushButtonABReparation->setText("B");
   }
   else if(m_reparationFragment.status() == 2)
   {
       m_reparationFragment.setPlay(0);
       ui->pushButtonABReparation->setText("AB");
   }
}

void MainWindow::slotReplayReparationAB(qint64 b) //СЛОТ
{
    if( (m_reparationFragment.status() == 2)
          && (b >= m_reparationFragment.retB() - 550
          && b <= m_reparationFragment.retB() + 550 ) )
        m_mediaPlayer.setPosition(m_reparationFragment.retA());
}

void MainWindow::slotSetColorElemetListWidget(QMediaPlayer::MediaStatus) //СЛОТ
{
//        /*Слот вызывает функцию m_trackLM->setColorListWidgetElement для установки текущей
//            проигруемой позиции в выделенный цвет, слот сробатывает если медиа статус равен
//            BufferedMedia*/

//        if(m_mediaPlayer.mediaStatus() == QMediaPlayer::BufferedMedia
//            &&  m_iIndexFileListPosition >= 0)
//        {
//            m_trackLM->setDefaultColorListWidget();
////            m_trackLM->setColorListWidgetElement(
////                        m_trackLM->TLM_sRealPlay.playlistNumber, m_iIndexFileListPosition, QColor(0, 100, 200));
//            m_trackLM->setColorListWidgetElement(
//                        m_trackLM->realTabPosition, m_iIndexFileListPosition, QColor(0, 100, 200));
//        }
}

void MainWindow::slotInvalidPlayngFile(QMediaPlayer::MediaStatus) //СЛОТ
{
    /*Слот преднозначин для воспроизведения следующиго файла если возникла ошибка
        при воспроизведении*/
    if(m_mediaPlayer.mediaStatus() == QMediaPlayer::InvalidMedia)
        slotNextFile();
}

void MainWindow::slotSetTabItemContextMenu(QPoint point)
{
    if(ui->tabWidget->tabBar()->tabAt(point) == -1)
        return;
    m_ContextMenuTabWidget->exec(QCursor::pos());
}

void MainWindow::slotDelTabWidgetElement(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::slotShowMenuOpenFile()
{
    m_ContextMenuOpenFile->exec(QCursor::pos());
}

void MainWindow::slotPlaybackActivated(int index)
{

}

void MainWindow::slotSetStartSettings()
{
    //Создание дефолтных папок
    if(!QDir(QApplication::applicationDirPath()).exists("conf"))
         QDir(QApplication::applicationDirPath() ).mkdir("conf");
    if(!QDir(QApplication::applicationDirPath()).exists("tmp"))
         QDir(QApplication::applicationDirPath() ).mkdir("tmp");
    if(!QDir(QApplication::applicationDirPath()).exists("playlist"))
         QDir(QApplication::applicationDirPath() ).mkdir("playlist");



    QSettings settings("conf/player.ini", QSettings::IniFormat);
    //Первый запуск приложения------------------------------------------------------------------
    if(!settings.value("RUN/NoRun").toInt())
    {
        m_qiPositionPlay = m_BASSPositionPlay = m_bFlagPausePlay  =
        m_iIndexFileListPosition = m_iReplayType = 0;
        ui->horizontalSliderVolume->setValue(25);
        slotVolumeSound(25);
        settings.setValue("SOUND/mute", 1);
        settings.setValue("RUN/NoRun", 1);
        return;
    }
    m_qiPositionPlay           = settings.value("REALPLAY/PositionQtDecoder").toInt();
    m_BASSPositionPlay      = settings.value("REALPLAY/PositionBassDecoder").toInt();

    m_bFlagPausePlay         = settings.value("REALPLAY/PlayPauseStop").toInt();

    m_iIndexFileListPosition = settings.value("PLAYLIST/RealPlaybackNumberPlaylist").toInt();

    //Настройка режима повтора-----------------------------------------------------------------
    m_iReplayType              = settings.value("REALPLAY/ReplayType").toInt();
    switch (m_iReplayType)
    {
        case 0:
            ui->pushButtonReplayType->setText("Rep No");
            break;
        case 1:
            ui->pushButtonReplayType->setText("Rep LS");
            break;
        case 2:
            ui->pushButtonReplayType->setText("Rep FL");
            break;
    }
    //Настройка громкасти и ползунка громкости------------------------------------------------
    slotVolumeSound(settings.value("SOUND/volume").toInt());
    ui->horizontalSliderVolume->setValue(settings.value("SOUND/volume").toInt());

}

void MainWindow::slotSetProgressPlayMax(QWORD max)
{
    ui->horizontalSliderProgressPlay->setMaximum(max);
}

void MainWindow::slotChangeStatusPlayer(int status)
{
   if(status == MyMediaPlayer::PLAY)
       ui->pushButtonPlay->setIcon(QIcon(":/new/prefix1/icon/MediaPlayer/media-playback-pause.png"));
   else if(status == MyMediaPlayer::PAUSE || status == MyMediaPlayer::STOP)
       ui->pushButtonPlay->setIcon(QIcon(":/new/prefix1/icon/MediaPlayer/media-playback-start.png"));
}


void MainWindow::slotShowWindowAudioEffect()
{
    if( !m_audioEffectWindow->isVisible())
    {
        m_audioEffectWindow->show();
        m_audioEffectWindow->move(x() +  width(), y());
    }
    else
        m_audioEffectWindow->close();
}

void MainWindow::slotShowWindowBuffereng(int status)
{
    //отобразить окно если satus == 0
    //закрыть окно если status == 1
    if(!status)
    {
        m_bufferengWindow->show();
        m_bufferengWindow->exec();
    }
    else m_bufferengWindow->close();
}

void MainWindow::setFormStyle()
{
        setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

        // Включаем прозрачность главной формы...
        setAttribute(Qt::WA_TranslucentBackground);

        // Задаём параметры прозрачности...
        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect -> setBlurRadius(9.0);
        shadowEffect -> setColor(QColor(0, 0, 0, 160));
        shadowEffect -> setOffset(4.0);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
        if(event->buttons() == Qt::LeftButton)
        {
            m_MouseEventDistance =  event->globalPos() - frameGeometry().topLeft();
            event->accept(); //Хрен знает для чего нужно, взято из примера "shapedclock"
        }
        QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->pos().y() >= 15)
        return;
        if(event->buttons() == Qt::LeftButton)
        {
            move( event->globalPos() - m_MouseEventDistance);
            event->accept(); //Хрен знает для чего нужно, взято из примера "shapedclock"
        }

        QMainWindow::mouseMoveEvent(event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 13, Qt::SolidLine, Qt::RoundCap,Qt::MiterJoin));
    painter.drawRect(0, 0, width(), 13);
    QMainWindow::paintEvent(event);
}

void MainWindow::slotPreviousFile() //СЛОТ
{
    /*Слот воспроизводит следующий файл в плейлисте, если плейлист пустой тогда выходим из слота.
        Если размер плейлиста больше или равно 1 тогда воспроизводим прелыдущий файл и уменшаем
        m_iIndexFileListPosition на 1*/
    if(m_fileListAdress->size() == 0)
        return;
    m_fileAdress->clear();
    if(m_iIndexFileListPosition >= 1)
    {
        m_fileAdress->append(m_fileListAdress->at(m_iIndexFileListPosition-1));
        m_iIndexFileListPosition--;
        slotPlayFileBASS(*m_fileAdress);
    }
    else
    {
        m_fileAdress->append(m_fileListAdress->at(m_iIndexFileListPosition));
        slotPlayFileBASS(*m_fileAdress);
    }
    m_bFlagPausePlay = 1;
}

void MainWindow::slotNextFile() //СЛОТ
{

    if(m_fileListAdress->size() == 0)
        return;
    m_fileAdress->clear();
    if(m_iIndexFileListPosition == m_fileListAdress->size() - 1)
    {
        m_fileAdress->append(m_fileListAdress->at(m_iIndexFileListPosition));
        slotPlayFileBASS(*m_fileAdress);
    }
    else
    {
        m_fileAdress->append(m_fileListAdress->at(m_iIndexFileListPosition+1));
        m_iIndexFileListPosition++;
        slotPlayFileBASS(*m_fileAdress);
    }
    m_bFlagPausePlay = 1;
}

void MainWindow::slotSetMute() //СЛОТ
{
    QSettings settings("conf/Player.ini", QSettings::IniFormat);
    if(m_mediaPlayer.isMuted() == true)
    {
        m_mediaPlayer.setMuted(false);
        settings.setValue("SOUND/mute", 0);
    }
    else
    {
        m_mediaPlayer.setMuted(true);
        settings.setValue("SOUND/mute", 1);
    }
}

void MainWindow::slotReplayPlayList(qint64 x) //СЛОТ
{

}

void MainWindow::slotReplayPlayList(QWORD x)
{
    if(m_iReplayType == 1 && x >= m_bassMediaPlayer->getLength() - 10000 && x <= m_bassMediaPlayer->getLength())
        slotNextFile();
    else if(m_iReplayType == 2 && x >= m_bassMediaPlayer->getLength() - 10000 && x <= m_bassMediaPlayer->getLength())
        m_bassMediaPlayer->play(m_fileListAdress->at(m_iIndexFileListPosition));
}

void MainWindow::slotSetReplayType() //СЛОТ
{
    QSettings settings("conf/Player.ini", QSettings::IniFormat);
    if(m_iReplayType == 0 )
    {
         m_iReplayType = 1;
         ui->pushButtonReplayType->setText("Rep LS");
         settings.setValue("REALPLAY/ReplayType", 1);
    }
    else if(m_iReplayType == 1)
    {
        m_iReplayType = 2;
        ui->pushButtonReplayType->setText("Rep FL");
        settings.setValue("REALPLAY/ReplayType", 2);
    }
    else if(m_iReplayType == 2)
    {
        m_iReplayType = 0;
        ui->pushButtonReplayType->setText("Rep No");
        settings.setValue("REALPLAY/ReplayType", 0);
    }
}

