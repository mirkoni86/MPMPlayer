#ifndef MYQLISTWIDGET_H
#define MYQLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
class MyQListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyQListWidget(QWidget *parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);

signals:

public slots:

private:
    void startDragSwap(QPoint point);
    QPoint m_ptDragPos;
    int distance;
};

#endif // MYQLISTWIDGET_H
