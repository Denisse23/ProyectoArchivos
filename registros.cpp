#include "registros.h"
#include "ui_registros.h"

registros::registros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registros)
{
    ui->setupUi(this);
}


void registros::setFile(QString x){
    mainfile.setFileName(x);
}//fin del metodo

void registros::Operate(){



    QStringList strings;
    if (mainfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int cont=0;
        QTextStream in(&mainfile);
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
