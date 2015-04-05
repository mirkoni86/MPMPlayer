#ifndef DIALOGDELETEPLAYLIST_H
#define DIALOGDELETEPLAYLIST_H

#include <QWidget>


namespace Ui {
class DialogDeletePlaylist;
}

class DialogDeletePlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit DialogDeletePlaylist(QWidget *parent = 0);
    ~DialogDeletePlaylist();

private:
    Ui::DialogDeletePlaylist *ui;
};

#endif // DIALOGDELETEPLAYLIST_H
