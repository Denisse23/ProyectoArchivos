#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);
}

window::~window()
{
    delete ui;
}

void window::on_nuevo_clicked()
{
    nuevo ventananuevo(this);
    ventananuevo.setModal(true);
    ventananuevo.exec();
}

void window::on_agregar_clicked()
{

    registros ventanaregistros(this);
    ventanaregistros.setModal(true);
    ventanaregistros.exec();

}

void window::on_listar_clicked()
{
    listar listaregistros(this);
    listaregistros.setModal(true);
    listaregistros.exec();
}

void window::on_pushButton_clicked()
{
    modificara modificararchivo(this);
    modificararchivo.setModal(true);
    modificararchivo.exec();
}

void window::on_borrar_clicked()
{
    borrar borrarregistros(this);
    borrarregistros.setModal(true);
    borrarregistros.exec();
}

void window::on_buscar_clicked()
{
    buscar buscarregistros(this);
    buscarregistros.setModal(true);
    buscarregistros.exec();
}

void window::on_pushButton_2_clicked()
{
    compactar compactararchivo(this);
    compactararchivo.setModal(true);
    compactararchivo.exec();
}

void window::on_pushButton_3_clicked()
{
    ver verarchivo(this);
    verarchivo.setModal(true);
    verarchivo.exec();
}
