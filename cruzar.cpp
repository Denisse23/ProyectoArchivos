#include "cruzar.h"
#include "ui_cruzar.h"


cruzar::cruzar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cruzar)
{
    ui->setupUi(this);
}

cruzar::~cruzar()
{
    delete ui;
}

void cruzar::on_pushButton_clicked()
{
    file1.close();
    file2.close();
    campos1.clear();
    campos2.clear();
    ui->comboarchivo1_cruzar->clear();
    ui->comboarchivo2_cruzar->clear();
    ui->combocampos_cruzar->clear();
    for(int i=ui->tabla_cruzar->rowCount()-1;i>=0;i--)
        ui->tabla_cruzar->removeRow(i);
    for(int i=ui->tabla_cruzar->columnCount();i>=0;i--)
        ui->tabla_cruzar->removeColumn(i);
    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboarchivo1_cruzar->addItem(QString::fromStdString(archivo));
        ui->comboarchivo2_cruzar->addItem(QString::fromStdString(archivo));
    }//fin del while
    verificar.close();

    ui->comboarchivo1_cruzar->removeItem(ui->comboarchivo1_cruzar->count()-1);
    ui->comboarchivo2_cruzar->removeItem(ui->comboarchivo2_cruzar->count()-1);
}

void cruzar::on_combocampos_cruzar_activated(const QString &arg1)
{
    for(int i=ui->tabla_cruzar->rowCount()-1;i>=0;i--)
        ui->tabla_cruzar->removeRow(i);
    for(int i=ui->tabla_cruzar->columnCount();i>=0;i--)
        ui->tabla_cruzar->removeColumn(i);

    bool campo1=true;
    for(int i=0;i<campos2.count();i++){
        if(campos2[i].getNombre()==ui->combocampos_cruzar->currentText() && campos2[i].getEsLlave()==true)
            campo1=false;
    }//fin del for
    int columnaeliminar=0;
    int campollave=0;

    if(campo1==false){
    for(int i=0;i<campos1.count();i++){
        ui->tabla_cruzar->insertColumn(i);
       if(campos1[i].getNombre().length()>campos1[i].getTamano())
            ui->tabla_cruzar->setColumnWidth(i,campos1[i].getNombre().length()*10);
        else
            ui->tabla_cruzar->setColumnWidth(i,campos1[i].getTamano()*15);
        ui->tabla_cruzar->setHorizontalHeaderItem(i,new QTableWidgetItem(campos1[i].getNombre()));
        if(campos1[i].getNombre()==ui->combocampos_cruzar->currentText() && campos1[i].getEsLlave()==false)
            campollave = i;
      }//fin del for

    for(int i=0;i<campos2.count();i++){
        int col =campos1.count()+i;
        ui->tabla_cruzar->insertColumn(col);
        if(campos2[i].getNombre().length()>campos2[i].getTamano())
            ui->tabla_cruzar->setColumnWidth(col,campos2[i].getNombre().length()*10);
        else
            ui->tabla_cruzar->setColumnWidth(col,campos2[i].getTamano()*15);
         ui->tabla_cruzar->setHorizontalHeaderItem(col,new QTableWidgetItem(campos2[i].getNombre()));
         if(campos2[i].getNombre()==ui->combocampos_cruzar->currentText() && campos2[i].getEsLlave()==true)
             columnaeliminar=col;
    }//fin del for
    }else{
        for(int i=0;i<campos2.count();i++){
            ui->tabla_cruzar->insertColumn(i);
           if(campos2[i].getNombre().length()>campos2[i].getTamano())
                ui->tabla_cruzar->setColumnWidth(i,campos2[i].getNombre().length()*10);
            else
                ui->tabla_cruzar->setColumnWidth(i,campos2[i].getTamano()*15);
            ui->tabla_cruzar->setHorizontalHeaderItem(i,new QTableWidgetItem(campos2[i].getNombre()));
             if(campos2[i].getNombre()==ui->combocampos_cruzar->currentText() && campos2[i].getEsLlave()==false)
                campollave = i;
        }//fin del for

        for(int i=0;i<campos1.count();i++){
            int col =campos2.count()+i;
            ui->tabla_cruzar->insertColumn(col);
            if(campos1[i].getNombre().length()>campos1[i].getTamano())
                ui->tabla_cruzar->setColumnWidth(col,campos1[i].getNombre().length()*10);
            else
                ui->tabla_cruzar->setColumnWidth(col,campos1[i].getTamano()*15);
             ui->tabla_cruzar->setHorizontalHeaderItem(col,new QTableWidgetItem(campos1[i].getNombre()));
             if(campos1[i].getNombre()==ui->combocampos_cruzar->currentText() && campos1[i].getEsLlave()==true)
                 columnaeliminar=col;
        }//fin del for
    }

     ui->tabla_cruzar->removeColumn(columnaeliminar);

     QString line;
     file1.seek(0);
     file2.seek(0);
     if(campo1==false){
         QTextStream in(&file1);
        bool empezar = false;
            while (!in.atEnd()) {
                line = in.readLine();
                if(empezar){
                     if(line[0]!='*'){
                         int rowc = ui->tabla_cruzar->rowCount();
                         int camino=0;
                         ui->tabla_cruzar->insertRow(rowc);
                         for(int o=0;o<campos1.count();o++){
                            ui->tabla_cruzar->setItem(rowc,o,new QTableWidgetItem(line.mid(camino,campos1[o].getTamano())));
                          camino+=campos1[o].getTamano();
                         }//fin del for
                     }//fin del if
              }//fin del if
            if(line=="$")
                empezar = true;
       }//fin del while

       QTextStream in2(&file2);
       empezar = false;
       int comienzoc =0;
       QList<int> lista;
       for(int u=0;u<columnaeliminar-campos1.count();u++)
           comienzoc+=campos2[u].getTamano();
        while (!in2.atEnd()) {
           line = in2.readLine();
           if(empezar){
            for(int i=0;i<ui->tabla_cruzar->rowCount();i++){
               QTableWidgetItem* item = ui->tabla_cruzar->item(i,campollave);
                if(item->text()==line.mid(comienzoc,campos2[columnaeliminar-campos1.count()].getTamano())){
                    int camino=0;
                    int col = campos1.count();
                    for(int o=0;o<campos2.count();o++){
                       if(o!=columnaeliminar-campos1.count()){
                       ui->tabla_cruzar->setItem(i,col,new QTableWidgetItem(line.mid(camino,campos2[o].getTamano())));
                       col++;
                       }//fin del uf
                       camino+=campos2[o].getTamano();
                       }//fin del for
                }//fin del if

            }//fin del for

           }//fin del if
           if(line=="$")
               empezar = true;
       }

    }else{

         QTextStream in(&file2);
         bool empezar = false;
        while (!in.atEnd()) {
            line = in.readLine();
            if(empezar){
                if(line[0]!='*'){
                    int rowc = ui->tabla_cruzar->rowCount();
                    int camino=0;
                    ui->tabla_cruzar->insertRow(rowc);
                    for(int o=0;o<campos2.count();o++){
                       ui->tabla_cruzar->setItem(rowc,o,new QTableWidgetItem(line.mid(camino,campos2[o].getTamano())));
                     camino+=campos2[o].getTamano();
                    }//fin del for
                }//fin del if
            }//fin del if
            if(line=="$")
                empezar = true;
        }//fin del while
        QTextStream in2(&file1);
        empezar = false;
        int comienzoc =0;

        for(int u=0;u<columnaeliminar-campos2.count();u++)
            comienzoc+=campos1[u].getTamano();

         while (!in2.atEnd()) {
            line = in2.readLine();
            if(empezar){
             for(int i=0;i<ui->tabla_cruzar->rowCount();i++){
                QTableWidgetItem* item = ui->tabla_cruzar->item(i,campollave);
                 if(item->text()==line.mid(comienzoc,campos1[columnaeliminar-campos2.count()].getTamano())){
                     int camino=0;
                     int col = campos2.count();
                     for(int o=0;o<campos1.count();o++){
                        if(o!=columnaeliminar-campos2.count()){
                        ui->tabla_cruzar->setItem(i,col,new QTableWidgetItem(line.mid(camino,campos1[o].getTamano())));
                        col++;
                        }//fin del if
                        camino+=campos1[o].getTamano();
                        }//fin del for
                 }//fin del if



            }//fin del for
           }//fin del if
          if(line=="$")
               empezar = true;
       }//fin del while

  }//fin del ultimo else
      ui->combocampos_cruzar->addItem(QString::number(ui->tabla_cruzar->columnCount()));
      int rowcount = ui->tabla_cruzar->rowCount();
      int i=0;
       while(i<rowcount){
          QTableWidgetItem* item = ui->tabla_cruzar->item(i,ui->tabla_cruzar->columnCount()-1);
          if(item==NULL){
              ui->tabla_cruzar->removeRow(i);
              rowcount--;
          }else{
              i++;
         }
       }//fin del while
}

