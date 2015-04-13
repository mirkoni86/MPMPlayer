#include "xmlplaylistmeneger.h"

XMLPlaylistMeneger::XMLPlaylistMeneger(QObject *parent) : QObject(parent)
{

}

XMLPlaylistMeneger::~XMLPlaylistMeneger()
{

}

//---------------------------------------------------------------------------------------------------------
//Реализация Reader
XMLPlaylistMeneger::Reader::Reader(QIODevice *device) : QXmlStreamReader(device)
{

}

XMLPlaylistMeneger::Reader::~Reader()
{

}
//-----------------------------------------------------------------------------------------------------------
//Реализация Writer

XMLPlaylistMeneger::Writer::Writer(QIODevice *device) : QXmlStreamWriter(device)
{

}

XMLPlaylistMeneger::Writer::~Writer()
{

}
