#include "buscar.h"
#include "ui_buscar.h"



buscar::buscar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buscar)
{
    ui->setupUi(this);

}

buscar::~buscar()
{
    delete ui;
}

void buscar::on_pushButton_clicked()
{


    ui->comboarchivos_buscar->clear();
    for(int y=0;y<ui->tablaBusqueda->rowCount();y++)
        ui->tablaBusqueda->removeRow(0);
    for(int y=0;y<ui->tablaBusqueda->columnCount();y++)
        ui->tablaBusqueda->removeColumn(0);

    QFile file("archivoscreados.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream in(&file);
        while (!in.atEnd()) {
        QString archivo;
        archivo=in.readLine();
        ui->comboarchivos_buscar->addItem((archivo));
    }//fin del while
}//fin del if
}



void buscar::on_pushButton_2_clicked()
{

    ui->tablaBusqueda->setRowCount(0);

    ui->tablaBusqueda->setColumnCount(0);

    QString linea;
    QStringList data;
    QStringList data_size;
    QStringList data_name;
    QString selected=ui->comboarchivos_buscar->currentText();
    QFile file((selected));
    int pos=0;
    int index=ui->combo_estructura->currentIndex();
    int cont=0;
    bool bandera=false;
    bool bandera2=false;
    QString parametro=ui->termino->text();
    QString substring;
    int acu=0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream in(&file);
        while (!in.atEnd()) {

            linea=in.readLine();
            if(bandera2){
             if(linea.contains(parametro)){
                pos=0;
                 ui->tablaBusqueda->setHorizontalHeaderLabels(data_name);
                for(int i=0;i<index;i++){
                    pos+=data_size[i].toInt();
                }//fin del for
                substring=linea.midRef(pos,data_size[index].toInt()).toString();



                if(substring.trimmed()==parametro){

                    ui->tablaBusqueda->insertRow((ui->tablaBusqueda->rowCount()));
                            for(int i=0;i<data_name.length();i++){
                                substring=linea.midRef(acu,data_size[i].toInt()).toString();
                                   ui->tablaBusqueda->setItem(ui->tablaBusqueda->rowCount()-1,i,new QTableWidgetItem(substring.trimmed()));
                                   acu+=data_size[i].toInt();
                            }//fin del for
                            cont++;
                }//fin del if para imprimir la tabla
            }//fin del if de comprobacion de que el parametro se encuentra la linea

            }//fin del if

            if(linea.contains("|")==false&&bandera==false){
               data=linea.split(" ");
               data_name.append(data[0]);
               data_size.append(data[2]);
               ui->tablaBusqueda->insertColumn(ui->tablaBusqueda->columnCount());
            }//fin del if
            if(linea.contains("|")){
                bandera=true;
                ui->combo_estructura->addItems(data_name);
            }//fin del if
            if(linea.contains("$")){
                bandera2=true;

            }//fin del if



cont++;
        }//fin del while
    }//fin del if

}

void buscar::on_comboarchivos_buscar_activated(const QString &arg1)
{

    ui->combo_estructura->clear();

    ui->tablaBusqueda->setRowCount(0);

    ui->tablaBusqueda->setColumnCount(0);


    QString selected=ui->comboarchivos_buscar->currentText();
    QFile file((selected));
    QString busqueda=ui->termino->text();
    QString linea="";
    bool bandera=false;

    QStringList data;
    QStringList data_size;
    QStringList data_name;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream in(&file);
        while (!in.atEnd()) {
            linea=in.readLine();

            if(linea.contains("|")==false&&bandera==false){
                data=linea.split(" ");
                data_name.append(data[0]);
                data_size.append(data[2]);
            }//fin del if
            if(linea.contains("|")){
                bandera=true;
                ui->combo_estructura->addItems(data_name);
            }//fin del if
        }//fin del while
    }//fin del if
}//fin del metodo
