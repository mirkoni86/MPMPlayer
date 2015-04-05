#include "dialogdeleteplaylist.h"
#include "ui_dialogdeleteplaylist.h"

DialogDeletePlaylist::DialogDeletePlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogDeletePlaylist)
{
    ui->setupUi(this);
}

DialogDeletePlaylist::~DialogDeletePlaylist()
{
    delete ui;
}
