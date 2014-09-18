#include "cruzarlineal.h"
#include "ui_cruzarlineal.h"

cruzarlineal::cruzarlineal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cruzarlineal)
{
    ui->setupUi(this);
}

cruzarlineal::~cruzarlineal()
{
    delete ui;
}

void cruzarlineal::on_pushButton_clicked()
{
    file1.close();
    file2.close();
    campos1.clear();
    campos2.clear();
    ui->comboarchivo1_cruzarlineal->clear();
    ui->comboarchivo2_cruzarlineal->clear();
    for(int i=ui->tabla_cruzarlineal->rowCount()-1;i>=0;i--)
        ui->tabla_cruzarlineal->removeRow(i);
    for(int i=ui->tabla_cruzarlineal->columnCount();i>=0;i--)
        ui->tabla_cruzarlineal->removeColumn(i);
    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboarchivo1_cruzarlineal->addItem(QString::fromStdString(archivo));
        ui->comboarchivo2_cruzarlineal->addItem(QString::fromStdString(archivo));
    }//fin del while
    verificar.close();

    ui->comboarchivo1_cruzarlineal->removeItem(ui->comboarchivo1_cruzarlineal->count()-1);
    ui->comboarchivo2_cruzarlineal->removeItem(ui->comboarchivo2_cruzarlineal->count()-1);
}

void cruzarlineal::on_comboarchivo1_cruzarlineal_activated(const QString &arg1)
{
    campos1.clear();
    for(int i=ui->tabla_cruzarlineal->rowCount()-1;i>=0;i--)
        ui->tabla_cruzarlineal->removeRow(i);
    for(int i=ui->tabla_cruzarlineal->columnCount();i>=0;i--)
        ui->tabla_cruzarlineal->removeColumn(i);
    ui->combocampos_cruzarlineal->clear();
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

}

