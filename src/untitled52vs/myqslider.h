#ifndef MYQSLIDER_H
#define MYQSLIDER_H
#include <QSlider>
#include <QMouseEvent>
#include <QStyleOptionSlider>
#include <QDebug>
class MyQSlider : public QSlider
{
    Q_OBJECT
public:
    MyQSlider(QWidget *parent = 0);
    ~MyQSlider();
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYQSLIDER_H
