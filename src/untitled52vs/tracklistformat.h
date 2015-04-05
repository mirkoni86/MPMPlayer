#ifndef TRACKLISTFORMAT_H
#define TRACKLISTFORMAT_H

#include <QWidget>
#include <QMediaPlayer>

namespace Ui {
class TrackListFormat;
}

class TrackListFormat : public QWidget
{
    Q_OBJECT

public:
    explicit TrackListFormat(QString str, QSize sz, QWidget *parent = 0);
    TrackListFormat();
    ~TrackListFormat();

private:
    Ui::TrackListFormat *ui;
    QString *fileAdress;
    QMediaPlayer *mediaPlayer;
};

#endif // TRACKLISTFORMAT_H
