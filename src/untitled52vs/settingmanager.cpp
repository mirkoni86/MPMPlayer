#include "settingmanager.h"
#include "ui_settingmanager.h"

SettingManager::SettingManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingManager)
{
    ui->setupUi(this);



}

SettingManager::~SettingManager()
{
    delete ui;
}
