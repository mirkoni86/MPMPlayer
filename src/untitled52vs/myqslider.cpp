#include "myqslider.h"
/*
 * Данный класс компилируется только тогда и только тогда когда файл *.cpp и файл *.h  ноходятся
 * в корне сборки проекта, т.е в корне  "имя проекта - Release" или  в "имя проекта- Debug"
*/
MyQSlider::MyQSlider(QWidget *parent) : QSlider(parent)
{

}

MyQSlider::~MyQSlider()
{

}

void MyQSlider::mousePressEvent(QMouseEvent *event)
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    int left = 0;
    int right = width();


    int newPosition = QStyle::sliderValueFromPosition(minimum(), maximum(), event->pos().x() - left, right - left, opt.upsideDown);
    //setSliderPosition(newPosition);
    emit sliderMoved(newPosition);
}

