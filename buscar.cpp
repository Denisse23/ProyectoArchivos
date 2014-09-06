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
    ui->combo_estructura->clear();
    for(int i=ui->tablaBusqueda->rowCount()-1;i>-1;i--)
        ui->tablaBusqueda->removeRow(i);
    for(int i=ui->tablaBusqueda->columnCount()-1;i>-1;i--)
        ui->tablaBusqueda->removeColumn(i);
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
          ui->comboarchivos_buscar->addItem(archivos[i]);
        }
        file.close();
      }
}



void buscar::on_pushButton_2_clicked()
{


    for(int i=ui->tablaBusqueda->rowCount()-1;i>-1;i--)
        ui->tablaBusqueda->removeRow(i);
    for(int i=ui->tablaBusqueda->columnCount()-1;i>-1;i--)
        ui->tablaBusqueda->removeColumn(i);
    if(ui->combo_estructura->count()>0 && ui->termino->text()!="" ){
        for(int i=0;i<camposa.count();i++){
            ui->tablaBusqueda->insertColumn(i);
            if(camposa[i].getNombre().length()>camposa[i].getTamano())
                ui->tablaBusqueda->setColumnWidth(i,camposa[i].getNombre().length()*10);
            else
                ui->tablaBusqueda->setColumnWidth(i,camposa[i].getTamano()*20);
            ui->tablaBusqueda->setHorizontalHeaderItem(i,new QTableWidgetItem(camposa[i].getNombre()));
        }


        int sumatamanos =0;
        for(int i=0;i<ui->combo_estructura->currentIndex();i++){
            sumatamanos+= camposa[i].getTamano();
        }
               file.seek(0);
               QTextStream in(&file);
               QString linea;
               QString particion;
               bool iniciore =false;
               while (!in.atEnd()) {
               linea=in.readLine();

               if(iniciore){
                particion =linea.mid(sumatamanos,camposa[ui->combo_estructura->currentIndex()].getTamano()).toLower();
                   if(linea[0]!='*' && particion.contains(ui->termino->text().toLower())){
                       int rowc = ui->tablaBusqueda->rowCount();
                       int camino=0;
                       ui->tablaBusqueda->insertRow(rowc);
                      for(int o=0;o<camposa.count();o++){
                           ui->tablaBusqueda->setItem(rowc,o,new QTableWidgetItem(linea.mid(camino,camposa[o].getTamano())));
                           camino+=camposa[o].getTamano();
                       }
                   }
               }
               if(linea=="$")
                   iniciore = true;
             }//fin while
         //}//fin if abrir archivo
         if(ui->tablaBusqueda->rowCount()==0){
             ui->tablaBusqueda->insertRow(0);
             ui->tablaBusqueda->setItem(0,0,new QTableWidgetItem("No se encontro"));
          }
    }//fin if principal


}

void buscar::on_comboarchivos_buscar_activated(const QString &arg1)
{
    file.close();
    ui->combo_estructura->clear();
    ui->termino->setText("");
    for(int i=ui->tablaBusqueda->rowCount()-1;i>-1;i--)
        ui->tablaBusqueda->removeRow(i);
    for(int i=ui->tablaBusqueda->columnCount()-1;i>-1;i--)
        ui->tablaBusqueda->removeColumn(i);

    camposa.clear();
    file.setFileName(ui->comboarchivos_buscar->currentText());
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

        for(int i=0;i<camposa.count();i++)
            ui->combo_estructura->addItem(camposa[i].getNombre());
}//fin del metodo

void buscar::on_combo_estructura_activated(const QString &arg1)
{
    ui->termino->setText("");
    for(int i=ui->tablaBusqueda->rowCount()-1;i>-1;i--)
        ui->tablaBusqueda->removeRow(i);
    for(int i=ui->tablaBusqueda->columnCount()-1;i>-1;i--)
        ui->tablaBusqueda->removeColumn(i);
}
