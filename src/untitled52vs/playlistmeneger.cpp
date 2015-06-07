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
    m_mapPlaylistListWidget = new QMap<QString, MyQListWidget*>();
    m_mapPlaylistStringList = new QMap<QString, QStringList*>();

    m_contextMenuItem = new MyCondextMenu(this);
    connect(m_contextMenuItem, SIGNAL(signalFileInfo(int)),
                                                             SLOT(slotViewInfoFile(int)));
    connect(m_contextMenuItem, SIGNAL(signalAddFileAddFileLocal()),
                                                              SLOT(slotAddTrackLocal()));
    connect(m_contextMenuItem, SIGNAL(signalAddFileAddFileLocalFolder()),
                                                            SLOT(slotAddTrackFolder()));
    connect(m_contextMenuItem, SIGNAL(signalAddFileAddFileVk()),
                                                            SLOT(slotAddTrackVk()));\
    connect(m_contextMenuItem, SIGNAL(signalAddFileAddFileNetwork()),
                                                              SLOT(slotAddTrackNetwork()));
    //connect(m_contextMenuItem, SIGNAL(signalAddFileAtPlaylist())
    playlistXMLParse("Playlist/");
}

PlaylistMeneger::~PlaylistMeneger()
{

}

void PlaylistMeneger::addPlaylist(QStringList listElement, QString listName)
{
    QFile xmlPlaylist("Playlist/" +  listName + ".mpmp");
    if(! xmlPlaylist.open(QIODevice::WriteOnly | QIODevice::ReadOnly) )
    {
        QMessageBox::critical(0, "Ошибка четения/записи", "Во время четения/записи файла " + listName + ".mpmp"
                                                       ", произошла ошибка. " + xmlPlaylist.errorString());
        throw QString(xmlPlaylist.errorString());
    }

    //Выделение памяти, для хранения плэйлиста
    MyQListWidget *listWidget = new MyQListWidget(this);
    listWidget->addItems(listElement);
    //Добавление плэйлиста в ассациативный контейнер
    m_mapPlaylistListWidget->insert(listName, listWidget);;

    //Контекстное меню, для плейлиста
    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listWidget, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotShowContextMenu(QPoint)));

    //Если произойдит двойной клик по item- элементу MyQListWidget, значит воспроизвести
    connect(listWidget, SIGNAL(activated(QModelIndex)), SLOT(slotClickItemPlaylistWidget(QModelIndex)));

    //Выделение памяти, под хранения адрессов трэков к плейлисту
    QStringList *stringList = new QStringList();
    stringList->append(listElement); //Добавление трэков в выделеную память
    //Добаление списка треков в асоциативный контейнер
    m_mapPlaylistStringList->insert(listName, stringList);

    formingViewPlaylist(xmlPlaylist, listElement, listName);
}

void PlaylistMeneger::formingViewPlaylist(QFile &xmlPlaylist, QStringList &listElement, QString listName, int begin)
{
    QListWidgetItem *listWidgetItem;
    double totalDuration = 0.0; //Счетчик общей продолжительности(сек) всех треков

    XMLPlaylistMeneger::Writer xmlWriter(&xmlPlaylist);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Playlist");

    for(int i = begin; i < listElement.size(); ++i)
    {
        listWidgetItem = m_mapPlaylistListWidget->value(listName)->item(i);
        listWidgetItem->setSizeHint(QSize(100, 25));
        QMap<QString, QString> audioTeg =  MyMediaPlayer::audioTegReader(listElement.at(i));
        listWidgetItem->setText(audioTeg["Artist"] + "- " + audioTeg["Title"]);
        totalDuration += audioTeg["Length"].toDouble();
        listWidgetItem->setIcon(QIcon(":/new/prefix1/image/1.png"));

        //Запись в плэйлист XML
        xmlWriter.writeStartElement("Track");

            xmlWriter.writeStartElement("File"); //Путь к файлу
            xmlWriter.writeCharacters(listElement.value(i));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("Artist"); //Имя артиста
            xmlWriter.writeCharacters(audioTeg["Artist"]);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("Title"); //Название трэка
            xmlWriter.writeCharacters(audioTeg["Title"]);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("Length"); //Длина трэка
            xmlWriter.writeCharacters(audioTeg["Length"]);
            xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();
    }

    //Записать дополнительную информацию в конец файла
    xmlWriter.writeStartElement("MPMPlayerInfoPlaylist");
        xmlWriter.writeStartElement("Count"); //Количество трэков в плэйлисте
        xmlWriter.writeCharacters(QString::number(listElement.size()));
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("TotalDuration"); //общая продолжитедьность(сек)
        xmlWriter.writeCharacters(QString::number(totalDuration));
        xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    xmlPlaylist.close();
}


MyQListWidget *PlaylistMeneger::getPlaylistWidget(QString key)
{
    return m_mapPlaylistListWidget->value(key);
}

QStringList* PlaylistMeneger::getPlaylist(QString key)
{
    return m_mapPlaylistStringList->value(key);
}

