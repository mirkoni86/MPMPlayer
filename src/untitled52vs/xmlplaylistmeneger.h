#ifndef XMLPLAYLISTMENEGER_H
#define XMLPLAYLISTMENEGER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class XMLPlaylistMeneger : public QObject
{
    Q_OBJECT
public:
    explicit XMLPlaylistMeneger(QObject *parent = 0);
    ~XMLPlaylistMeneger();

    class Reader : public QXmlStreamReader
    {
    public:
        Reader(QIODevice *device);
        ~Reader();
    };

    class Writer : public QXmlStreamWriter
    {
    public:
        Writer(QIODevice *device);
        ~Writer();
    };

signals:

public slots:
};

#endif // XMLPLAYLISTMENEGER_H
