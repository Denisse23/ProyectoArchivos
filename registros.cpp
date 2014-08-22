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
    ui->lnumre_registros->setText("0");
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
    ui->lnumre_registros->setText("0");
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
     int numcampollave=-1;
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
          if(llave=="Si---"){
              lla=true;
               numcampollave=camposa.count();
          }
          camposa.append(campos(QString::fromStdString(nombre),QString::fromStdString(tipo),QString::fromStdString(tamano).toInt(),lla));
     }
     archivo.close();
     if(numcampollave!=-1){
     ifstream archivo1(nom);
     bool regis = false;
     int cam = 0;
     while(archivo1.good()){
        if(cam==camposa.count())
            cam=0;
        string key;
        archivo1>>key;
        if(key[0]!='\0'){
        if(key=="$" || regis){
            if(regis){
                if(key[0]!='[' && cam==0){
                    for(int j=0;j<camposa[0].getTamano();j++){
                        if(key[j]=='-')
                            key[j]='\0';
                    }
                    llaves.append(QString::fromStdString(key));
                    ui->comboarchivos_registros->addItem(llaves[llaves.count()-1]);

                 }
                cam++;
            }
            regis = true;

        }
        }

    }

     archivo1.close();

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
    if(ui->lentradacampo_registros->text()==""){}else{
    bool entrar = true;
    for(int i=0;i<llaves.count();i++){

        if(llaves[i]==ui->lentradacampo_registros->text()){
          entrar = false;
           ui->comboarchivos_registros->addItem(llaves[i]);
          break;
        }
    }
    if(entrar){

    camposllenados.append(ui->lentradacampo_registros->text());
    num++;

    if(num<camposa.count()){
        ui->lnumcampo_registros->setText(QString::number(num+1));
        ui->lnombrecampo_registros->setText(camposa[num].getNombre());
        ui->ltipocampo_registros->setText(camposa[num].getTipo());
        ui->ltamanocampo_registros->setText(QString::number(camposa[num].getTamano()));
        if(camposa[num].getEsLlave())
            ui->lesllave_registros->setText("Si");
        else
            ui->lesllave_registros->setText("No");
        ui->lentradacampo_registros->setText("");
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
        ui->lnumre_registros->setText(QString::number(ui->lnumre_registros->text().toInt()+1));
        string registro;

        for(int i=0;i<camposllenados.count();i++){
           for(int o=0;o<camposllenados[i].length();o++){
                if(camposllenados[i][o]==' ')
                    camposllenados[i][o] = '-';
            }

           for(int b=camposllenados[i].length();b<camposa[i].getTamano();b++)
               camposllenados[i]+= "-";

           camposllenados[i]+=" ";
           registro+= camposllenados[i].toStdString();

        }
        string nomarchivo =ui->comboarchivos_registros->currentText().toStdString();

         char nom[30];
         for(int i=0;i<nomarchivo.length();i++)
             nom[i] = nomarchivo[i];
         if(nomarchivo.length()<30)
            nom[nomarchivo.length()] = '\0';
        ofstream agregar(nom, fstream::app);
        agregar<<registro<<endl;
        agregar.close();
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
        camposllenados.clear();
    }
    }
    else{
            ui->lentradacampo_registros->setText("");
        }
    }
}
