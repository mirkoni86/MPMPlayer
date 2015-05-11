#include "mycondextmenu.h"


MyCondextMenu::MyCondextMenu(QWidget *parent) : QMenu(parent)
{
    QAction * actionAddFile = new QAction(tr("Добавить в плейлист"), this);
     addAction(actionAddFile);
    QAction *actionAddFileLocal = new QAction(tr("Открыть локальный файл"), this);
    QAction *actionAddFileLocalFolder = new QAction(tr("Открыть папку"), this);
    QAction *actionAddFileVk = new QAction(tr("ВКонтакте"), this);
    QAction *actionAddFileNetwork = new QAction(tr("Открыть по URL"), this);
    QMenu *menuContextAddFile = new QMenu(this);
    menuContextAddFile->addAction(actionAddFileLocal);
    menuContextAddFile->addAction(actionAddFileLocalFolder);
    menuContextAddFile->addAction(actionAddFileVk);
    menuContextAddFile->addAction(actionAddFileNetwork);
    actionAddFile->setMenu(menuContextAddFile);
    connect(actionAddFileLocal, SIGNAL(triggered()), SIGNAL(signalAddFileAddFileLocal()));
    connect(actionAddFileLocalFolder, SIGNAL(triggered()), SIGNAL(signalAddFileAddFileLocalFolder()));
    connect(actionAddFileVk, SIGNAL(triggered()), SIGNAL(signalAddFileAddFileVk()));
    connect(actionAddFileNetwork, SIGNAL(triggered()), SIGNAL(signalAddFileAddFileNetwork()));

    QAction *actionDeleteFile = new QAction(tr("Удалить "), this);
    QAction *actionInfo = new QAction(tr("Информация о треке"), this);
    QAction *actionInfoAutor = new QAction(tr("Информация о исполнителе"), this);
    QAction *actionOpenDisck = new QAction(tr("Открыть в файловом менеджере"), this);
    QAction *actionSort = new QAction(tr("Сортировка"), this);
    QAction *actionTextTrack = new QAction(tr("Найти текст песни"), this);
    QAction *actionCopyBuffer = new QAction(tr("Копировать в буфер обмена"), this);

    addAction(actionDeleteFile);
    addSeparator();
    addAction(actionInfo);
    addAction(actionInfoAutor);
    addAction(actionOpenDisck);
    addAction(actionSort);
    addAction(actionTextTrack);
    addAction(actionCopyBuffer);


    connect(actionInfo, SIGNAL(triggered()), SLOT(slotFileInfo()));
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
