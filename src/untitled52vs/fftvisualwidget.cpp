#include "fftvisualwidget.h"
#include "ui_fftvisualwidget.h"

FFTVisualWidget::FFTVisualWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FFTVisualWidget)
{
    ui->setupUi(this);
}

FFTVisualWidget::~FFTVisualWidget()
{
    delete ui;
}

void FFTVisualWidget::setData(const QVector<unsigned short> &data)
{
    if(m_polygon.size())
        m_polygon.clear();
    m_data = data;
    const float CONST_SHORT_POS = 65536 / 4 / ( (!height()) ? 1 : height() ) ; // Константное значение для оптимального расположения точек
                                                                                          // расчитывается путем максмиальное значение data / высоту виджета

    //Ростановка точек
   for(int i = 0; i < MAX_DATA; ++i)
    {
       //qDebug() << m_pointXY0[i].y() << " ";
       m_pointXY0[i].setX(i);
       m_pointXY1[i].setX(i);
       m_pointXY0[i].setY(height() -  static_cast<int>( m_data.at(i)  / CONST_SHORT_POS) );
       m_pointXY1[i].setY(height());
    }

   update();


}

void FFTVisualWidget::paintEvent(QPaintEvent *event)
{
       QPainter painter(this);

       painter.setRenderHint(QPainter::Antialiasing, true);
       painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap,Qt::MiterJoin));
       //painter.drawPolygon(m_polygon);

       const int BEGIN_SELECTION = 127; // Позиция с которой начинается выборка данных
       const int STEP_SELECTION = 6;       //Шаг выборки

       for(int i = BEGIN_SELECTION; i < MAX_DATA; i += STEP_SELECTION )
       {

               if(m_pointXY0[i].y() >= 3 && m_pointXY0[i].y() <= 5 )
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 1 );
               else  if(m_pointXY0[i].y() > 5 && m_pointXY0[i].y() <= 7)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 2 );
               else if(m_pointXY0[i].y() == 8)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) +  4);
               else  if(m_pointXY0[i].y() == 9)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 6);
               else  if(m_pointXY0[i].y() == 10)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 10);
               else  if(m_pointXY0[i].y() == 11)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 16 );
               else  if(m_pointXY0[i].y() == 12)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) +  22);
               else  if(m_pointXY0[i].y() == 13)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 29);
               else  if(m_pointXY0[i].y() == 14)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 36);
               else  if(m_pointXY0[i].y() == 15)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 42);
               else  if(m_pointXY0[i].y() == 16)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 44);
               else  if(m_pointXY0[i].y() > 17)
                   m_pointXY0[i].setY( (m_pointXY0[i].y() ) + 46);

           if(m_pointXY0[i].x() < 0 || m_pointXY0[i].y() < 0 ||
               m_pointXY1[i].x() < 0 || m_pointXY1[i].y() < 0)
               continue;

               m_pointXY0[i].setX(m_pointXY0[i].x() - BEGIN_SELECTION - STEP_SELECTION + 1) ;
               m_pointXY1[i].setX(m_pointXY1[i].x() - BEGIN_SELECTION - STEP_SELECTION + 1);

               QLinearGradient gradient(0, 0, 0, height());
               gradient.setColorAt(1, Qt::green);
               gradient.setColorAt(0.66, Qt::yellow);
               gradient.setColorAt(0, Qt::red);

                painter.setPen(QPen(gradient, 1, Qt::SolidLine, Qt::RoundCap,Qt::MiterJoin));

           painter.drawLine(m_pointXY0[i], m_pointXY1[i]);
           //qDebug() << "i " << i  <<": " << m_pointXY0[i];
       }


}
