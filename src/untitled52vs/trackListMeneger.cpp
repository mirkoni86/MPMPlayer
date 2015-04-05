#include "trackListMeneger.h"
#include "fileinfodialog.h"

TrackListMeneger::TrackListMeneger(QWidget *parent) : QWidget(parent), m_realPosition(0)
{

    //Инициилизация векторов
    m_vectorListW         = new QVector<MyQListWidget* >    (0);
    m_vectorListName    = new QVector<QString* >          (0);
    m_vectorStringList   = new QVector<QStringList* >     (0);
    m_mediaPlayerTLM  = new QMediaPlayer(this);
    m_realSizeVector     = 0;
    m_allLenght = 0;

    m_contextMenuItem = new MyCondextMenu(this);
    connect(m_contextMenuItem, SIGNAL(signalFileInfo(int)),                   SLOT(slotViewInfoFile(int)));
    connect(m_contextMenuItem, SIGNAL(signalAddFileAtPlaylist()),                 SLOT(slotAddTrack()));
    connect(m_contextMenuItem, SIGNAL(signalDeleteTrack()),                        SLOT(slotDeleteTrack()));
    connect(m_contextMenuItem, SIGNAL(signalOpenAtFileMeneger(int)),   SLOT(slotOpenAtFileMeneger(int)));
    connect(m_contextMenuItem, SIGNAL(signalSort()),                                  SLOT(slotSort()));
    connect(m_contextMenuItem, SIGNAL(signalInfoAutor(int)), SLOT(slotShowAutorInfo(int)));

}

TrackListMeneger::~TrackListMeneger()
{
    //delete [] listName;
    //delete [] listW;
}
void TrackListMeneger::addList(QStringList fileAddPlaylist, QString playlistName)
{
    //---------------------------------------------------------------------------------------
    if(m_realPosition == 100) //Нельзя больше ста плэйлистов
        return;
    QStringList *strAddP        = new QStringList(fileAddPlaylist);
    QString *strPlName         = new QString(playlistName);
    MyQListWidget *lw             = new MyQListWidget(this);
    lw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Создание контекстного меню для плейлиста
    lw->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(lw, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotShowContextMenu(QPoint)));
    lw->addItems(*strAddP);
    for(int i = 0; i < fileAddPlaylist.size(); ++i)
    {
        m_listWItem = lw->item(i);
        m_listWItem->setSizeHint(QSize(100, 25));
        m_listWItem->setText( id3tegExtract(strAddP->at(i)));
        m_listWItem->setIcon(QIcon(":/new/prefix1/image/1.png"));
    }
    elementPushBackBlocksVector(strAddP, strPlName, lw);
    resizeBlocksVector(1);
    m_realPosition++;
    slotMessageConnect(m_realPosition);

}
int TrackListMeneger::realSize()
{
    return m_realPosition;
}

void TrackListMeneger::slotListChangeItem(QModelIndex x)
{
    emit signalItemPosition(x, *m_vectorStringList->value(realTabPosition));
    qDebug() << x.row();
}

MyQListWidget *TrackListMeneger::retList()
{
    return m_vectorListW->value(m_realPosition-1);
}
MyQListWidget *TrackListMeneger::retList(int index)
{
    return m_vectorListW->value(index);
}
QString *TrackListMeneger::retListName()
{
    return m_vectorListName->value(m_realPosition-1);
}
QString *TrackListMeneger::retListName(int index)
{
    return m_vectorListName->value(index);
}

QStringList TrackListMeneger::retStringList()
{
    TLM_sRealPlay.playlistNumber = m_realPosition-1;
    return *m_vectorStringList->value(m_realPosition-1);
}

QStringList TrackListMeneger::retStringList(int index)
{
    TLM_sRealPlay.playlistNumber = index;
    return *m_vectorStringList->value(index);
}
void TrackListMeneger::setChenTabPos(int it)
{
    realTabPosition = it;
    qDebug() << it << endl;
}

void TrackListMeneger::slotMessageConnect(int ps)
{
    for(int i = 0; i < ps; ++i)
    {
        connect(m_vectorListW->value(i), SIGNAL(activated(QModelIndex)),
                                                    SLOT(slotListChangeItem(QModelIndex)));
        qDebug() << i << " OK" << endl;
    }

}


QString TrackListMeneger::retAudioMetaDataInfo(QString audioFile, int rIndex)
{
    rIndex = rIndex;
    return audioFile;
}
QMenu *TrackListMeneger::getContextMenuItem() const
{
    return m_contextMenuItem;
}

