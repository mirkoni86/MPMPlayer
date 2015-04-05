#include "myid3tegextractor.h"
#include <iostream>
#include <string>

MyId3TegExtractor::MyId3TegExtractor(const QString str, QObject *parent) : QObject(parent)
{

    audioFiile = new QFile(str);

        if(!audioFiile->open(QIODevice::ReadOnly))
           QMessageBox::critical(0, QWidget::tr("Ошибка"), QWidget::tr("Не удалось открыть файл для чтения метаднных"));
        else
        {
            byteArrAudioFile = new QByteArray(audioFiile->readAll());
            searchTypeID3();
        }

}

void MyId3TegExtractor::searchTypeID3()
{
    QString strID3v1, strID3v2;
    for(int i = 0;  i  < 3; ++i)
    {
       strID3v1.append(byteArrAudioFile->at(byteArrAudioFile->size() - 128 + i));
       strID3v2.append(byteArrAudioFile->at(i));
    }

    if(strID3v2 == "ID3")
    {
        extractorID3v2();
    }
    if(strID3v1 == "TAG")
    {
        ID3v1.okID3v1 = true;
        extractorID3v1();
    }
    audioFiile->close();
    delete audioFiile;
    delete byteArrAudioFile;
}


void MyId3TegExtractor::extractorID3v1()
{
    //--------------------------------------------------------------------------------------------------
    //ID3v1 занимает 128 байт в конце файла
    //  3 байт - загаловок "TAG";
    //30 байт - название трэка;      30 байт - исполнитель;
    //30 байт - альбом;                    4 байт  - год;
    //28 байт - комментарий;           1 байт - флаг номера трэка;
    //  1 байт - номер трэка;            1 байт - индекс жанра;

                  int lenNameTrack =             byteArrAudioFile->size() - 128 + 3,
                       lenAutorTrack =             byteArrAudioFile->size() - 128 + 3 + 30,
                       lenAlbumTrack =            byteArrAudioFile->size() - 128 + 3 + 30 + 30,
                       lenYearTrack =               byteArrAudioFile->size() - 128 + 3 + 30 + 30 + 30,
                       lenCommentTrack =      byteArrAudioFile->size() - 128 + 3 + 30 + 30 + 30 + 4,
                       lenFlagNumberTrack =   byteArrAudioFile->size() - 128 + 3 + 30 + 30 + 30 + 4 + 28,
                       lenNumberTrack =         byteArrAudioFile->size() - 128 + 3 + 30 + 30 + 30 + 4 + 28 + 1,
                       lenIdGenreTrack =         byteArrAudioFile->size() - 128 + 3 + 30 + 30 + 30 + 4 + 28 + 1 + 1;

                  for(int i = byteArrAudioFile->size() - 128+3; i <= byteArrAudioFile->size(); i++)
                  {
                      if(i == lenAutorTrack) //Названние трэка
                          for(int j = lenNameTrack, k = 0;   j < lenAutorTrack; ++j)
                          {
                              if( (int) byteArrAudioFile->at(j) == 0)
                                  break;
                              if( ((int) byteArrAudioFile->at(j)) < 0 )
                                  ID3v1.title.append( toUnicod( (int) byteArrAudioFile->at(j) ) );
                              else ID3v1.title.append(  byteArrAudioFile->at(j) );
                          }
                      if(i == lenAlbumTrack) //Исполнитель
                          for(int j = lenAutorTrack; j < lenAlbumTrack; ++j)
                          {
                              if( (int) byteArrAudioFile->at(j) == 0)
                                  break;
                              if( ((int) byteArrAudioFile->at(j)) < 0 )
                                  ID3v1.autor.append( toUnicod( (int) byteArrAudioFile->at(j) ) );
                              else ID3v1.autor.append(  byteArrAudioFile->at(j) );
                          }
                      if(i == lenYearTrack) //Альбом
                          for(int j = lenAlbumTrack; j < lenYearTrack; ++j)
                          {
                              if( (int) byteArrAudioFile->at(j) == 0)
                                  break;
                              if( ((int) byteArrAudioFile->at(j)) < 0 )
                                  ID3v1.album.append( toUnicod( (int) byteArrAudioFile->at(j) ) );
                              else ID3v1.album.append(  byteArrAudioFile->at(j) );
                          }
                      if(i == lenCommentTrack) //Год
                          for(int j = lenYearTrack; j < lenCommentTrack; ++j)
                          {
                              if( (int) byteArrAudioFile->at(j) == 0)
                                  break;
                              ID3v1.year.append(byteArrAudioFile->at(j));
                          }
                      if(i == lenFlagNumberTrack) //Комментарий
                          for(int j = lenCommentTrack; j < lenFlagNumberTrack; ++j)
                          {
                              if( (int) byteArrAudioFile->at(j) == 0)
                                  break;
                              if( ((int) byteArrAudioFile->at(j)) < 0 )
                                  ID3v1.comment.append( toUnicod( (int) byteArrAudioFile->at(j) ) );
                              else ID3v1.comment.append(  byteArrAudioFile->at(j) );
                          }
                      if(i == lenNumberTrack) //Если есть номер трэка то установлен нулевой байт
                          for(int j = lenFlagNumberTrack; j < lenNumberTrack; ++j)
                          {
                              if( (int) byteArrAudioFile->at(j) == 0)
                                  break;
                              ID3v1.flagNumberTrack.append(byteArrAudioFile->at(j));
                          }
                      if(i == lenIdGenreTrack) //Номер трэка
                          for(int j = lenNumberTrack; j < lenIdGenreTrack; ++j)
                          {
                              if( (int) byteArrAudioFile->at(j) == 0)
                                  break;
                              ID3v1.numberTrack.append(byteArrAudioFile->at(j));
                          }
                      if(i == lenIdGenreTrack + 1) //Индетификатор жанра
                      {
                          for(int j = lenIdGenreTrack; j <= lenIdGenreTrack; ++j)
                          {
                              if( (int) byteArrAudioFile->at(j) == 0)
                                  break;
                              ID3v1.genre.append( QString::number( (int) byteArrAudioFile->at(j)));
                          }
                          ID3v1.genre.append(genreList(ID3v1.genre.toInt()));
                      }
                  }
}

