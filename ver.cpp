#include "ver.h"
#include "ui_ver.h"

ver::ver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ver)
{
    ui->setupUi(this);
}

ver::~ver()
{
    delete ui;
}

void ver::on_pushButton_clicked()
{
    for(int i=ui->tabla_ver->rowCount()-1;i>=0;i--)
        ui->tabla_ver->removeRow(i);

    ui->comboarchivos_ver->clear();
    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboarchivos_ver->addItem(QString::fromStdString(archivo));
    }

    camposa.clear();
    ui->comboarchivos_ver->removeItem(ui->comboarchivos_ver->count()-1);
}

void ver::on_comboarchivos_ver_activated(const QString &arg1)
{
    ui->tabla_ver->setEditTriggers(false);
    for(int i=ui->tabla_ver->rowCount()-1;i>=0;i--)
        ui->tabla_ver->removeRow(i);

    camposa.clear();
    QFile file (ui->comboarchivos_ver->currentText());
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
            if(divisiones[3]=="Sí"){
                lla=true;
            }
            camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));

       }

     for(int i=0;i<camposa.count();i++ ){
         ui->tabla_ver->insertRow(i);
         ui->tabla_ver->setItem(i,0,new QTableWidgetItem(camposa[i].getNombre()));
         ui->tabla_ver->setItem(i,1,new QTableWidgetItem(camposa[i].getTipo()));
         ui->tabla_ver->setItem(i,2,new QTableWidgetItem(QString::number(camposa[i].getTamano())));
         if(camposa[i].getEsLlave())
             ui->tabla_ver->setItem(i,3,new QTableWidgetItem("Sí"));
         else
            ui->tabla_ver->setItem(i,3,new QTableWidgetItem("No"));
     }
}
