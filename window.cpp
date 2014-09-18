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

void window::on_pushButton_4_clicked()
{
    reindexar reindexararchivo(this);
    reindexararchivo.setModal(true);
    reindexararchivo.exec();
}

void window::on_pushButton_6_clicked()
{
    cruzar cruzararchivos(this);
    cruzararchivos.setModal(true);
    cruzararchivos.exec();
}

void window::on_pushButton_5_clicked()
{
    exportar exportararchivo(this);
    exportararchivo.setModal(true);
    exportararchivo.exec();
}

void window::on_pushButton_7_clicked()
{
    cruzarlineal cruzarlinealarchivo(this);
    cruzarlinealarchivo.setModal(true);
    cruzarlinealarchivo.exec();
}

void window::on_pushButton_8_clicked()
{
    cruzararbol cruzararbolarchivo(this);
    cruzararbolarchivo.setModal(true);
    cruzararbolarchivo.exec();
}
