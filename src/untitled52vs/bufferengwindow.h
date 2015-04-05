#ifndef BUFFERENGWINDOW_H
#define BUFFERENGWINDOW_H

#include <QDialog>

namespace Ui {
class BufferengWindow;
}

class BufferengWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BufferengWindow(QWidget *parent = 0);
    ~BufferengWindow();

private:
    Ui::BufferengWindow *ui;
};

#endif // BUFFERENGWINDOW_H
