#include "windowplaylist.h"
#include "ui_windowplaylist.h"

WindowPlaylist::WindowPlaylist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowPlaylist)
{
    ui->setupUi(this);
}

WindowPlaylist::~WindowPlaylist()
{
    delete ui;
}

void WindowPlaylist::addPlaylist(QWidget *widget, QString playlist)
{
    ui->tabWidget->addTab(widget, playlist);
}
