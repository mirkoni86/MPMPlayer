#include "dialogrenameplaylist.h"
#include "ui_dialogrenameplaylist.h"

DialogRenamePlaylist::DialogRenamePlaylist(QTabWidget *tw, int index, QWidget *parent) :
    QDialog(parent),indexTab(index), tabWidget(tw),
    ui(new Ui::DialogRenamePlaylist)
{
    ui->setupUi(this);
    name = "";
    cancelflag = false;
    ui->lineEdit->setText(QDateTime::currentDateTime().toString("d-MM-yy h-mm-s"));
    setWindowTitle(tr("Имя плэлиста"));
    connect(ui->pushButtonRename, SIGNAL(clicked()), SLOT(slotRename()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), SLOT(slotCancel()));
}

DialogRenamePlaylist::~DialogRenamePlaylist()
{
    delete ui;
}

QString DialogRenamePlaylist::newName()
{
    return name;
}

bool DialogRenamePlaylist::isCancel()
{
    return cancelflag;
}

void DialogRenamePlaylist::slotRename()
{
    for(int i = 0; i < tabWidget->count(); ++i)
        if(tabWidget->tabText(i) == ui->lineEdit->text())
        {
            QMessageBox::warning(this, tr("Внимание"), tr("Плэйлист с таким именем уже существует"));
            return;
        }
    if(!ui->lineEdit->text().size())
        ui->lineEdit->setText(QDateTime::currentDateTime().toString("d-MM-yy h-mm-s"));
    name =  ui->lineEdit->text();
    close();
}

void DialogRenamePlaylist::slotCancel()
{
    cancelflag = true;
    close();
}