void MyId3TegExtractor::extractorID3v2()
{
    QString titleFreme[] =
    {
        "AENC",     "APIC",     "COMM",     "COMR",     "ENCR",     "EQUA",
        "ETCO",     "GEOB",   "GRID",       "IPLS",       "LINK",      "MCDI",
        "MLLT",      "OWNE",  "PRIV",        "PCNT",      "POPM",     "POSS",
        "RBUF",     "RVAD",   "RVRB",       "SYLT",       "SYTC",      "TALB",
        "TBPM",     "TCOM",   "TCON",      "TCOP",      "TDAT",       "TDLY",
        "TENC",     "TEXT",    "TFLT",        "TIME",       "TIT1",        "TIT2",
        "TIT3",      "TKEY",    "TLAN",       "TLEN",       "TOAL",       "TOFN",
        "TOLY",     "TOPE",    "TORY",       "TOWN",      "TPE1",       "TPE2",
        "TPE3",     "TPE4",    "TPOS",       "TPUB",       "TRCK",       "TRDA",
        "TRSN",    "TRSO",   "TSIZ",        "TSRC",       "TSSE",       "TYER",
        "TXXX",    "UFID",    "USER",       "USLT",       "WCOM",     "WCOP",
        "WOAF",   "WOAR",  "WOAS",      "WORS",     "WPAY",      "WPUB",
        "WXXX"
    };

    QString sizeID3;
//    for(int i = 0; i <= 1024; ++i)
//        if(byteArrAudioFile->at(i)    == 'T' &&
//           byteArrAudioFile->at(i+1) == 'I' &&
//           byteArrAudioFile->at(i+2) == 'T' &&
//           byteArrAudioFile->at(i+3) == '2')
//        {
//            for(int j = i+13; ; ++j)
//            {
//                if((byteArrAudioFile->at(j))      == 'T' &&
//                    (byteArrAudioFile->at(j+1)) == 'P' &&
//                    (byteArrAudioFile->at(j+2)) == 'E' &&
//                    (byteArrAudioFile->at(j+3)) == '1')
//                    break;
//                std::cout <<  byteArrAudioFile->at(j);
//            }
//        }
    int sum = 0;
    for(int i = 6; i <= 9; ++i)
    {
        sum += (int) byteArrAudioFile->at(i);
        qDebug() << "i" << i << ": " << sum;
    }

    qDebug() << "size TEG: " << sum;


}

