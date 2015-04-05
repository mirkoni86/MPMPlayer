#ifndef WINDOWPLAYLIST_H
#define WINDOWPLAYLIST_H

#include <QMainWindow>

namespace Ui {
class WindowPlaylist;
}

class WindowPlaylist : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowPlaylist(QWidget *parent = 0);
    ~WindowPlaylist();
public slots:
    void addPlaylist(QWidget *widget, QString playlist);
private:
    Ui::WindowPlaylist *ui;

};

#endif // WINDOWPLAYLIST_H
