#ifndef CONTEXTMENUGLOBAL_H
#define CONTEXTMENUGLOBAL_H

#include <QWidget>
#include <QMenu>
#include <QDebug>

class ContextMenuGlobal : public QMenu
{
    Q_OBJECT
public:
    ContextMenuGlobal(QWidget *parent);
    ~ContextMenuGlobal();
signals:
    void signalSetting();
    void signalPlayPause();
    void signalStop();
private:
    QAction *m_settings;
    QAction *m_playPause;
    QAction *m_stop;
};

#endif // CONTEXTMENUGLOBAL_H
