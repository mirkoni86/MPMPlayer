#ifndef PLAYLISTMENEGER_H
#define PLAYLISTMENEGER_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QListWidgetItem>
#include <QMessageBox>
#include "myqlistwidget.h"
#include "mymediaplayer.h"
#include "mycondextmenu.h"
#include "fileinfodialog.h"
#include "dialogrenameplaylist.h"

class PlaylistMeneger : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistMeneger(QTabWidget *tabwgt, QWidget *parent = 0);
    ~PlaylistMeneger();
    void addPlaylist(QStringList listElement, QString listName);
    void addElement(QStringList &listElement);
signals:

public slots:
    void slotViewInfoFile(int indexItem);
    void slotRemovePlaylist(int index);
    void slotRenamePlaylist(int index);
    void slotSetCurrentPlaylist(int index);
private slots:
    void slotShowContextMenu(QPoint point);
private:
    QTabWidget *m_tabWidgetPlaylist; //Указатель на TabWidget на котором размещаются плейлисты
    //Два контейнера для плэйлистов, первый хранит ПЛЭЛИСТЫ а второй СПИСОКИ ТРЭКОВ К ПЛЭЙЛИСТАМ
    QMap<QString, MyQListWidget*> *m_mapPlaylist;
    QMap<QString, QStringList*> *m_mapPlaylistStringList;
    QString  m_keyCurrentPlaylist; //Хронится имя(ключь) текущего(по которому тыкнули) плэйлиста
    int m_indexCurrentPlaylist; //Хронится индекс текущего(по которому тыкнули) плэйлиста
    MyCondextMenu *m_contextMenuItem;
    QFile *m_playlistXMLRedWrt;
};

#endif // PLAYLISTMENEGER_H
