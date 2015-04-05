#include "bufferengwindow.h"
#include "ui_bufferengwindow.h"

BufferengWindow::BufferengWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BufferengWindow)
{
    ui->setupUi(this);
}

BufferengWindow::~BufferengWindow()
{
    delete ui;
}
