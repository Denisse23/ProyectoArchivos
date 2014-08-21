#include "registros.h"
#include "ui_registros.h"

registros::registros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registros)
{
    ui->setupUi(this);
}


registros::~registros()
{
    delete ui;
}

void registros::on_pushButton_clicked()
{
    ui->lnumregistros_registros->setText("0");
    ui->comboarchivos_registros->clear();
    ui->lnombrecampo_registros->setText("");
    ui->lnumcampo_registros->setText("");
    ui->ltipocampo_registros->setText("");
    ui->ltamanocampo_registros->setText("");
    ui->lentradacampo_registros->setText("");
    ui->lesllave_registros->setText("");

    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboarchivos_registros->addItem(QString::fromStdString(archivo));
    }

    camposa.clear();
    camposllenados.clear();
    ui->comboarchivos_registros->removeItem(ui->comboarchivos_registros->count()-1);

}

void registros::on_comboarchivos_registros_activated(const QString &arg1)
{
    ui->lnumregistros_registros->setText("0");
    ui->lnombrecampo_registros->setText("");
    ui->lnumcampo_registros->setText("");
    ui->ltipocampo_registros->setText("");
    ui->ltamanocampo_registros->setText("");
    ui->lentradacampo_registros->setText("");
    ui->lesllave_registros->setText("");
    camposa.clear();
    camposllenados.clear();

    string nomarchivo =ui->comboarchivos_registros->currentText().toStdString();

     char nom[30];
     for(int i=0;i<nomarchivo.length();i++)
         nom[i] = nomarchivo[i];
     if(nomarchivo.length()<30)
        nom[nomarchivo.length()] = '\0';
     ui->lnombrecampo_registros->setText(QString::fromStdString(nomarchivo));
     ifstream archivo(nom);
     while(archivo.good()){
         string nombre="";
         string tipo="";
         string tamano="";
         string llave="";
         archivo >>nombre>>tipo>>tamano>>llave;
         if(nombre=="|")
             break;
         for (int u=0;u<nombre.length();u++){
             if(nombre[u]=='-'){
                 nombre[u]='\0';

             }
         }
         for (int u=0;u<tipo.length();u++){
             if(tipo[u]=='-'){
                 tipo[u]='\0';

             }
         }
         for (int u=0;u<tamano.length();u++){
             if(tamano[u]=='-'){
                 tamano[u]='\n';

             }
         }

          bool lla = false;
          if(llave=="Si---")
              lla=true;
          camposa.append(campos(QString::fromStdString(nombre),QString::fromStdString(tipo),QString::fromStdString(tamano).toInt(),lla));
     }

     ui->lnumcampo_registros->setText("1");
     ui->lnombrecampo_registros->setText(camposa[0].getNombre());
     ui->ltipocampo_registros->setText(camposa[0].getTipo());
     ui->ltamanocampo_registros->setText(QString::number(camposa[0].getTamano()));
     if(camposa[0].getEsLlave())
         ui->lesllave_registros->setText("Si");
     else
         ui->lesllave_registros->setText("No");
     QString mask;
     if(camposa[0].getTipo()=="Entero"){
        for(int i=0;i<camposa[0].getTamano();i++)
            mask+="0";
     }else{
        for(int i=0;i<camposa[0].getTamano();i++)
            mask+="n";
     }
     ui->lentradacampo_registros->setInputMask(mask+"\0");


}

void registros::on_boton_agregar_campo_clicked()
{
    int num = camposllenados.count();
    if(ui->lentradacampo_registros->text()=="" && camposa[num].getEsLlave()){

    }else{
    camposllenados.append(ui->lentradacampo_registros->text());
    num++;
    ui->lnumregistros_registros->setText(QString::number(num));
    if(num<camposa.count()){
        ui->lnumcampo_registros->setText(QString::number(num+1));
        ui->lnombrecampo_registros->setText(camposa[num].getNombre());
        ui->ltipocampo_registros->setText(camposa[num].getTipo());
        ui->ltamanocampo_registros->setText(QString::number(camposa[num].getTamano()));
        if(camposa[num].getEsLlave())
            ui->lesllave_registros->setText("Si");
        else
            ui->lesllave_registros->setText("No");
        QString mask;
        if(camposa[num].getTipo()=="Entero"){
           for(int i=0;i<camposa[num].getTamano();i++)
               mask+="0";
        }else{
           for(int i=0;i<camposa[num].getTamano();i++)
               mask+="n";
        }
        ui->lentradacampo_registros->setInputMask(mask+"\0");
    }else{
        ui->lnumcampo_registros->setText("1");
        ui->lnombrecampo_registros->setText(camposa[0].getNombre());
        ui->ltipocampo_registros->setText(camposa[0].getTipo());
        ui->ltamanocampo_registros->setText(QString::number(camposa[0].getTamano()));
        if(camposa[0].getEsLlave())
            ui->lesllave_registros->setText("Si");
        else
            ui->lesllave_registros->setText("No");
        QString mask;
        if(camposa[0].getTipo()=="Entero"){
           for(int i=0;i<camposa[0].getTamano();i++)
               mask+="0";
        }else{
           for(int i=0;i<camposa[0].getTamano();i++)
               mask+="n";
        }
        ui->lentradacampo_registros->setInputMask(mask+"\0");
        ui->lnumregistros_registros->setText("0");
    }
    }
}
