#include "borrar.h"
#include "ui_borrar.h"

borrar::borrar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrar)
{
    ui->setupUi(this);
}

borrar::~borrar()
{
    delete ui;
}
