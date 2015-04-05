#include "mycondextmenu.h"


MyCondextMenu::MyCondextMenu(QWidget *parent) : QMenu(parent)
{
    QAction * actionAddFile = new QAction(tr("Добавить в плейлист"), this);
    QAction *actionDeleteFile = new QAction(tr("Удалить "), this);
    QAction *actionInfo = new QAction(tr("Информация о треке"), this);
    QAction *actionInfoAutor = new QAction(tr("Информация о исполнителе"), this);
    QAction *actionOpenDisck = new QAction(tr("Открыть в файловом менеджере"), this);
    QAction *actionSort = new QAction(tr("Сортировка"), this);
    QAction *actionTextTrack = new QAction(tr("Найти текст песни"), this);
    QAction *actionCopyBuffer = new QAction(tr("Копировать в буфер обмена"), this);

    addAction(actionAddFile);
    addAction(actionDeleteFile);
    addSeparator();
    addAction(actionInfo);
    addAction(actionInfoAutor);
    addAction(actionOpenDisck);
    addAction(actionSort);
    addAction(actionTextTrack);
    addAction(actionCopyBuffer);


    connect(actionInfo, SIGNAL(triggered()), SLOT(slotFileInfo()));
    connect(actionAddFile, SIGNAL(triggered()), SLOT(slotAddFileAtPlaylist()));
    connect(actionDeleteFile, SIGNAL(triggered()), SLOT(slotDeleteTrack()));
    connect(actionOpenDisck, SIGNAL(triggered()), SLOT(slotOpenAtFileMeneger()));
    connect(actionSort, SIGNAL(triggered()), SLOT(slotSort()));
    connect(actionInfoAutor, SIGNAL(triggered()), SLOT(slotInfoAutor()));
}

MyCondextMenu::~MyCondextMenu()
{

}

void MyCondextMenu::SetFileAdress(QString adress)
{
    fileAdress = adress;
    qDebug() << fileAdress << endl;
}

void MyCondextMenu::setIndexItem(int index)
{
    m_ItemIndex = index;
}

int MyCondextMenu::retIndexItem()
{
    return m_ItemIndex;
}

//----------------------------------------------------------------------
//Private слоты
void MyCondextMenu::slotFileInfo()
{
    emit signalFileInfo(m_ItemIndex);
}

void MyCondextMenu::slotAddFileAtPlaylist()
{
    emit signalAddFileAtPlaylist();
}

void MyCondextMenu::slotDeleteTrack()
{
    emit signalDeleteTrack();
}

void MyCondextMenu::slotOpenAtFileMeneger()
{
    emit signalOpenAtFileMeneger(m_ItemIndex);
}

void MyCondextMenu::slotSort()
{
    emit signalSort();
}

void MyCondextMenu::slotInfoAutor()
{
    emit signalInfoAutor(m_ItemIndex);
}
