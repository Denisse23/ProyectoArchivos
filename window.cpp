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

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.txt*)"));
    registros r(this);
    r.setModal(true);
    r.exec();
    r.setFile(fileName);
}
