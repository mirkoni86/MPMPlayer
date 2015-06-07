#include "opensource.h"

OpenSource::OpenSource(QObject *parent) : QObject(parent)
{

}

OpenSource::~OpenSource()
{

}

QStringList OpenSource::openLocalFile()
{
    QStringList tempList;
    tempList.append(QFileDialog::getOpenFileNames(0, tr("Open File"), "D:\\Музыка", tr("Audio Files (*.mp3 *.flac *.wav *.wma *.amr *.m4a *.m4r);;All files (*.*)")));
    return tempList;
}

QStringList OpenSource::openLocalFolder()
{
    QString dir = QFileDialog::getExistingDirectory();
    QStringList base;
    findFiles(dir, &base);
    return base;
}

void OpenSource::findFiles(QString d, QStringList *base)
{
    QApplication::processEvents();
    QDir dir(d);
    QStringList fileList =  dir.entryList(QDir::Files) ;
    foreach (QString str,  fileList )
    {
        base->append( dir.absoluteFilePath(str) );
    }
    QStringList dirList = dir.entryList(QDir::Dirs);

    foreach(QString str, dirList)
    {
        if(str == "." || str == "..")
            continue;
        findFiles(dir.absoluteFilePath(str), base);
    }
}

//QStringList OpenSource::openVKontakte()
//{

//}

//QStringList OpenSource::openURL()
//{

//}

