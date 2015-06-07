#ifndef DIALOGRENAMEPLAYLIST_H
#define DIALOGRENAMEPLAYLIST_H

#include <QWidget>
#include <QDialog>
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
namespace Ui {
class DialogRenamePlaylist;
}

class DialogRenamePlaylist : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRenamePlaylist(QTabWidget *tw, int index = 0,QWidget *parent = 0);
    ~DialogRenamePlaylist();
    QString newName();
    bool isCancel();
public slots:
    void slotRename();
private slots:
    void slotCancel();
private:
    Ui::DialogRenamePlaylist *ui;
    QTabWidget *tabWidget;
    QString name;
    int indexTab;
    bool cancelflag;

};

#endif // DIALOGRENAMEPLAYLIST_H
