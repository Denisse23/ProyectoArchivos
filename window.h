#ifndef WINDOW_H
#define WINDOW_H
#include "nuevo.h"
#include "registros.h"
#include <QMainWindow>
#include <QFileDialog>


namespace Ui {
class window;
}

class window : public QMainWindow
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();

private slots:
    void on_nuevo_clicked();

    void on_agregar_clicked();

private:
    Ui::window *ui;
};

#endif // WINDOW_H
