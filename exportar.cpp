#include "exportar.h"
#include "ui_exportar.h"
#include <QTextCodec>
exportar::exportar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportar)
{
    ui->setupUi(this);
}

exportar::~exportar()
{
    delete ui;
}

void exportar::on_pushButton_clicked()
{
    camposa.clear();
    ui->comboarchivos_exportar->clear();
    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboarchivos_exportar->addItem(QString::fromStdString(archivo));
    }
    ui->comboarchivos_exportar->removeItem(ui->comboarchivos_exportar->count()-1);
}

void exportar::on_pushButton_2_clicked()
{
    if(ui->comboarchivos_exportar->count()>0){
    QString nombre =ui->comboarchivos_exportar->currentText();
    nombre[nombre.length()-4]='x';
    nombre[nombre.length()-3]='m';
    nombre[nombre.length()-2]='l';
    nombre[nombre.length()-1]='\0';
    QFile file1(nombre);
    if (!file1.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
    QTextStream out(&file1);
    char num[5], cod[7];
    num[0]='"',num[1]='1',num[2]='.',num[3]='0',num[4]='"';
    cod[0]='"',cod[1]='U',cod[2]='T',cod[3]='F',cod[4]='-',cod[5]='8',cod[6]='"';
    out<<"<?xml version="+QString::fromStdString(num)+" encoding="+QString::fromStdString(cod)+"?>"<<endl;
    nombre[nombre.length()-1]='p';
    QString nomb;
    for(int i=0;i<nombre.length()-5;i++){
        nomb+=nombre[i];
    }

    out<<"<"+nomb+">"<<endl;
    file.seek(0);
    QTextStream in(&file);
    QString line;
    bool empezar = false;
       while (!in.atEnd()) {
           line = in.readLine();
           if(empezar){
                if(line[0]!='*'){
                    int camino=0;
                    out<<"<"+nomb+">"<<endl;
                   for(int i=0;i<camposa.count();i++){
                       out<<"   ";
                       out<<"<"+camposa[i].getNombre()+">";
                       out<<line.mid(camino,camposa[i].getTamano());
                       out<<"</"+camposa[i].getNombre()+">"<<endl;
                       camino+=camposa[i].getTamano();
                   }
                    out<<"</"+nomb+">"<<endl;
                }
         }
       if(line=="$")
           empezar = true;
  }
  out<<"</"+nomb+">";

  file1.close();
  ui->comboarchivos_exportar->clear();
  }
}

void exportar::on_comboarchivos_exportar_activated(const QString &arg1)
{
    file.close();
    camposa.clear();
    file.setFileName(ui->comboarchivos_exportar->currentText());
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            if(line=="|")
                break;
            QStringList divisiones = line.split(" ");
            bool lla =false;
            if(divisiones[3]=="Sí")
                lla=true;
            camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
    }

}
