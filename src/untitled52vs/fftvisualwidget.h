#ifndef FFTVISUALWIDGET_H
#define FFTVISUALWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
namespace Ui {
class FFTVisualWidget;
}

class FFTVisualWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FFTVisualWidget(QWidget *parent = 0);
    ~FFTVisualWidget();
public slots:
    void setData(const QVector<unsigned short> &data);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    Ui::FFTVisualWidget *ui;
    static const int MAX_DATA = 256;
    QPolygonF m_polygon;
    QVector<unsigned short> m_data;
    QPainter *m_painter;
    QPoint m_pointXY0[MAX_DATA];
    QPoint m_pointXY1[MAX_DATA];
};

#endif // FFTVISUALWIDGET_H
