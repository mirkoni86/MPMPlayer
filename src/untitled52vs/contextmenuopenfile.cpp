#include "contextmenuopenfile.h"

ContextMenuOpenFile::ContextMenuOpenFile(QWidget *parent) :
    QMenu(parent)
{
    QAction *openFile = new QAction(QIcon(":/new/prefix1/icon/MediaPlayer/document-open.png") ,tr("Открыть локальный файл"),  this);
    QAction *openFolder = new QAction(QIcon(":/new/prefix1/icon/MediaPlayer/document-open-folder.png"), tr("Открыть папку"), this);
    QAction *openVKontakte = new QAction(QIcon(":/new/prefix1/icon/MediaPlayer/vk.png"),tr("ВКонтакте"), this);
    QAction *openUrl = new QAction(QIcon(":/new/prefix1/icon/MediaPlayer/download.png"), tr("Открыть по URL"), this);

    addAction(openFile);
    addAction(openFolder);
    addAction(openVKontakte);
    addAction(openUrl);

    connect(openFile, SIGNAL(triggered()), SIGNAL(signalOpenFile()));
    connect(openFolder, SIGNAL(triggered()), SIGNAL(signalOpenFolder()));
    connect(openVKontakte, SIGNAL(triggered()), SIGNAL(signalOpenVkontakte()));
    connect(openUrl, SIGNAL(triggered()), SIGNAL(signalOpenUrl()));

}
