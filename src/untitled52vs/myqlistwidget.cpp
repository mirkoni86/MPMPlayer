#include "myqlistwidget.h"

MyQListWidget::MyQListWidget(QWidget *parent) :
    QListWidget(parent)
{

}

void MyQListWidget::mousePressEvent(QMouseEvent* pe)
{
    if(pe->button() == Qt::LeftButton)
    {
        m_ptDragPos = pe->pos();
    }
    QListWidget::mousePressEvent(pe);
}

void MyQListWidget::mouseMoveEvent(QMouseEvent *pe)
{
    if(pe->buttons() == Qt::LeftButton)
    {
        distance = (pe->pos() - m_ptDragPos).manhattanLength() ;
        if(distance > QApplication::startDragDistance())
        {
            ; // Здесь будет функция для перемещения элемента QListWidget
            qDebug() << pe->pos();
            startDragSwap(pe->pos());
        }
    }
    QListWidget::mousePressEvent(pe);
}

void MyQListWidget::startDragSwap(QPoint point)
{
    if( (point.x() > 0) && (point.y() > 0) )
    {
        qDebug() << "x: " << point.x() << " y: " << point.y();

    }
}
