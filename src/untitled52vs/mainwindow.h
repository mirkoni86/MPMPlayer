#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QListWidgetItem>
#include <QtWidgets>
#include <QDateTime>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QMediaPlayer>
#include <QDebug>
#include <QListWidget>
#include <QIcon>
#include <QByteArray>
#include <QAudio>
#include <QAudioDeviceInfo>
#include <QtMultimedia/QSoundEffect>
#include <QtConcurrent/QtConcurrent>
#include "trackListMeneger.h"
#include "reparationFragment.h"
#include "contextmenutabwidget.h"
#include "contextmenuopenfile.h"
#include "contextmenuglobal.h"
#include "vkauth.h"
#include "bass.h"
#include "cstring"
#include "mymediaplayer.h"
#include "audioeffectwindow.h"
#include "windowplaylist.h"
#include "fftvisualwidget.h"
#include "bufferengwindow.h"
#include "playlistmeneger.h"
#include "dialogrenameplaylist.h"
#include "settingmanager.h"
#include "opensource.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotOpenFile();
    void slotOpenPlaylist();
    void slotOpenFolder();
    void slotOpenVKPlaylist();
    void slotPlayFile();
    void slotPlayFileBASS(QString file);
    void slotPlayFileList(QModelIndex x);
    void slotPlayFileList(QModelIndex x, QStringList str);
    void slotPlayFileListBASS(QModelIndex x);
    void slotPlayFileListBASS(QModelIndex x, QStringList str);
    void slotAddFileFileListAdress(QStringList list);
    void slotStopFile();
    void slotPositionProgress(qint64 x);
    void slotPositionProgress(QWORD x);
    void slotPositionProgresMousePress(int x);
    void slotVolumeSound(int x);
    void slotPreviousFile();
    void slotNextFile();
    void slotSetMute();
    void slotReplayPlayList(qint64 x);
    void slotReplayPlayList(QWORD x);
    void slotSetReplayType();
    void metaTegInfo();
    void slotReparationAB();
    void slotReplayReparationAB(qint64 b);
    void slotSetColorElemetListWidget(QMediaPlayer::MediaStatus);
    void slotInvalidPlayngFile(QMediaPlayer::MediaStatus);
    void slotSetTabItemContextMenu(QPoint point);
    void slotDelTabWidgetElement(int index);
    void slotShowMenuOpenFile();
    void slotPlaybackActivated(int index = 0);
    void slotSetStartSettings();
    void slotSetProgressPlayMax(QWORD max);
    void slotChangeStatusPlayer(int status);
    void slotShowWindowAudioEffect();
    void slotShowWindowBuffereng(int status); //отображает окно о выполнении буферации. 0- начало, 1- конец
    void slotShowSettingsWindow();
    void slotLoadCover(QString file);

signals:
    void signalPlayReparation(qint64 rep, ReparationFragment &repFrag);
private slots:
    void slotShowContextMenuGlobal(QPoint point);

protected:
   virtual void  mousePressEvent(QMouseEvent *event);
   virtual void mouseMoveEvent(QMouseEvent *event);
private:
    Ui::MainWindow         *ui;
    QString                     *m_fileAdress;
    QStringList                *m_fileListAdress;
    QString                     *m_fileDirectors;
    QMediaPlayer              m_mediaPlayer;
    QListWidgetItem        *m_listWidgetItemTrackList;
    TrackListMeneger       *m_trackLM;
    PlaylistMeneger           *m_playlistMeneger;
    ReparationFragment     m_reparationFragment;
    int                              m_bFlagPausePlay;
    qint64                         m_qiPositionPlay;
    int                              m_iIndexFileListPosition;
    int                              m_iReplayType;
    int                              m_BASSPositionPlay;
    ContextMenuTabWidget *m_ContextMenuTabWidget;
    ContextMenuOpenFile *m_ContextMenuOpenFile;
    ContextMenuGlobal *m_contextMenuGlobal;
    MyMediaPlayer            *m_bassMediaPlayer;
    AudioEffectWindow      *m_audioEffectWindow;
    QPoint                           m_MouseEventDistance;
    FFTVisualWidget *m_fftvisualWidget;
    BufferengWindow *m_bufferengWindow;
    SettingManager *m_settingMenger;
};

#endif // MAINWINDOW_H
