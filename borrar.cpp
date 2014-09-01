#include "borrar.h"
#include "ui_borrar.h"

borrar::borrar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrar)
{
    ui->setupUi(this);
}

borrar::~borrar()
{
    delete ui;
}
void borrar::borrarregistros(QList<int> RRNP){
    char conectar[RRNP.count()+1][2];
        for(int i=0;i<RRNP.count()+1;i++){
            if(i==0){
             conectar[i][0]=ultimocampoborrado;
             conectar[i][1]=RRNP[i];
            }else if(i==RRNP.count()){
             conectar[i][0]=RRNP[i-1];
             conectar[i][1]=-1;
            }else{
             conectar[i][0]=RRNP[i-1];
             conectar[i][1]=RRNP[i];
           }
       }

    if(RRNP.count()>0){
       for(int i=0;i<RRNP.count()+1;i++){
        QFile file (ui->comboarchivos_borrar->currentText());
            file.open(QIODevice::ReadWrite|QIODevice::Text);
            QTextStream in(&file);
            QString line;
            int offset = 0;
            int conR =0;
            bool leer = false;
            bool head = false;
            while (!in.atEnd()) {
                line = in.readLine();
                if(head){
                    if(conectar[i][0]==-1){
                        for(int k=0;k<6;k++){
                            if(k<QString::number(conectar[i][1]).length()){
                                line[k]= QString::number(conectar[i][1])[k];
                             }else{
                                line[k]=' ';
                             }
                        }
                        file.seek(offset+1);
                        in<<line<<endl;
                        break;
                    }
                    head = false;
                }
                if(leer){
                   conR++;
                  if(conR==conectar[i][0]){
                      line[0]='*';
                     for(int k=0;k<QString::number(conectar[i][1]).length();k++){
                        line[k+1]= QString::number(conectar[i][1])[k];
                     }
                     line[QString::number(conectar[i][1]).length()+1]='*';
                     file.seek(offset+1);
                     in<<line<<endl;
                     break;
                 }
                }
                 if(line=="$")
                     leer = true;
                 if(line=="|")
                     head = true;
                 offset+= line.length()+1;
             }
        file.close();
        }

    }
}

void borrar::on_pushButton_clicked()
{
    RRN.clear();
    ultimocampoborrado=-1;
    ui->comboregistros_borrar->clear();
    ui->lbusqueda_borrar->setText("");
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
    camposa.clear();
    ui->comboarchivos_borrar->clear();
    ui->combocampos_borrar->clear();
    QList<QString> archivos;
    QFile file("archivoscreados.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream in(&file);
        while (!in.atEnd()) {
        QString archivo;
        archivo=in.readLine();
        archivos.append(archivo);
    }//fin del while
}//fin del if
    //solo cargara archivos con
    for(int i=0;i<archivos.count();i++){
        QFile file (archivos[i]);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QTextStream in(&file);
        QString line = in.readLine();
        int mas = 0;
        bool activar = false;
        while (!line.isNull()) {
            line = in.readLine();
            if(mas==1){
                mas++;
                break;
             }
            if(activar)
                if(line!="\n")
                  mas++;
             if(line=="$")
                activar = true;
          }

        if(mas==2){
          ui->comboarchivos_borrar->addItem(archivos[i]);
        }
        file.close();
      }
}

