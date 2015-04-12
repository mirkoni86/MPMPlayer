#include "dialogrenameplaylist.h"
#include "ui_dialogrenameplaylist.h"

DialogRenamePlaylist::DialogRenamePlaylist(QTabWidget *tw, int index, QWidget *parent) :
    QDialog(parent),indexTab(index), tabWidget(tw),
    ui(new Ui::DialogRenamePlaylist)
{
    ui->setupUi(this);
    name = "";
    setWindowTitle(tr("Имя плэлиста"));
    connect(ui->pushButtonRename, SIGNAL(clicked()), SLOT(slotRename()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), SLOT(close()));
}

DialogRenamePlaylist::~DialogRenamePlaylist()
{
    delete ui;
}

QString DialogRenamePlaylist::newName()
{
    return name;
}

void DialogRenamePlaylist::slotRename()
{
    for(int i = 0; i < tabWidget->count(); ++i)
        if(tabWidget->tabText(i) == ui->lineEdit->text())
        {
            QMessageBox::warning(this, tr("Внимание"), tr("Плэйлист с таким именем уже существует"));
            return;
        }
    //tabWidget->setTabText(indexTab, ui->lineEdit->text());
    name =  ui->lineEdit->text();
    close();
}
