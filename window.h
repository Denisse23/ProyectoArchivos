#ifndef WINDOW_H
#define WINDOW_H
#include "nuevo.h"
#include "registros.h"
#include <QMainWindow>
#include <QFileDialog>
#include "listar.h"
#include "modificara.h"
#include "borrar.h"
#include "buscar.h"
#include "compactar.h"
#include "ver.h"
#include "reindexar.h"
#include "cruzar.h"
#include "exportar.h"
#include "cruzarlineal.h"
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

    void on_buscar_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::window *ui;
};

#endif // WINDOW_H
