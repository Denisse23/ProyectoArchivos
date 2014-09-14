#include "listar.h"
#include "ui_listar.h"

listar::listar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar)
{
    ui->setupUi(this);
}

listar::~listar()
{
    delete ui;
}

void listar::on_pushButton_clicked()
{
    camposa.clear();

    for(int i=ui->comboarchivos_listar->count()-1;i>=0;i--)
        ui->comboarchivos_listar->removeItem(i);
    for(int i=ui->tablaregistros_listar->rowCount()-1;i>=0;i--)
        ui->tablaregistros_listar->removeRow(i);
    for(int i=ui->tablaregistros_listar->columnCount();i>=0;i--)
        ui->tablaregistros_listar->removeColumn(i);
    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboarchivos_listar->addItem(QString::fromStdString(archivo));
    }
    verificar.close();
    ui->comboarchivos_listar->removeItem(ui->comboarchivos_listar->count()-1);
}

void listar::on_comboarchivos_listar_activated(const QString &arg1)
{
    camposa.clear();
    ui->tablaregistros_listar->setEditTriggers(false);
    for(int i=ui->tablaregistros_listar->rowCount()-1;i>=0;i--)
        ui->tablaregistros_listar->removeRow(i);
    for(int i=ui->tablaregistros_listar->columnCount();i>=0;i--)
        ui->tablaregistros_listar->removeColumn(i);
    QFile file (ui->comboarchivos_listar->currentText());
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
        for(int i=0;i<camposa.count();i++){
            ui->tablaregistros_listar->insertColumn(i);
            if(camposa[i].getNombre().length()>camposa[i].getTamano())
                ui->tablaregistros_listar->setColumnWidth(i,camposa[i].getNombre().length()*10);
            else
                ui->tablaregistros_listar->setColumnWidth(i,camposa[i].getTamano()*20);
            ui->tablaregistros_listar->setHorizontalHeaderItem(i,new QTableWidgetItem(camposa[i].getNombre()));
        }

            bool empezar = false;
            while (!in.atEnd()) {
                line = in.readLine();
                if(empezar){
                    if(line[0]!='*'){
                        int rowc = ui->tablaregistros_listar->rowCount();
                        int camino=0;
                        ui->tablaregistros_listar->insertRow(rowc);
                       for(int o=0;o<camposa.count();o++){
                            ui->tablaregistros_listar->setItem(rowc,o,new QTableWidgetItem(line.mid(camino,camposa[o].getTamano())));
                            camino+=camposa[o].getTamano();
                        }

//
                     }
                }
                if(line=="$")
                    empezar = true;


            }


           file.close();
}
