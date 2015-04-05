#ifndef CONTEXTMENUOPENFILE_H
#define CONTEXTMENUOPENFILE_H

#include <QWidget>
#include <QMenu>
#include <QDebug>

class ContextMenuOpenFile : public QMenu
{
    Q_OBJECT
public:
    explicit ContextMenuOpenFile(QWidget *parent = 0);

signals:
    void signalOpenFile();
    void signalOpenFolder();
    void signalOpenVkontakte();
    void signalOpenUrl();
public slots:

};

#endif // CONTEXTMENUOPENFILE_H
