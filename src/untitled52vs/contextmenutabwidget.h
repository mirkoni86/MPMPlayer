#ifndef CONTEXTMENUTABWIDGET_H
#define CONTEXTMENUTABWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QTabBar>
class ContextMenuTabWidget : public QMenu
{
    Q_OBJECT
public:
    explicit ContextMenuTabWidget(QTabBar *tabBar, QWidget *parent = 0);
    ~ContextMenuTabWidget();
    int retTabPosition();
signals:
    void signalRemoveTabElement(int index);
    void signalRenameTabElement(int index);
    void signalAddTabElement();
public slots:
    void slotSetIndexClickedTabBar(int index);
    void slotSetTabBarPointer(QTabBar* tb);
private slots:
    void slotRemoveTabElement();
    void slotRanameTabElement();
private:
    int indexClickedTabBar;

    QTabBar* m_pTabBar; //Указатель на таб бар, не знаю для чего нужно, но нужно
};

#endif // CONTEXTMENUTABWIDGET_H
