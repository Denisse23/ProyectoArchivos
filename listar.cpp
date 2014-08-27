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
static void process_line(const QByteArray &)
{
}

static void process_line(const QString &)
{
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
        QString line = in.readLine();
        QStringList divisiones = line.split(" ");
        bool lla =false;
        if(divisiones[3]=="Sí")
        lla=true;
        camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
        while (!line.isNull()) {
            line = in.readLine();
            process_line(line);
           if(line=="|")
                break;
            QStringList divisiones = line.split(" ");
            bool lla =false;
            if(divisiones[3]=="Sí")
                lla=true;
            camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
        }
        ui->tablaregistros_listar->setColumnCount(camposa.count());

        for(int i=0;i<camposa.count();i++){

            ui->tablaregistros_listar->setHorizontalHeaderItem(i,new QTableWidgetItem(camposa[i].getNombre()));
        }

        QFile file1 (ui->comboarchivos_listar->currentText());
        if (!file1.open(QIODevice::ReadWrite | QIODevice::Text))
                return;
            QTextStream in1(&file1);
            QString line1 = in1.readLine();
            bool empezar = false;
            while (!line1.isNull()) {
                line1 = in1.readLine();
                process_line(line1);
                if(empezar){
                    if(line1[0]!='*'){
                        int rowc = ui->tablaregistros_listar->rowCount();
                        int camino=0;
                        ui->tablaregistros_listar->insertRow(rowc);
                       for(int o=0;o<camposa.count();o++){
                            ui->tablaregistros_listar->setItem(rowc,o,new QTableWidgetItem(line1.mid(camino,camposa[o].getTamano())));
                            camino+=camposa[o].getTamano();
                        }

//
                     }
                }
                if(line1=="$")
                    empezar = true;


            }
            if(ui->tablaregistros_listar->rowCount()>0)
             ui->tablaregistros_listar->removeRow(ui->tablaregistros_listar->rowCount()-1);

            file1.close();
}
