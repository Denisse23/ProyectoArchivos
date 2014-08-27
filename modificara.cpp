#include "modificara.h"
#include "ui_modificara.h"

modificara::modificara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modificara)
{
    ui->setupUi(this);
}

modificara::~modificara()
{
    delete ui;
}
