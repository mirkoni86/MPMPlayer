#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class SettingManager;
}

class SettingManager : public QDialog
{
    Q_OBJECT

public:
    explicit SettingManager(QWidget *parent = 0);
    ~SettingManager();

private:
    Ui::SettingManager *ui;
};

#endif // SETTINGMANAGER_H
