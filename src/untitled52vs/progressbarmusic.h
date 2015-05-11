#ifndef PROGRESSBARMUSIC_H
#define PROGRESSBARMUSIC_H
/*
 * -------------------------------------------------------------
 * TODO
 * -------------------------------------------------------------
 * Данный класс должен заменить собой  MyQSlider
*/

#include <QWidget>
#include <QSlider>
#include <QStyleOptionSlider>
#include <QMouseEvent>

class ProgressBarMusic : public QSlider
{
public:
    ProgressBarMusic(QWidget *parent = 0);
    ~ProgressBarMusic();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // PROGRESSBARMUSIC_H
