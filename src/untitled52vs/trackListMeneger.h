#ifndef TRACKLISTMENEGER_H
#define TRACKLISTMENEGER_H
#include <QWidget>
#include <QDialog>
#include <QLinkedList>
#include <QListWidget>
#include <QVector>
#include <QMenu>
#include <QDebug>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QTimer>
#include <QAction>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollBar>
#include <QTime>
#include <QProcess>

#include "mycondextmenu.h"
#include "myid3tegextractor.h"
#include "contextmenutabwidget.h"
#include "dialogdeleteplaylist.h"
#include "dialogrenameplaylist.h"
#include "myqlistwidget.h"
#include "bass.h"
#include "bassflac.h"
#include "basswma.h"
#include "bass_fx.h"
#include "tags.h"
#include "artistinfowiki.h"


class TrackListMeneger : public QWidget
{
    Q_OBJECT

public:
   explicit TrackListMeneger(QWidget *parent = 0);
    ~TrackListMeneger();
    void addList(QStringList fileAddPlaylist, QString playlistName);
    MyQListWidget *retList();
    MyQListWidget *retList(int index);
    QString *retListName();
    QString *retListName(int index);
    QStringList retStringList();
    QStringList retStringList(int index);
    int realSize();
    int realTabPosition;
    int numberElementColor;
    //Функции работы с векторами
    void resizeBlocksVector(int syn);
    void removeElementBlocksVector(int elm);
    void elementPushBackBlocksVector(QStringList *fileAddPlaylist, QString *playlistName, MyQListWidget *listWdt);
    void setColorListWidgetElement(int numberStringList, int numberElement, QColor color);
    void setDefaultColorListWidget();
    QString id3tegExtract(QString fileadress);
    struct RealPlay
    {
        int playlistNumber;
        int fileNumber;
    } TLM_sRealPlay;
    QMenu *getContextMenuItem() const;
    void setPointTabWidget(QTabWidget *point);


signals:
    void signalItemPosition(QModelIndex sx, QStringList sl);

public slots:
    void slotListChangeItem(QModelIndex x);
    void setChenTabPos(int it);
    void slotMessageConnect(int ps);
    void slotExtractMediaTeg(bool ok, QString &fadress);
    void slotShowContextMenu(QPoint point);
    void slotViewInfoFile(int indexItem);
    void slotAddTrack();
    void slotDeleteTrack();
    void slotOpenAtFileMeneger(int index);
    void slotSort();
    void slotShowAutorInfo(int index);
    void slotRemoveTabWidgetElement(int index);
    void slotRenameTabWidgetElement(int index);
    void slotSwapPlaylist(int a, int b);

protected:


private:
    QString retAudioMetaDataInfo(QString audioFile, int rIndex = 0);
    QListWidgetItem                      *m_listWItem;
    int                                            m_realPosition;
    int                                            m_realIndexClicked;
    QVector<MyQListWidget* >      *m_vectorListW;
    QVector<QListWidgetItem* >   *m_vectorListWItem;
    QVector<QString* >                *m_vectorListName;
    QVector<QStringList* >           *m_vectorStringList;
    int                                            m_realSizeVector;
    int                                            m_playPosition;
    int                                             m_allLenght;
    QMediaPlayer                           *m_mediaPlayerTLM;
    MyCondextMenu                       *m_contextMenuItem;
    QTabWidget                             *m_pTabWudget;
    QFile                                         *m_pFilePlaylist;
};
#endif // TRACKLISTMENEGER_H
