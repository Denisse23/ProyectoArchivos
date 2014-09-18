#include "cruzararbol.h"
#include "ui_cruzararbol.h"

cruzararbol::cruzararbol(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cruzararbol)
{
    ui->setupUi(this);
}

cruzararbol::~cruzararbol()
{
    delete ui;
}

void cruzararbol::on_pushButton_clicked()
{
    file1.close();
    file2.close();
    campos1.clear();
    campos2.clear();
    ui->comboarchivo1_cruzararbol->clear();
    ui->comboarchivo2_cruzararbol->clear();
    for(int i=ui->tabla_cruzararbol->rowCount()-1;i>=0;i--)
        ui->tabla_cruzararbol->removeRow(i);
    for(int i=ui->tabla_cruzararbol->columnCount();i>=0;i--)
        ui->tabla_cruzararbol->removeColumn(i);
    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboarchivo1_cruzararbol->addItem(QString::fromStdString(archivo));
        ui->comboarchivo2_cruzararbol->addItem(QString::fromStdString(archivo));
    }
    verificar.close();

    ui->comboarchivo1_cruzararbol->removeItem(ui->comboarchivo1_cruzararbol->count()-1);
    ui->comboarchivo2_cruzararbol->removeItem(ui->comboarchivo2_cruzararbol->count()-1);
}

void cruzararbol::on_comboarchivo1_cruzararbol_activated(const QString &arg1)
{
    campos1.clear();
    for(int i=ui->tabla_cruzararbol->rowCount()-1;i>=0;i--)
        ui->tabla_cruzararbol->removeRow(i);
    for(int i=ui->tabla_cruzararbol->columnCount();i>=0;i--)
        ui->tabla_cruzararbol->removeColumn(i);
    ui->combocampos_cruzararbol->clear();
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
            }

            campos1.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));

        }
}

void cruzararbol::on_comboarchivo2_cruzararbol_activated(const QString &arg1)
{
    campos2.clear();
    for(int i=ui->tabla_cruzararbol->rowCount()-1;i>=0;i--)
        ui->tabla_cruzararbol->removeRow(i);
    for(int i=ui->tabla_cruzararbol->columnCount();i>=0;i--)
        ui->tabla_cruzararbol->removeColumn(i);
    ui->combocampos_cruzararbol->clear();
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
            }

            campos2.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));

        }
}

void cruzararbol::on_pushButton_2_clicked()
{
for(int i=ui->tabla_cruzararbol->rowCount()-1;i>=0;i--)
    ui->tabla_cruzararbol->removeRow(i);
for(int i=ui->tabla_cruzararbol->columnCount();i>=0;i--)
    ui->tabla_cruzararbol->removeColumn(i);
ui->combocampos_cruzararbol->clear();

if(ui->comboarchivo1_cruzararbol->currentText()!=ui->comboarchivo2_cruzararbol->currentText()){
      for(int i=0;i<campos1.count();i++){
          for(int j=0;j<campos2.count();j++){
              if(campos1[i].getNombre()==campos2[j].getNombre() && campos1[i].getTamano()==campos2[j].getTamano()
                  && campos1[i].getTipo()== campos2[j].getTipo()){
                  if(campos1[i].getEsLlave() || campos2[j].getEsLlave())
                  ui->combocampos_cruzararbol->addItem(campos1[i].getNombre());
                  j=campos2.count();
              }
          }
      }
  }
}

