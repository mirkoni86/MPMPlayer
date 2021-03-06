#ifndef MYCONDEXTMENU_H
#define MYCONDEXTMENU_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QObject>
#include "contextmenuopenfile.h"
class MyCondextMenu : public QMenu
{

    Q_OBJECT
public:
   MyCondextMenu(QWidget *parent = 0);
   ~MyCondextMenu();
    void SetFileAdress(QString adress);
    void setIndexItem(int index);
    int retIndexItem();
signals:
    void signalAddFileAddFileLocal();
    void signalAddFileAddFileLocalFolder();
    void signalAddFileAddFileVk();
    void signalAddFileAddFileNetwork();

    void signalFileInfo(int index);
    void signalDeleteTrack();
    void signalOpenAtFileMeneger(int itemIndex);
    void signalSort();
    void signalInfoAutor(int);
private  slots:
    void slotFileInfo();
    void slotDeleteTrack();
    void slotOpenAtFileMeneger();
    void slotSort();
    void slotInfoAutor();
private:
    QString fileAdress;
    int m_ItemIndex;
};

#endif // MYCONDEXTMENU_H