void cruzar::on_comboarchivo1_cruzar_activated(const QString &arg1)
{
    campos1.clear();
    for(int i=ui->tabla_cruzar->rowCount()-1;i>=0;i--)
        ui->tabla_cruzar->removeRow(i);
    for(int i=ui->tabla_cruzar->columnCount();i>=0;i--)
        ui->tabla_cruzar->removeColumn(i);
    ui->combocampos_cruzar->clear();
    file1.close();
    file1.setFileName(arg1);
    if(!file1.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

        QTextStream in(&file1);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            if(line=="|")
                break;
            QStringList divisiones = line.split(" ");
            bool lla =false;
            if(divisiones[3]=="Sí"){
                lla=true;
            }//fin del if

            campos1.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));

        }//fin del while

}//fin del metodo

void cruzar::on_comboarchivo2_cruzar_activated(const QString &arg1)
{
    campos2.clear();
    for(int i=ui->tabla_cruzar->rowCount()-1;i>=0;i--)
        ui->tabla_cruzar->removeRow(i);
    for(int i=ui->tabla_cruzar->columnCount();i>=0;i--)
        ui->tabla_cruzar->removeColumn(i);
    ui->combocampos_cruzar->clear();
    file2.close();
    file2.setFileName(arg1);
    if (!file2.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QTextStream in(&file2);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            if(line=="|")
                break;
            QStringList divisiones = line.split(" ");
            bool lla =false;
            if(divisiones[3]=="Sí"){
                lla=true;
            }//fin del if

            campos2.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));

        }//fin del while
}

void cruzar::on_pushButton_2_clicked()
{
    for(int i=ui->tabla_cruzar->rowCount()-1;i>=0;i--)
        ui->tabla_cruzar->removeRow(i);
    for(int i=ui->tabla_cruzar->columnCount();i>=0;i--)
        ui->tabla_cruzar->removeColumn(i);
    ui->combocampos_cruzar->clear();

    if(ui->comboarchivo1_cruzar->currentText()!=ui->comboarchivo2_cruzar->currentText()){
          for(int i=0;i<campos1.count();i++){
              for(int j=0;j<campos2.count();j++){
                  if(campos1[i].getNombre()==campos2[j].getNombre() && campos1[i].getTamano()==campos2[j].getTamano()
                      && campos1[i].getTipo()== campos2[j].getTipo()){
                      if(campos1[i].getEsLlave() || campos2[j].getEsLlave())
                      ui->combocampos_cruzar->addItem(campos1[i].getNombre());
                      j=campos2.count();
                  }//fin del if
              }//fin del for
          }//fin del for
      }//fin del if


}
