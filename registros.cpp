#include "registros.h"
#include "ui_registros.h"

registros::registros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registros)
{
    ui->setupUi(this);
}

void registros::Operate(QString file2){
    QFile file(file2);
    QStringList strings;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int cont=0;
        QTextStream in(&file);
        while (!in.atEnd()) {
            if(cont!=0){
            strings += in.readLine().split(" ");


            }//fin del if

            if(in.readLine().contains('*')){
                   break;
            }//fin del if
            cont++;
        }//fin del while
    }//fin del if

}//fin del metodo

registros::~registros()
{
    delete ui;
}
