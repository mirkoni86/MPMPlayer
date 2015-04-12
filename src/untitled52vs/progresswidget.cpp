#include "progresswidget.h"

ProgressWidget::ProgressWidget(Qt::Orientation orentation, QWidget *parent) : QSlider(orentation, parent)
{
    setOrientation(orentation);
}

ProgressWidget::~ProgressWidget()
{

}

