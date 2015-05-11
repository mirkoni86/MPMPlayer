#include "contextmenuglobal.h"

ContextMenuGlobal::ContextMenuGlobal(QWidget *parent) : QMenu(parent)
{
    m_settings = new QAction(tr("Настройки"), this);
    m_playPause = new QAction(tr("Вспр./Пауза"), this);
    m_stop = new QAction(tr("Стоп"), this);

    addAction(m_settings);
    addAction(m_playPause);
    addAction(m_stop);

    connect(m_settings, SIGNAL(triggered()), SIGNAL(signalSetting()));
    connect(m_playPause, SIGNAL(triggered()), SIGNAL(signalPlayPause()));
    connect(m_stop, SIGNAL(triggered()), SIGNAL(signalStop()));

}

ContextMenuGlobal::~ContextMenuGlobal()
{

}

