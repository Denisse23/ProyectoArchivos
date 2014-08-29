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

void compactar::on_combo_compactar_activated(const QString &arg1)
{

}

void compactar::on_pushButton_2_clicked()
{
        QString linea="";
        QFile tmp("temporal.txt");
        tmp.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream out(&tmp);
        QString selected=ui->combo_compactar->currentText();
        QFile file(selected);
        bool bandera=false;
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
               QTextStream in(&file);

            while (!in.atEnd()) {
               linea=in.readLine();
              //linea[0]=="Ø";
               if(linea[0]=='*'&&bandera==false){
                   bandera=true;
               }//fin del if
                if((linea[0]!='*')){
                            out<<linea+"\n";
                }//fin del if
            }//fin del while
                if(bandera){
                    file.remove();
                    tmp.rename(selected);
                    tmp.close();
                }//fin del if
                else{
                    tmp.close();
                    tmp.remove();
                }//fin del else

        }//fin del if
}