QString MyId3TegExtractor::genreList(int nIndex)
{
    ID3v1.genre.clear();
    static const int genresSize = 148;
    static const QString genres[] = {
      "Blues",             "Classic Rock",  "Country",                  "Dance",
      "Disco",              "Funk",             "Grunge",                  "Hip-Hop",
      "Jazz",               "Metal",            "New Age",                 "Oldies",
      "Other",             "Pop",                "R&B",                      "Rap",                 "Reggae",
      "Rock",               "Techno",           "Industrial",              "Alternative",
      "Ska",                "Death Metal",   "Pranks",                   "Soundtrack",
      "Euro-Techno",    "Ambient",         "Trip-Hop",                "Vocal",
      "Jazz+Funk",      "Fusion",           "Trance",                   "Classical",
      "Instrumental",   "Acid",               "House",                   "Game",
      "Sound Clip",      "Gospel",            "Noise",                    "Alternative Rock",
      "Bass", "Soul",    "Punk",               "Space",
      "Meditative",       "Instrumental Pop", "Instrumental Rock", "Ethnic",
      "Gothic",             "Darkwave",       "Techno-Industrial",   "Electronic",
      "Pop-Folk",          "Eurodance",       "Dream",                  "Southern Rock",
      "Comedy",           "Cult",                "Gangsta",                 "Top 40",           "Christian Rap",
      "Pop/Funk",         "Jungle",             "Native American",    "Cabaret",
      "New Wave",       "Psychedelic",      "Rave",                     "Showtunes",
      "Trailer",             "Lo-Fi",               "Tribal",                     "Acid Punk",
      "Acid Jazz",         "Polka",               "Retro",                     "Musical",
      "Rock & Roll",      "Hard Rock",        "Folk",                       "Folk/Rock",
      "National Folk",   "Swing",              "Fusion",                    "Bebob",
      "Latin",               "Revival",            "Celtic",                     "Bluegrass",
      "Avantgarde",     "Gothic Rock",      "Progressive Rock",     "Psychedelic Rock",
      "Symphonic Rock", "Slow Rock",     "Big Band",                 "Chorus",
      "Easy Listening", "Acoustic",           "Humour",                  "Speech",
      "Chanson",          "Opera",              "Chamber Music",       "Sonata",
      "Symphony",       "Booty Bass",       "Primus",                   "Porn Groove",
      "Satire",             "Slow Jam",         "Club",                       "Tango",
      "Samba",            "Folklore",           "Ballad",                     "Power Ballad",
      "Rhythmic Soul", "Freestyle",         "Duet",                       "Punk Rock",
      "Drum Solo",       "A Cappella",       "Euro-House",            "Dance Hall",
      "Goa",                "Drum & Bass",    "Club-House",            "Hardcore",
      "Terror",             "Indie",                "BritPop",                  "Negerpunk",
      "Polsk Punk",      "Beat",                 "Christian Gangsta Rap",
      "Heavy Metal",    "Black Metal",       "Crossover",              "Contemporary Christian",
      "Christian Rock", "Merengue",         "Salsa",                     "Thrash Metal",
      "Anime",             "Jpop",                 "Synthpop"
    };

        for(int i = 0; i < genresSize; ++i)
            if(nIndex  == i)
                return genres[i];

    return QString("");
}

QString MyId3TegExtractor::toUnicod(int latter)
{
    switch (latter) {
    //--------------------------------------------------------------------
    //А-Я
    case -64:
        return QString("А");
    case -63:
        return QString("Б");
    case - 62:
        return QString("В");
    case -61:
        return QString("Г");
    case -60:
        return QString("Д");
    case -59:
        return QString("Е");
    case -58:
        return QString("Ж");
     case - 57:
        return QString("З");
     case - 56:
        return QString("И");
    case - 55:
       return QString("Й");
    case -54:
       return QString("К");
    case - 53:
       return QString("Л");
    case -52:
       return QString("М");
    case - 51:
       return QString("Н");
    case -50:
       return QString("О");
    case -49:
       return QString("П");
    case -48:
       return QString("Р");
    case -47:
       return QString("С");
    case -46:
       return QString("Т");
    case -45:
       return QString("У");
    case -44:
       return QString("Ф");
    case -43:
       return QString("Х");
    case -42:
       return QString("Ц");
    case -41:
       return QString("Ч");
    case -40:
       return QString("Ш");
    case -39:
       return QString("Щ");
    case -38:
       return QString("Ъ");
    case -37:
       return QString("Ы");
    case -36:
       return QString("Ь");
    case -35:
       return QString("Э");
    case -34:
       return QString("Ю");
    case -33:
       return QString("Я");
    //---------------------------------------------------------------------------
   //а-я
    case -32:
       return QString("а");
    case -31:
       return QString("б");
    case -30:
       return QString("в");
    case -29:
       return QString("г");
    case -28:
       return QString("д");
    case -27:
       return QString("е");
    case -26:
       return QString("ж");
    case -25:
       return QString("з");
    case -24:
       return QString("и");
    case -23:
       return QString("й");
    case -22:
       return QString("к");
    case -21:
       return QString("л");
    case -20:
       return QString("м");
    case -19:
       return QString("н");
    case -18:
       return QString("о");
    case -17:
       return QString("п");
    case -16:
       return QString("р");
    case -15:
       return QString("с");
    case -14:
       return QString("т");
    case -13:
       return QString("у");
    case -12:
       return QString("ф");
    case -11:
       return QString("х");
    case -10:
       return QString("ц");
    case -9:
       return QString("ч");
    case -8:
       return QString("ш");
    case -7:
       return QString("щ");
    case -6:
       return QString("ъ");
    case -5:
       return QString("ы");
    case -4:
       return QString("ь");
    case -3:
       return QString("э");
    case -2:
       return QString("ю");
    case -1:
       return QString("я");

    }
    return QString((char) latter);

}
