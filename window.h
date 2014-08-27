#ifndef WINDOW_H
#define WINDOW_H
#include "nuevo.h"
#include "registros.h"
#include <QMainWindow>
#include <QFileDialog>
#include "listar.h"
#include "modificara.h"
#include "borrar.h"
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

    void on_listar_clicked();

    void on_pushButton_clicked();

    void on_borrar_clicked();

private:
    Ui::window *ui;
};

#endif // WINDOW_H