void borrar::on_comboarchivos_borrar_activated(const QString &arg1)
{
    RRN.clear();
    ultimocampoborrado=-1;
    ui->comboregistros_borrar->clear();
    ui->lbusqueda_borrar->setText("");
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
    ui->combocampos_borrar->clear();
    camposa.clear();
    QFile file (arg1);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QTextStream in(&file);
        QString line = in.readLine();
        QStringList divisiones = line.split(" ");
        bool lla =false;
        if(divisiones[3]=="Sí"){
             lla=true;
        }
        camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
        while (!line.isNull()) {
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

        for(int i=0;i<camposa.count();i++)
            ui->combocampos_borrar->addItem(camposa[i].getNombre());
}

void borrar::on_pushButton_2_clicked()
{
    RRN.clear();
    ultimocampoborrado=-1;
    ui->comboregistros_borrar->clear();
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
    if(ui->combocampos_borrar->count()>0 && ui->lbusqueda_borrar->text()!="" ){
        for(int i=0;i<camposa.count();i++){
            ui->tabla_borrar->insertColumn(i);
            if(camposa[i].getNombre().length()>camposa[i].getTamano())
                ui->tabla_borrar->setColumnWidth(i,camposa[i].getNombre().length()*10);
            else
                ui->tabla_borrar->setColumnWidth(i,camposa[i].getTamano()*10);
            ui->tabla_borrar->setHorizontalHeaderItem(i,new QTableWidgetItem(camposa[i].getNombre()));
        }

        QFile file(ui->comboarchivos_borrar->currentText());
        int sumatamanos =0;
        for(int i=0;i<ui->combocampos_borrar->currentIndex();i++){
            sumatamanos+= camposa[i].getTamano();
        }
         if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
               QTextStream in(&file);
               QString linea;
               QString particion;
               bool iniciore =false;
               bool saberllave = false;
               bool buscarborrados = false;
               int contadorRRN = 0;
             while (!in.atEnd()) {
               linea=in.readLine();
               if(saberllave){
                   saberllave = false;
                   if(linea!="-1    ")
                       buscarborrados=true;
               }
               if(iniciore){
                   contadorRRN++;
                   particion =linea.mid(sumatamanos,camposa[ui->combocampos_borrar->currentIndex()].getTamano()).toLower();
                   if(linea[0]!='*' && particion.contains(ui->lbusqueda_borrar->text().toLower())){
                       RRN.append(contadorRRN);
                       int rowc = ui->tabla_borrar->rowCount();
                       int camino=0;
                       ui->tabla_borrar->insertRow(rowc);
                      for(int o=0;o<camposa.count();o++){
                           ui->tabla_borrar->setItem(rowc,o,new QTableWidgetItem(linea.mid(camino,camposa[o].getTamano())));
                           camino+=camposa[o].getTamano();
                       }


                   }else if(linea[0]=='*' && buscarborrados){
                      if(linea[1]=='-' && linea[2]=='1'){
                          ultimocampoborrado=contadorRRN;
                          buscarborrados=false;
                     }
                   }
               }
               if(linea=="$")
                   iniciore = true;
               if(linea=="|")
                   saberllave=true;
             }//fin while
         }//fin if abrir archivo
         if(ui->tabla_borrar->rowCount()==0){
             ui->tabla_borrar->insertRow(0);
             ui->tabla_borrar->setItem(0,0,new QTableWidgetItem("No se encontro"));
          }
    }//fin if principal

}

void borrar::on_combocampos_borrar_activated(const QString &arg1)
{
    RRN.clear();
    ui->comboregistros_borrar->clear();
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
    ui->lbusqueda_borrar->setText("");
}

void borrar::on_pushButton_3_clicked()
{
    bool repetido = false;
    for(int i=0;i<ui->comboregistros_borrar->count();i++){
        if(ui->comboregistros_borrar->itemText(i).toInt()==ui->tabla_borrar->currentRow()+1){
            repetido=true;
            break;
        }
    }
    if(repetido==false)
         ui->comboregistros_borrar->addItem(QString::number(ui->tabla_borrar->currentRow()+1));

}

void borrar::on_pushButton_4_clicked()
{
    ui->comboregistros_borrar->clear();

}

void borrar::on_pushButton_5_clicked()
{
    borrarregistros(RRN);
    ui->lbusqueda_borrar->setText("");
    ui->comboregistros_borrar->clear();
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
}

void borrar::on_pushButton_6_clicked()
{
    QList<int> RRN2;

    for(int i=0;i<ui->comboregistros_borrar->count();i++){
        RRN2.append(RRN[ui->comboregistros_borrar->itemText(i).toInt()-1]);
    }
    borrarregistros(RRN2);
    ui->lbusqueda_borrar->setText("");
    ui->comboregistros_borrar->clear();
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
}
