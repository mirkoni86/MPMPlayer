/*
 * Класс для открытия файлов, папок и прочих ресурсов
 * содржащих музыку
*/
#ifndef OPENSOURCE_H
#define OPENSOURCE_H

#include <QObject>
#include <QStringList>
#include <QFileDialog>
#include <QApplication>

class OpenSource : public QObject
{
    Q_OBJECT
public:
    explicit OpenSource(QObject *parent = 0);
    ~OpenSource();
    static QStringList openLocalFile();
    static QStringList openLocalFolder();
    static QStringList openVKontakte();
    static QStringList openURL();
signals:

public slots:
private:
    static void findFiles(QString d, QStringList *base);
};

#endif // OPENSOURCE_H