void cruzararbol::on_combocampos_cruzararbol_activated(const QString &arg1)
{
    for(int i=ui->tabla_cruzararbol->rowCount()-1;i>=0;i--)
        ui->tabla_cruzararbol->removeRow(i);
    for(int i=ui->tabla_cruzararbol->columnCount();i>=0;i--)
        ui->tabla_cruzararbol->removeColumn(i);

    bool campo1=true;
    for(int i=0;i<campos2.count();i++){
        if(campos2[i].getNombre()==ui->combocampos_cruzararbol->currentText() && campos2[i].getEsLlave()==true)
            campo1=false;
    }
    int columnaeliminar=0;
    int campollave=0;
    int tamano=0;
    if(campo1==false){
    for(int i=0;i<campos1.count();i++){
        ui->tabla_cruzararbol->insertColumn(i);
       if(campos1[i].getNombre().length()>campos1[i].getTamano())
            ui->tabla_cruzararbol->setColumnWidth(i,campos1[i].getNombre().length()*10);
        else
            ui->tabla_cruzararbol->setColumnWidth(i,campos1[i].getTamano()*15);
        ui->tabla_cruzararbol->setHorizontalHeaderItem(i,new QTableWidgetItem(campos1[i].getNombre()));
        if(campos1[i].getNombre()==ui->combocampos_cruzararbol->currentText() && campos1[i].getEsLlave()==false)
            campollave = i;

    }

    for(int i=0;i<campos2.count();i++){
        tamano+=campos2[i].getTamano();
        int col =campos1.count()+i;
        ui->tabla_cruzararbol->insertColumn(col);
        if(campos2[i].getNombre().length()>campos2[i].getTamano())
            ui->tabla_cruzararbol->setColumnWidth(col,campos2[i].getNombre().length()*10);
        else
            ui->tabla_cruzararbol->setColumnWidth(col,campos2[i].getTamano()*15);
         ui->tabla_cruzararbol->setHorizontalHeaderItem(col,new QTableWidgetItem(campos2[i].getNombre()));
         if(campos2[i].getNombre()==ui->combocampos_cruzararbol->currentText() && campos2[i].getEsLlave()==true)
             columnaeliminar=col;
    }
    }else{
        for(int i=0;i<campos2.count();i++){
            ui->tabla_cruzararbol->insertColumn(i);
           if(campos2[i].getNombre().length()>campos2[i].getTamano())
                ui->tabla_cruzararbol->setColumnWidth(i,campos2[i].getNombre().length()*10);
            else
                ui->tabla_cruzararbol->setColumnWidth(i,campos2[i].getTamano()*15);
            ui->tabla_cruzararbol->setHorizontalHeaderItem(i,new QTableWidgetItem(campos2[i].getNombre()));
            if(campos2[i].getNombre()==ui->combocampos_cruzararbol->currentText() && campos2[i].getEsLlave()==false)
                campollave = i;
        }

        for(int i=0;i<campos1.count();i++){
            tamano+=campos1[i].getTamano();
            int col =campos2.count()+i;
            ui->tabla_cruzararbol->insertColumn(col);
            if(campos1[i].getNombre().length()>campos1[i].getTamano())
                ui->tabla_cruzararbol->setColumnWidth(col,campos1[i].getNombre().length()*10);
            else
                ui->tabla_cruzararbol->setColumnWidth(col,campos1[i].getTamano()*15);
             ui->tabla_cruzararbol->setHorizontalHeaderItem(col,new QTableWidgetItem(campos1[i].getNombre()));
             if(campos1[i].getNombre()==ui->combocampos_cruzararbol->currentText() && campos1[i].getEsLlave()==true)
                 columnaeliminar=col;
        }
    }
     ui->tabla_cruzararbol->removeColumn(columnaeliminar);
     btree arbol;
     QString nombreindicea;
     int cantr=0;

     if(campo1==false){
         nombreindicea = file2.fileName()+"x";
         cantr=campos2[columnaeliminar-campos1.count()].getTamano();
     }else{
         nombreindicea = file1.fileName()+"x";
         cantr=campos1[columnaeliminar-campos2.count()].getTamano();
     }
     nombreindicea[nombreindicea.length()-5] = 'b',nombreindicea[nombreindicea.length()-4] = 't';
     nombreindicea[nombreindicea.length()-3] = 'i',nombreindicea[nombreindicea.length()-2] = 'd';
     QFile filea(nombreindicea);
     if (!filea.open(QIODevice::ReadWrite | QIODevice::Text))
      return;
     QTextStream in(&filea);
     QString line;
     while(!in.atEnd()){
         line=in.readLine();
         nodo temp;
         QList<indice> indices;
         QList<int> hijos;
         int camino=0;
         for(int i=0;i<63;i++){
             indices.append(indice(line.mid(camino,cantr),line.mid(cantr+camino,10)));
             camino+=cantr+10;
         }
         camino-=cantr+6;
         for(int i=0;i<64;i++){
             hijos.append(line.mid(camino,4).toInt());
             camino+=4;
         }
         temp.setData(indices);
         temp.setSons(hijos);
         arbol.insertNodo(temp);
     }
     filea.close();
     int padre=arbol.getNodos().count()-1;


     ui->comboarchivo1_cruzararbol->addItem(QString::number(padre));

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
                     int rowc = ui->tabla_cruzararbol->rowCount();
                     int camino=0;
                     ui->tabla_cruzararbol->insertRow(rowc);
                     QString data;
                     for(int o=0;o<campos1.count();o++){
                         data= line.mid(camino,campos1[o].getTamano());
                        ui->tabla_cruzararbol->setItem(rowc,o,new QTableWidgetItem(data));
                      camino+=campos1[o].getTamano();
                   }
                 }
             }
             if(line=="$")
                 empezar=true;

         }

       QTextStream in2(&file2);
       QString line2;
        for(int i=0;i<ui->tabla_cruzararbol->rowCount();i++){
            QTableWidgetItem* item = ui->tabla_cruzararbol->item(i,campollave);
            QString llave = item->text();
            QList<int> partes;
            if(campos2[columnaeliminar-campos1.count()].getTipo()=="Char"){
                partes = arbol.buscarIndice(llave,padre,1);
             }else{
                partes = arbol.buscarIndice(llave,padre,2);
            }
            if(partes[0]!=-1){
                file2.seek(arbol.getNodos()[partes[0]].getData()[partes[1]].getRRN('a').toInt());
                line2=in2.readLine();
                int camino=0;
                for(int k=0;k<campos2.count();k++){
                    if(k!=columnaeliminar-campos1.count()){
                        ui->tabla_cruzararbol->setItem(i,k+(campos1.count()-1),new QTableWidgetItem(line2.mid(camino,campos2[k].getTamano())));
                    }
                    camino+=campos2[k].getTamano();
                }
            }
        }

       }else{
         QTextStream in(&file2);
         QString line;
         bool empezar = false;
         while(!in.atEnd()){
             line = in.readLine();
             if(empezar){
                 if(line[0]!='*'){
                     int rowc = ui->tabla_cruzararbol->rowCount();
                     int camino=0;
                     ui->tabla_cruzararbol->insertRow(rowc);
                     QString data;
                     for(int o=0;o<campos2.count();o++){
                         data= line.mid(camino,campos2[o].getTamano());
                         ui->tabla_cruzararbol->setItem(rowc,o,new QTableWidgetItem(data));
                      camino+=campos2[o].getTamano();
                   }
                }
              }
             if(line=="$")
                 empezar=true;

         }

         QTextStream in2(&file1);
         QString line2;
          for(int i=0;i<ui->tabla_cruzararbol->rowCount();i++){
              QTableWidgetItem* item = ui->tabla_cruzararbol->item(i,campollave);
              QString llave = item->text();
              QList<int> partes;
              if(campos1[columnaeliminar-campos2.count()].getTipo()=="Char"){
                  partes = arbol.buscarIndice(llave,padre,1);
               }else{
                  partes = arbol.buscarIndice(llave,padre,2);
              }
              if(partes[0]!=-1){
                  file1.seek(arbol.getNodos()[partes[0]].getData()[partes[1]].getRRN('a').toInt());
                  line2=in2.readLine();
                  int camino=0;
                  for(int k=0;k<campos1.count();k++){
                      if(k!=columnaeliminar-campos2.count()){
                          ui->tabla_cruzararbol->setItem(i,k+(campos2.count()-1),new QTableWidgetItem(line2.mid(camino,campos1[k].getTamano())));
                      }
                      camino+=campos1[k].getTamano();
                  }
              }
          }


     }


     ui->combocampos_cruzararbol->addItem(QString::number(ui->tabla_cruzararbol->columnCount()));
     int rowcount = ui->tabla_cruzararbol->rowCount();
     int i=0;
      while(i<rowcount){
         QTableWidgetItem* item = ui->tabla_cruzararbol->item(i,ui->tabla_cruzararbol->columnCount()-1);
         if(item==NULL){
             ui->tabla_cruzararbol->removeRow(i);
             rowcount--;
         }else{
             i++;
        }
      }
}
