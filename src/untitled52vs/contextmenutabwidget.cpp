#include "contextmenutabwidget.h"

ContextMenuTabWidget::ContextMenuTabWidget(QTabBar *tabBar, QWidget *parent) :
     m_pTabBar(tabBar), QMenu(parent)
{
    QAction *closePlaylist = new QAction(QIcon(":/new/prefix1/icon/MediaPlayer/tab-close.png"), tr("Закрыть плейлист"), this);
    QAction *renamePlaylist = new QAction(QIcon(":/new/prefix1/icon/MediaPlayer/edit-rename.png"),tr("Переименовать плэйлист"), this);
    QAction *addPlaylist = new QAction(QIcon(":/new/prefix1/icon/MediaPlayer/tab-new-background.png"), tr("Добавить плэйлист"), this);

    addAction(addPlaylist);
    addAction(closePlaylist);
    addAction(renamePlaylist);

    connect(closePlaylist, SIGNAL(triggered()), SLOT(slotRemoveTabElement()));
    connect(renamePlaylist, SIGNAL(triggered()), SLOT(slotRanameTabElement()));
    connect(addPlaylist, SIGNAL(triggered()), SIGNAL(signalAddTabElement()));
}

ContextMenuTabWidget::~ContextMenuTabWidget()
{

}

void ContextMenuTabWidget::slotSetIndexClickedTabBar(int index)
{
    indexClickedTabBar = index;
    qDebug() << "ContextMenuTabWidget::slotSetIndexClickedTabBar: " << index << endl;
}

void ContextMenuTabWidget::slotSetTabBarPointer(QTabBar *tb)
{
    m_pTabBar = tb;
}

void ContextMenuTabWidget::slotRemoveTabElement()
{
    emit signalRemoveTabElement(indexClickedTabBar);
}

void ContextMenuTabWidget::slotRanameTabElement()
{
    emit signalRenameTabElement(indexClickedTabBar);
}
