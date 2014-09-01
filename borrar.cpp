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

void borrar::on_pushButton_clicked()
{
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
    ultimocampoborrado=-1;
    ui->comboregistros_borrar->clear();
    ui->lbusqueda_borrar->setText("");
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
    ui->combocampos_borrar->clear();
    camposa.clear();
    QFile file (ui->comboarchivos_borrar->currentText());
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
                       int rowc = ui->tabla_borrar->rowCount();
                       int camino=0;
                       ui->tabla_borrar->insertRow(rowc);
                      for(int o=0;o<camposa.count();o++){
                           ui->tabla_borrar->setItem(rowc,o,new QTableWidgetItem(linea.mid(camino,camposa[o].getTamano())));
                           camino+=camposa[o].getTamano();
                       }


                   }else if(linea[0]=='*' && buscarborrados){
                      if(linea[1]=='-' && linea[2]=='-1'){
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
    ui->comboregistros_borrar->clear();
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
    ui->lbusqueda_borrar->setText("");
}

void borrar::on_pushButton_3_clicked()
{

    ui->comboregistros_borrar->addItem(QString::number(ui->tabla_borrar->currentRow()+17));

}

void borrar::on_pushButton_4_clicked()
{
    ui->comboregistros_borrar->clear();
}

void borrar::on_pushButton_5_clicked()
{

    ui->lbusqueda_borrar->setText("");
    ui->comboregistros_borrar->clear();
    for(int i=ui->tabla_borrar->rowCount()-1;i>-1;i--)
        ui->tabla_borrar->removeRow(i);
    for(int i=ui->tabla_borrar->columnCount()-1;i>-1;i--)
        ui->tabla_borrar->removeColumn(i);
}