bool PlaylistMeneger::playlistXMLParse(const QString &d)
{
    QDir dir(d);
    QStringList list(dir.entryList(QDir::Files));
    for(int i = 0; i < list.size(); i++)
    {

        QFile file(d + list.at(i));
        if(! file.open(QIODevice::ReadOnly))
            throw QString(tr("Не удалось выполеить четения плэлиста. ") + file.errorString());
        XMLPlaylistMeneger::Reader reader(&file);

        QStringList *filePath = new QStringList();
        QStringList artist;
        QStringList title;
        while(!reader.atEnd())
        {
            if(reader.isStartElement())
            {
                if(reader.name() == "File")
                {
                    filePath->append( reader.readElementText() );
                }
                if(reader.name() == "Artist")
                {
                    artist.append( reader.readElementText() );
                }
                if(reader.name() == "Title")
                {
                    title.append( reader.readElementText() );
                }
            }
            reader.readNext();
        }

        MyQListWidget *listWidget = new MyQListWidget(this);
        listWidget->addItems(*filePath);
        //Контекстное меню, для плейлиста
        listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(listWidget, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotShowContextMenu(QPoint)));

        //Если произойдит двойной клик по item- элементу MyQListWidget, значит воспроизвести
        connect(listWidget, SIGNAL(activated(QModelIndex)), SLOT(slotClickItemPlaylistWidget(QModelIndex)));
        QListWidgetItem *item = nullptr;
        for(int i = 0; i  < listWidget->count(); i++)
        {
            item = listWidget->item(i);
            item->setSizeHint(QSize(100, 25));
            item->setIcon(QIcon(":/new/prefix1/image/1.png"));
            item->setText(artist.at(i) + " - " + title.at(i));
        }
        QString listName = list.at(i).mid(0, list.at(i).size() - 6);
        m_mapPlaylistStringList->insert(listName, filePath);
        m_mapPlaylistListWidget->insert(listName, listWidget);
        m_tabWidgetPlaylist->addTab(listWidget, listName);
    }
    return true;
}


void PlaylistMeneger::slotShowContextMenu(QPoint point)
{
    QListWidgetItem *item = m_mapPlaylistListWidget->value(m_keyCurrentPlaylist)->itemAt(point);

    if(!item)
        return;

    m_contextMenuItem->SetFileAdress(item->text());
    m_contextMenuItem->setIndexItem(m_mapPlaylistListWidget->value(m_keyCurrentPlaylist)->indexAt(point).row());
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
    if(!m_mapPlaylistListWidget->size() || !m_mapPlaylistStringList->size())
        return;
    //получаем имя удаляемого элемента QTabBar по индексу
    //index- это номер элемента QTabBar
    //tabText(i)- возвращает имя элемента QTabBar
    QString strKey = m_tabWidgetPlaylist->tabBar()->tabText(index);
    //Освобождение памяти
    delete m_mapPlaylistListWidget->value(strKey);
    delete m_mapPlaylistStringList->value(strKey);
    //Удаление ключей и их связей из ассацеативного контейнера
    m_mapPlaylistListWidget->remove(strKey);
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
    if(m_mapPlaylistListWidget->contains(oldName) && m_mapPlaylistStringList->contains(oldName))
    {
        //Получить указатель на память плэйлиста и память списка треков
        mql =  m_mapPlaylistListWidget->value(oldName);
        strlist = m_mapPlaylistStringList->value(oldName);

        //Занести плейлист и список трэков в ассациативный контейнер,  под новым именем(ключом)
        m_mapPlaylistListWidget->insert(newName, mql);
        m_mapPlaylistStringList->insert(newName, strlist);

        //Удалить из ассациативного контейнера старое имя(ключ)
        m_mapPlaylistListWidget->remove(oldName);
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

void PlaylistMeneger::slotClickItemPlaylistWidget(QModelIndex index)
{
    emit signalClickItemPlaylistWidget(index, *m_mapPlaylistStringList->value(m_keyCurrentPlaylist));
}

void PlaylistMeneger::slotAddTrackLocal()
{
    QStringList tempList;
    tempList.append(QFileDialog::getOpenFileNames(this, tr("Open File"), "D:\\Музыка", tr("Audio Files (*.mp3 *.flac *.wav *.wma *.amr *.m4a *.m4r);;All files (*.*)")));
    if(! tempList.size() )
        return;
    QFile xmlPlaylist("Playlist/" +  m_keyCurrentPlaylist + ".mpmp");
    if(! xmlPlaylist.open(QIODevice::ReadOnly | QIODevice::WriteOnly))
    {
        QMessageBox::critical(0, "Ошибка четения/записи", "Во время четения/записи файла " + m_keyCurrentPlaylist + ".mpmp"
                                                       ", произошла ошибка. " + xmlPlaylist.errorString());
       return;
    }
    m_mapPlaylistStringList->value(m_keyCurrentPlaylist)->append(tempList);
    m_mapPlaylistListWidget->value(m_keyCurrentPlaylist)->addItems(tempList);
    emit signalAddNewTrack(tempList);
    formingViewPlaylist(xmlPlaylist,
                                           *m_mapPlaylistStringList->value(m_keyCurrentPlaylist),
                                           m_keyCurrentPlaylist,
                                           m_mapPlaylistListWidget->value(m_keyCurrentPlaylist)->count() - 1 - tempList.size() - 1);
    m_mapPlaylistListWidget->value(m_keyCurrentPlaylist)->update();
    xmlPlaylist.close();

}

void PlaylistMeneger::slotAddTrackFolder()
{

}

void PlaylistMeneger::slotAddTrackVk()
{

}

void PlaylistMeneger::slotAddTrackNetwork()
{

}