void TrackListMeneger::setPointTabWidget(QTabWidget *point)
{
    m_pTabWudget = point;
}

//Функции для работы с векторми
void TrackListMeneger::resizeBlocksVector(int syn)
{
    m_realSizeVector += syn;
    m_vectorListW->resize(m_realSizeVector);
    m_vectorListName->resize(m_realSizeVector);
    m_vectorStringList->resize(m_realSizeVector);
}
void TrackListMeneger::removeElementBlocksVector(int elm)
{
    m_vectorListW->remove(elm);
    m_vectorListName->remove(elm);
    m_vectorStringList->remove(elm);
}
void TrackListMeneger::elementPushBackBlocksVector(
        QStringList *fileAddPlaylist, QString *playlistName, MyQListWidget *listWdt)
{
    m_vectorListName->push_back(playlistName);
    m_vectorStringList->push_back(fileAddPlaylist);
    m_vectorListW->push_back(listWdt);
}

void TrackListMeneger::setColorListWidgetElement(int numberListWidget, int numberElement, QColor color)
{
    QListWidgetItem *item = m_vectorListW->value(numberListWidget)->item(numberElement);
    item->setBackgroundColor(QColor(color));
}

void TrackListMeneger::setDefaultColorListWidget()
{
    QListWidgetItem *item = 0;
    for(int i = 0; i < m_vectorListW->size(); ++i)
    {
        for(int j = 0; j < m_vectorListW->value(i)->count(); ++j)
        {
             item = m_vectorListW->value(i)->item(j);
            if(item->backgroundColor() == QColor(0, 100, 200) )
                m_vectorListW->value(i)->item(j)->setBackgroundColor(QColor(255, 255, 255));
        }
    }

}

QString TrackListMeneger::id3tegExtract(QString fileadress)
{
//    #include <iostream>
//    using namespace std;
//    ID3_Tag tag;
//     char *pCh = new  char[fileadress.size() + 1];
//    for(int i = 0; i <= fileadress.size(); i++)
//    {
//        if(fileadress.data()[i] == '\0')
//        {
//            pCh[i] = '\0';
//            break;
//        }
//        pCh[i] =  fileadress.at(i).unicode();
//        //cout << pCh[i];
//       cout << (int)  fileadress.at(i).unicode() << " ";
//    }
//    cout << endl;
//    tag.Link(pCh, ID3TT_ID3V1 | ID3TT_LYRICS3V2 | ID3TT_MUSICMATCH);
//    fileadress.clear();
//    fileadress.append(ID3_GetArtist(&tag)).append(" - ").append(ID3_GetTitle(&tag));

//    if(fileadress.size() < 3)
//        return fileadress;
//    if(fileadress.mid(fileadress.size() - 3) == "mp3" )
//    {
//        MyId3TegExtractor tegE(fileadress);
//        QString author = tegE.ID3v1.autor;
//        QString title = tegE.ID3v1.title;
//        if(author == "" && title == "")
//            return fileadress;
//        fileadress.clear();
//        fileadress.append(author + "- " + title);
//        return fileadress;
//    }


    //BASS_Free();
    bool ok = BASS_Init (-1, 44100, 0 , NULL, NULL);
    if ( false == ok || true == ok)
    {
        HSTREAM stream;
        QByteArray barray = fileadress.toLocal8Bit().data();
        char *mfile = barray.data();
        for(int i = 0; mfile[i] != '\0'; ++i)
        {
            if(mfile[i] == '\\')
                mfile[i] = '/';
        }
        if( fileadress.mid(fileadress.size()-5) == ".flac" || fileadress.mid(fileadress.size()-5) == ".FLAC") //Creates a sample stream from an FLAC
            stream =   BASS_FLAC_StreamCreateFile(FALSE, mfile, 0, 0, 0);
        else if (fileadress.mid(fileadress.size()-4) == ".wma" || fileadress.mid(fileadress.size()-4) == ".WMA") // Creates a sample stream from an WMA
            stream = BASS_WMA_StreamCreateFile(FALSE, mfile, 0, 0, 0);
        else if(fileadress.mid(0, 7) == "http://" || fileadress.mid(0, 8) == "https://" || fileadress.mid(0, 6) == "ftp://")
            return fileadress;
        else
            stream = BASS_StreamCreateFile(FALSE, mfile, 0, 0, 0);         //Creates a sample stream from an MP3, MP2, MP1, OGG, WAV, AIFF
        m_allLenght += static_cast<int>( BASS_ChannelBytes2Seconds(stream ,  BASS_ChannelGetLength(stream, BASS_POS_BYTE)) );
        fileadress.clear();
        fileadress.append(TAGS_Read( stream, "%UTF8(%ARTI)- %UTF8(%TITL)" ));
    }
    qDebug() << "AllLenght: " << m_allLenght;
    return fileadress;
}

