#ifndef FILEINFODIALOG_H
#define FILEINFODIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QDateTime>
#include <QDebug>

namespace Ui {
class FileInfoDialog;
}

class FileInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileInfoDialog(QString adress, QWidget *parent = 0);
    ~FileInfoDialog();
private slots:
    void metaDataExtractor(QMediaPlayer::MediaStatus status);
private:
    Ui::FileInfoDialog *ui;
    QFileInfo *fileInfo;
    QMediaPlayer *mediaPlayer;
};

#endif // FILEINFODIALOG_H
