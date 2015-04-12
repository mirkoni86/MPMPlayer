#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H
#include <QSlider>
#include <QWidget>
class ProgressWidget : public QSlider
{
    Q_OBJECT
public:
    ProgressWidget(Qt::Orientation orentation, QWidget *parent = 0);
    ~ProgressWidget();
};

#endif // PROGRESSWIDGET_H
