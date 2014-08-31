#include "compactar.h"
#include "ui_compactar.h"

compactar::compactar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::compactar)
{
    ui->setupUi(this);
}

compactar::~compactar()
{
    delete ui;
}

void compactar::on_pushButton_clicked()
{


    ui->combo_compactar->clear();
    QFile file("archivoscreados.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream in(&file);
        while (!in.atEnd()) {
        QString archivo;
        archivo=in.readLine();
        ui->combo_compactar->addItem((archivo));
    }//fin del while
}//fin del if
}//fin del metodo



void compactar::on_pushButton_2_clicked()
{

        QString linea="";
        QFile tmp("temporal.txt");
        tmp.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream out(&tmp);
        QString selected=ui->combo_compactar->currentText();
        QFile file(selected);
        bool banderahead = false;
        bool bandera = true;
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
               QTextStream in(&file);

            while (!in.atEnd()) {
               linea=in.readLine();
               if(linea[0]!='*'){
                   if(banderahead){
                       if(linea!="-1    "){
                         out<<"-1    \n";
                         banderahead=false;
                       }else{
                         bandera = false;
                         break;
                       }
                   }else{
                      out<<linea+"\n";
                    }
               }//fin del if

               if( linea=="|"){
                      banderahead = true;
                }//fin del if
            }//fin del while
                  if(bandera){
                    file.remove();
                    tmp.rename(selected);
                    tmp.close();
                   }else{
                    tmp.close();
                    tmp.remove();
                   }

        }//fin del if
        ui->combo_compactar->clear();
}

