#ifndef XMLPLAYLISTMENEGER_H
#define XMLPLAYLISTMENEGER_H

#include <QObject>

class XMLPlaylistMeneger : public QObject
{
    Q_OBJECT
public:
    explicit XMLPlaylistMeneger(QObject *parent = 0);
    ~XMLPlaylistMeneger();

    class Reader : public QObject
    {
        Reader(QString file, QObject *parent = 0);
        ~Reader();
    };

    class Writer : public QObject
    {

        Writer(QString file, QObject *parent = 0);
        ~Writer();
    };

signals:

public slots:
};

#endif // XMLPLAYLISTMENEGER_H
