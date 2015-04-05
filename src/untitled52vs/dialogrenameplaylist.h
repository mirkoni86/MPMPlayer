#ifndef DIALOGRENAMEPLAYLIST_H
#define DIALOGRENAMEPLAYLIST_H

#include <QWidget>
#include <QDialog>
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class DialogRenamePlaylist;
}

class DialogRenamePlaylist : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRenamePlaylist(QTabWidget *tw, int index,QWidget *parent = 0);
    ~DialogRenamePlaylist();
public slots:
    void slotRename();
private:
    Ui::DialogRenamePlaylist *ui;
    QTabWidget *tabWidget;
    int indexTab;

};

#endif // DIALOGRENAMEPLAYLIST_H
