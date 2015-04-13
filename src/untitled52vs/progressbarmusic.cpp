#include "progressbarmusic.h"

ProgressBarMusic::ProgressBarMusic(QWidget *parent) : QSlider(parent)
{

}

ProgressBarMusic::~ProgressBarMusic()
{

}

void ProgressBarMusic::mousePressEvent(QMouseEvent *event)
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    int left = 0;
    int right = width();

    int newPosition = QStyle::sliderValueFromPosition(minimum(), maximum(), event->pos().x() - left, right - left, opt.upsideDown);
    //setSliderPosition(newPosition);
    emit sliderMoved(newPosition);
}