void TrackListMeneger::slotExtractMediaTeg(bool ok, QString &fadress)
{
    m_mediaPlayerTLM->metaData("Title").toString();
}

void TrackListMeneger::slotShowContextMenu(QPoint point)
{
    QListWidgetItem *item;
    item = m_vectorListW->value(realTabPosition)->itemAt(point);

    if(!item)
        return;

    m_contextMenuItem->SetFileAdress(item->text());
    m_contextMenuItem->setIndexItem(m_vectorListW->value(realTabPosition)->indexAt(point).row());
    m_contextMenuItem->exec(QCursor::pos());
}

void TrackListMeneger::slotViewInfoFile(int indexItem)
{
    FileInfoDialog *fid = new FileInfoDialog(m_vectorStringList->value(realTabPosition)->at(indexItem));
    fid->exec();
    delete fid; //Так будет лучше
}

void TrackListMeneger::slotAddTrack()
{

    m_vectorStringList->value(realTabPosition)->append(QFileDialog::getOpenFileNames(this, tr("Открыть файл "), "", tr("MP3 files (*.mp3);;All files (*.*)")));
    m_vectorListW->value(realTabPosition)->clear();
    m_vectorListW->value(realTabPosition)->addItems(*m_vectorStringList->value(realTabPosition));
    for(int i = 0; i < m_vectorListW->value(realTabPosition)->count(); ++i)
    {
        m_listWItem = m_vectorListW->value(realTabPosition)->item(i);
        m_listWItem->setSizeHint(QSize(100 , 25));
        m_listWItem->setText( id3tegExtract(m_vectorStringList->value(realTabPosition)->at(i)));
        m_listWItem->setIcon(QIcon(":/new/prefix1/image/1.png"));
    }
}

void TrackListMeneger::slotDeleteTrack()
{
    QListWidgetItem *lwiten = m_vectorListW->value(realTabPosition)->item(m_contextMenuItem->retIndexItem());
    m_vectorStringList->value(realTabPosition)->removeAt(m_contextMenuItem->retIndexItem());
    delete lwiten;
}

void TrackListMeneger::slotOpenAtFileMeneger(int index)
{
    QProcess *process = new QProcess(this);
    process->start("explorer");
}

void TrackListMeneger::slotSort()
{
    m_vectorListW->value(realTabPosition)->sortItems(Qt::DescendingOrder);
}

void TrackListMeneger::slotShowAutorInfo(int index)
{
    int endSerarchString = m_vectorListW->value(realTabPosition)->item(index)->text().indexOf("-");
    QString autor(m_vectorListW->value(realTabPosition)->item(index)->text().mid(0, endSerarchString));
    ArtistInfoWiki *artistWiki = new ArtistInfoWiki(autor, this);
    //connect(artistWiki, &ArtistInfoWiki::destroyed, [=]() {delete artistWiki; });
    artistWiki->show();
    artistWiki->get();


}

void TrackListMeneger::slotRemoveTabWidgetElement(int index)
{
    m_pTabWudget->removeTab(index);
    delete m_vectorListW->value(index);
    delete m_vectorListName->value(index);
    delete m_vectorStringList->value(index);
    m_vectorListW->remove(index);
    m_vectorListName->remove(index);
    m_vectorStringList->remove(index);
    m_realPosition--; m_realSizeVector--;
}

void TrackListMeneger::slotRenameTabWidgetElement(int index)
{
    DialogRenamePlaylist *dialog = new DialogRenamePlaylist(m_pTabWudget, index, this);
    dialog->exec();
}

void TrackListMeneger::slotSwapPlaylist(int a, int b)
{
    MyQListWidget *lw = m_vectorListW->value(a);
    m_vectorListW->operator [](a) = m_vectorListW->operator [](b);
    m_vectorListW->operator [](b) = lw;

    QString *str = m_vectorListName->value(a);
    m_vectorListName->operator [](a) = m_vectorListName->operator [](b);
    m_vectorListName->operator [](b) = str;

    QStringList *sList = m_vectorStringList->value(a);
    m_vectorStringList->operator [](a) = m_vectorStringList->operator [](b);
    m_vectorStringList->operator [](b) = sList;

}