void cruzarlineal::on_comboarchivo2_cruzarlineal_activated(const QString &arg1)
{
    campos2.clear();
    for(int i=ui->tabla_cruzarlineal->rowCount()-1;i>=0;i--)
        ui->tabla_cruzarlineal->removeRow(i);
    for(int i=ui->tabla_cruzarlineal->columnCount();i>=0;i--)
        ui->tabla_cruzarlineal->removeColumn(i);
    ui->combocampos_cruzarlineal->clear();
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

void cruzarlineal::on_pushButton_2_clicked()
{
    for(int i=ui->tabla_cruzarlineal->rowCount()-1;i>=0;i--)
        ui->tabla_cruzarlineal->removeRow(i);
    for(int i=ui->tabla_cruzarlineal->columnCount();i>=0;i--)
        ui->tabla_cruzarlineal->removeColumn(i);
    ui->combocampos_cruzarlineal->clear();

    if(ui->comboarchivo1_cruzarlineal->currentText()!=ui->comboarchivo2_cruzarlineal->currentText()){
          for(int i=0;i<campos1.count();i++){
              for(int j=0;j<campos2.count();j++){
                  if(campos1[i].getNombre()==campos2[j].getNombre() && campos1[i].getTamano()==campos2[j].getTamano()
                      && campos1[i].getTipo()== campos2[j].getTipo()){
                      if(campos1[i].getEsLlave() || campos2[j].getEsLlave())
                      ui->combocampos_cruzarlineal->addItem(campos1[i].getNombre());
                      j=campos2.count();
                  }//fin del if
              }//fin del for
          }//fin del for
      }//fin del if
}

void cruzarlineal::on_combocampos_cruzarlineal_activated(const QString &arg1)
{
    for(int i=ui->tabla_cruzarlineal->rowCount()-1;i>=0;i--)
        ui->tabla_cruzarlineal->removeRow(i);
    for(int i=ui->tabla_cruzarlineal->columnCount();i>=0;i--)
        ui->tabla_cruzarlineal->removeColumn(i);

    bool campo1=true;
    for(int i=0;i<campos2.count();i++){
        if(campos2[i].getNombre()==ui->combocampos_cruzarlineal->currentText() && campos2[i].getEsLlave()==true)
            campo1=false;
    }//fin del for
    int columnaeliminar=0;
    int campollave=0;
    int tamano=0;
    if(campo1==false){
    for(int i=0;i<campos1.count();i++){
        ui->tabla_cruzarlineal->insertColumn(i);
       if(campos1[i].getNombre().length()>campos1[i].getTamano())
            ui->tabla_cruzarlineal->setColumnWidth(i,campos1[i].getNombre().length()*10);
        else
            ui->tabla_cruzarlineal->setColumnWidth(i,campos1[i].getTamano()*15);
        ui->tabla_cruzarlineal->setHorizontalHeaderItem(i,new QTableWidgetItem(campos1[i].getNombre()));
        if(campos1[i].getNombre()==ui->combocampos_cruzarlineal->currentText() && campos1[i].getEsLlave()==false)
            campollave = i;

    }//fin del for

    for(int i=0;i<campos2.count();i++){
        tamano+=campos2[i].getTamano();
        int col =campos1.count()+i;
        ui->tabla_cruzarlineal->insertColumn(col);
        if(campos2[i].getNombre().length()>campos2[i].getTamano())
            ui->tabla_cruzarlineal->setColumnWidth(col,campos2[i].getNombre().length()*10);
        else
            ui->tabla_cruzarlineal->setColumnWidth(col,campos2[i].getTamano()*15);
         ui->tabla_cruzarlineal->setHorizontalHeaderItem(col,new QTableWidgetItem(campos2[i].getNombre()));
         if(campos2[i].getNombre()==ui->combocampos_cruzarlineal->currentText() && campos2[i].getEsLlave()==true)
             columnaeliminar=col;
    }//fin del for
    }else{
        for(int i=0;i<campos2.count();i++){
            ui->tabla_cruzarlineal->insertColumn(i);
           if(campos2[i].getNombre().length()>campos2[i].getTamano())
                ui->tabla_cruzarlineal->setColumnWidth(i,campos2[i].getNombre().length()*10);
            else
                ui->tabla_cruzarlineal->setColumnWidth(i,campos2[i].getTamano()*15);
            ui->tabla_cruzarlineal->setHorizontalHeaderItem(i,new QTableWidgetItem(campos2[i].getNombre()));
            if(campos2[i].getNombre()==ui->combocampos_cruzarlineal->currentText() && campos2[i].getEsLlave()==false)
                campollave = i;
        }//fin del for

        for(int i=0;i<campos1.count();i++){
            tamano+=campos1[i].getTamano();
            int col =campos2.count()+i;
            ui->tabla_cruzarlineal->insertColumn(col);
            if(campos1[i].getNombre().length()>campos1[i].getTamano())
                ui->tabla_cruzarlineal->setColumnWidth(col,campos1[i].getNombre().length()*10);
            else
                ui->tabla_cruzarlineal->setColumnWidth(col,campos1[i].getTamano()*15);
             ui->tabla_cruzarlineal->setHorizontalHeaderItem(col,new QTableWidgetItem(campos1[i].getNombre()));
             if(campos1[i].getNombre()==ui->combocampos_cruzarlineal->currentText() && campos1[i].getEsLlave()==true)
                 columnaeliminar=col;
        }//fin del for
    }//fin del else

     ui->tabla_cruzarlineal->removeColumn(columnaeliminar);
     QString nombreindice;
     int cantr=0;
     if(campo1==false){
         nombreindice = file2.fileName();
         cantr = file2.size()/tamano;
     }else{
         nombreindice = file1.fileName();
         cantr = file1.size()/tamano;
     }//fin del else
     QList<QString> matriz[cantr][2];
     nombreindice[nombreindice.length()-4] = 'l',nombreindice[nombreindice.length()-3] = 'i';
     nombreindice[nombreindice.length()-2] = 'd',nombreindice[nombreindice.length()-1] = 'x';
     QFile fileindice (nombreindice);
     if (!fileindice.open(QIODevice::ReadWrite | QIODevice::Text))
         return;
     QTextStream ini(&fileindice);
     QString linea;
     int RRN=0;
     while(!ini.atEnd()){
         linea = ini.readLine();
         matriz[RRN][0].append(linea.mid(0,linea.length()-6));
         RRN++;
     }//fin del while

     file1.seek(0);
     file2.seek(0);
     if(campo1==false){
         QTextStream in(&file1);
         QString line;
         bool empezar = false;
         while(!in.atEnd()){
             line = in.readLine();
             if(empezar){
                 if(line[0]!='*'){
                     int rowc = ui->tabla_cruzarlineal->rowCount();
                     int camino=0;
                     ui->tabla_cruzarlineal->insertRow(rowc);
                     QString data;
                     for(int o=0;o<campos1.count();o++){
                         data= line.mid(camino,campos1[o].getTamano());
                         if(o==campollave){
                            for(int i=0;i<RRN;i++){
                              if(data.toUpper()==matriz[i][0][0]){
                                  matriz[i][1].append(QString::number(rowc));
                                 break;
                              }//fin del if

                            }//fin del for
                         }//fin del if
                        ui->tabla_cruzarlineal->setItem(rowc,o,new QTableWidgetItem(data));
                      camino+=campos1[o].getTamano();
                   }//fin del for
                 }//fin del if
             }//fin del if
             if(line=="$")
                 empezar=true;

         }

         QTextStream in2(&file2);
         empezar = false;
         while(!in2.atEnd()){
             line = in2.readLine();
             if(empezar){
                 QString data;
                 int camino=0;
                 int lugma =-1;
                for(int o=0;o<campos2.count();o++){
                    data = line.mid(camino,campos2[o].getTamano());
                    if(o==columnaeliminar-campos1.count()){
                        for(int i=0;i<RRN;i++){
                            if(data.toUpper()==matriz[i][0][0]){
                              lugma = i;
                              break;
                            }//fin del if
                         }//fin del for
                    }//fin del if
                    camino+=campos2[o].getTamano();
                }//fin del for
                camino=0;
                int col  = campos1.count();
                for(int o=0;o<campos2.count();o++){
                    data = line.mid(camino,campos2[o].getTamano());
                    if(o!=columnaeliminar-campos1.count()){
                        if(lugma>-1){
                            for(int u=0;u<matriz[lugma][1].count();u++){
                               ui->tabla_cruzarlineal->setItem(matriz[lugma][1][u].toInt(),col+o,new QTableWidgetItem(data));
                               ui->comboarchivo1_cruzarlineal->addItem(matriz[lugma][1][u]);
                         }//fin del for
                        }//fin del if
                    }else{
                        col-=1;
                    }//fin del else
                    camino+=campos2[o].getTamano();
                }//fin del for
             }//fin del if
             if(line=="$")
                 empezar = true;
         }
     }else{
         QTextStream in(&file2);
         QString line;
         bool empezar = false;
         while(!in.atEnd()){
             line = in.readLine();
             if(empezar){
                 if(line[0]!='*'){
                     int rowc = ui->tabla_cruzarlineal->rowCount();
                     int camino=0;
                     ui->tabla_cruzarlineal->insertRow(rowc);
                     QString data;
                     for(int o=0;o<campos2.count();o++){
                         data= line.mid(camino,campos2[o].getTamano());
                         if(o==campollave){
                            for(int i=0;i<RRN;i++){
                              if(data.toUpper()==matriz[i][0][0]){
                                  matriz[i][1].append(QString::number(rowc));
                                 break;
                              }//fin del if

                            }//fin del for
                         }//fin del if
                        ui->tabla_cruzarlineal->setItem(rowc,o,new QTableWidgetItem(data));
                      camino+=campos2[o].getTamano();
                   }//fin del for
                }//fin del if
              }//fin del if
             if(line=="$")
                 empezar=true;

         }
         QTextStream in2(&file1);
         empezar = false;
         while(!in2.atEnd()){
             line = in2.readLine();
             if(empezar){
                 QString data;
                 int camino=0;
                 int lugma =-1;
                for(int o=0;o<campos1.count();o++){
                    data = line.mid(camino,campos1[o].getTamano());
                    if(o==columnaeliminar-campos2.count()){
                        for(int i=0;i<RRN;i++){
                            if(data.toUpper()==matriz[i][0][0]){
                              lugma = i;
                              break;
                            }//fin del if
                         }//fin del for
                    }//fin del if
                    camino+=campos1[o].getTamano();
                }//fin del for
                camino=0;
                int col  = campos2.count();
                for(int o=0;o<campos1.count();o++){
                    data = line.mid(camino,campos1[o].getTamano());
                    if(o!=columnaeliminar-campos2.count()){
                        if(lugma>-1){
                            for(int u=0;u<matriz[lugma][1].count();u++){
                               ui->tabla_cruzarlineal->setItem(matriz[lugma][1][u].toInt(),col+o,new QTableWidgetItem(data));
                            }//fin del for
                        }//fin del if
                    }else{
                        col-=1;
                    }
                    camino+=campos1[o].getTamano();
                }//fin del for
             }//fin del if
             if(line=="$")
                 empezar = true;
         }//fin del while

     }//fin del else

     ui->combocampos_cruzarlineal->addItem(QString::number(ui->tabla_cruzarlineal->columnCount()));
     int rowcount = ui->tabla_cruzarlineal->rowCount();
     int i=0;
      while(i<rowcount){
         QTableWidgetItem* item = ui->tabla_cruzarlineal->item(i,ui->tabla_cruzarlineal->columnCount()-1);
         if(item==NULL){
             ui->tabla_cruzarlineal->removeRow(i);
             rowcount--;
         }else{
             i++;
        }//fin del else
      }//fin del while


}
