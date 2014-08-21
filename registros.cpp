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



registros::~registros()
{
    delete ui;
}

void registros::on_pushButton_clicked()
{
    ui->comboarchivos_registros->clear();
    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboarchivos_registros->addItem(QString::fromStdString(archivo));
    }
    string nomarchivo = ui->comboarchivos_registros->currentText().toStdString();
    char nom[30];
    for(int i=0;i<nomarchivo.length();i++)
        nom[i] = nomarchivo[i];
    ifstream archivo(nom);
    string line;
    while(archivo.good()){
        string num;
        string nombre;
        string tipo;
        string tamano;
        string llave;
        archivo >>num>>nombre>>tipo>>tamano>>llave;


         bool lla = false;
         if(llave=="Si")
             lla=true;
         camposa.append(campos(QString::fromStdString(nombre),QString::fromStdString(tipo),QString::fromStdString(tamano).toInt(),lla));
    }
    ui->lnumcampo_archivos->setText("1");
    ui->lnombrecampo_archivos->setText(camposa[0].getNombre());
    ui->ltipodecampo_archivos->setText(camposa[0].getTipo());
    ui->ltamanocampo_archivos->setText(QString::number(camposa[0].getTamano()));
    if(camposa[0].getEsLlave())
        ui->lesllave_archivos->setText("Si");
    else
        ui->lesllave_archivos->setText("No");

    ui->comboarchivos_registros->removeItem(ui->comboarchivos_registros->count()-1);
    ui->lnombrecampo_archivos->setText("");
    ui->lnumcampo_archivos->setText("");
    ui->ltipodecampo_archivos->setText("");
    ui->ltamanocampo_archivos->setText("");
    ui->lentradacampo_registros->setText("");
    ui->lesllave_archivos->setText("");
    camposa.clear();
    camposllenados.clear();
}
