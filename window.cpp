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
