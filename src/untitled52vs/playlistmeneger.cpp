#include "playlistmeneger.h"

PlaylistMeneger::PlaylistMeneger(QTabWidget *tabwgt, QWidget *parent) :
    m_tabWidgetPlaylist(tabwgt), QWidget(parent)
{
    /*
        m_mapPlaylist- служит для хранения плэлистов
        m_mapPlaylistStringList- служит для хранения треков к плейлистам
        элементы в m_mapPlaylist и m_mapPlaylistStringList имеют общий ключ
        которым являится имя плелиста
    */
    m_mapPlaylist = new QMap<QString, MyQListWidget*>();
    m_mapPlaylistStringList = new QMap<QString, QStringList*>();
    m_contextMenuItem = new MyCondextMenu(this);
}

PlaylistMeneger::~PlaylistMeneger()
{

}

void PlaylistMeneger::addPlaylist(QStringList listElement, QString listName)
{
    //Выделение памяти, для хранения плэйлиста
    MyQListWidget *listWidget = new MyQListWidget(this);
    listWidget->addItems(listElement);
    //Добавление плэйлиста в ассациативный контейнер
    m_mapPlaylist->insert(listName, listWidget);

    //Контекстное меню, для плейлиста
    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listWidget, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotShowContextMenu(QPoint)));

    //Выделение памяти, под хранения адрессов трэков к плейлисту
    QStringList *stringList = new QStringList();
    stringList->append(listElement); //Добавление трэков в выделеную память
    //Добаление списка треков в асоциативный контейнер
    m_mapPlaylistStringList->insert(listName, stringList);

    QListWidgetItem *listWidgetItem;
    //В цикле формируются вид добовляемых элементов
    for(int i = 0; i < listElement.size(); ++i)
    {
        listWidgetItem = m_mapPlaylist->value(listName)->item(i);
        listWidgetItem->setSizeHint(QSize(100, 25));
        QMap<QString, QString> audioTeg =  MyMediaPlayer::audioTegReader(listElement.at(i));
        listWidgetItem->setText(audioTeg["Artist"] + "- " + audioTeg["Title"]);
        listWidgetItem->setIcon(QIcon(":/new/prefix1/image/1.png"));
    }

}

void PlaylistMeneger::addElement(QStringList &listElement)
{
    //Получает размер плэйлиста, пока не добалены новые элементы
    const int LEN_OLD = m_mapPlaylist->value(m_keyCurrentPlaylist)->count();
    //Добавление новых элементов
     m_mapPlaylist->value(m_keyCurrentPlaylist)->addItems(listElement);
    QListWidgetItem *listWidgetItem;
    //В цикле формируются вид добовляемых элементов
    //начало отсчета от старой длины до новой
    for(int i = LEN_OLD - 1; i < m_mapPlaylist->value(m_keyCurrentPlaylist)->count(); ++i)
    {
        listWidgetItem = m_mapPlaylist->value(m_keyCurrentPlaylist)->item(i);
        listWidgetItem->setSizeHint(QSize(100, 25));
        QMap<QString, QString> audioTeg =  MyMediaPlayer::audioTegReader(listElement.at(i));
        listWidgetItem->setText(audioTeg["Artist"] + "- " + audioTeg["Title"]);
        listWidgetItem->setIcon(QIcon(":/new/prefix1/image/1.png"));
    }
}

void PlaylistMeneger::slotShowContextMenu(QPoint point)
{
    QListWidgetItem *item = m_mapPlaylist->value(m_keyCurrentPlaylist)->itemAt(point);

    if(!item)
        return;

    m_contextMenuItem->SetFileAdress(item->text());
    m_contextMenuItem->setIndexItem(m_mapPlaylist->value(m_keyCurrentPlaylist)->indexAt(point).row());
    m_contextMenuItem->exec(QCursor::pos());
}

void PlaylistMeneger::slotViewInfoFile(int indexItem)
{
    FileInfoDialog *fid = new FileInfoDialog(m_mapPlaylistStringList->value(m_keyCurrentPlaylist)->at(indexItem));
    fid->exec();
    delete fid; //Так НАВЕРНОЕ будет лучше)))))))))
}

void PlaylistMeneger::slotRemovePlaylist(int index)
{
    if(!m_mapPlaylist->size() || !m_mapPlaylistStringList->size())
        return;
    //получаем имя удаляемого элемента QTabBar по индексу
    //index- это номер элемента QTabBar
    //tabText(i)- возвращает имя элемента QTabBar
    QString strKey = m_tabWidgetPlaylist->tabBar()->tabText(index);
    //Освобождение памяти
    delete m_mapPlaylist->value(strKey);
    delete m_mapPlaylistStringList->value(strKey);
    //Удаление ключей и их связей из ассацеативного контейнера
    m_mapPlaylist->remove(strKey);
    m_mapPlaylistStringList->remove(strKey);
    //Удаление элемента QTabBar
    m_tabWidgetPlaylist->tabBar()->removeTab(index);


}

void PlaylistMeneger::slotRenamePlaylist(int index)
{
    //Сначала получить старое имч плэлиста
    QString oldName = m_tabWidgetPlaylist->tabBar()->tabText(index);

    //Отобразить диалоговое окно ввода
     DialogRenamePlaylist *dialog = new DialogRenamePlaylist(m_tabWidgetPlaylist, index, this);
     dialog->exec();

    //TODO-----------------------------------------------------------------------------------------------------
    //Здесь желательно бы выполнить проверку на повторяющееся имя в списке плэйлистов
    //TODO-----------------------------------------------------------------------------------------------------

    //Получить новое имя
    QString newName  = m_tabWidgetPlaylist->tabBar()->tabText(index);

    //Если имена идентичны то выйте
    if(newName == oldName)
        return;

    MyQListWidget *mql = NULL;
    QStringList *strlist = NULL;

    //Если такие ключи соществуют в ассациативных контейнерах
    if(m_mapPlaylist->contains(oldName) && m_mapPlaylistStringList->contains(oldName))
    {
        //Получить указатель на память плэйлиста и память списка треков
        mql =  m_mapPlaylist->value(oldName);
        strlist = m_mapPlaylistStringList->value(oldName);

        //Занести плейлист и список трэков в ассациативный контейнер,  под новым именем(ключом)
        m_mapPlaylist->insert(newName, mql);
        m_mapPlaylistStringList->insert(newName, strlist);

        //Удалить из ассациативного контейнера старое имя(ключ)
        m_mapPlaylist->remove(oldName);
        m_mapPlaylistStringList->remove(oldName);
    }
    else
        QMessageBox::critical(this, "Внутреннея ошибка", "Error " +  this->objectName() + " " + "::slotRenamePlaylist()");


}

void PlaylistMeneger::slotSetCurrentPlaylist(int index)
{
    m_keyCurrentPlaylist =  m_tabWidgetPlaylist->tabBar()->tabText(index);
    m_indexCurrentPlaylist = index;
}
