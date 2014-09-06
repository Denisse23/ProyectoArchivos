#include "modificara.h"
#include "ui_modificara.h"

modificara::modificara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modificara)
{
    ui->setupUi(this);
}

modificara::~modificara()
{
    delete ui;
}

void modificara::on_bcargar_modificara_clicked()
{
    ui->ltextos_modificar->setText("");
    for(int i=ui->comboarchivos_modificara->count()-1;i>=0;i--)
        ui->comboarchivos_modificara->removeItem(i);
    for(int i=ui->combocampos_modificar->count()-1;i>=0;i--)
        ui->combocampos_modificar->removeItem(i);
    archivos.clear();
    ui->lnombrecampo_modificar->setText("");
    ui->spintamano_modificar->setValue(1);
    ifstream verificar("archivoscreados.txt");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        archivos.append(QString::fromStdString(archivo));

    }
    archivos.removeAt(archivos.count()-1);
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

        if(mas==1){
            ui->comboarchivos_modificara->addItem(archivos[i]);
        }
        file.close();
      }



}

void modificara::on_comboarchivos_modificara_activated(const QString &arg1)
{
    file.close();
    ui->ltextos_modificar->setText("");
    for(int i=ui->combocampos_modificar->count()-1;i>=0;i--)
        ui->combocampos_modificar->removeItem(i);

        camposa.clear();
        ui->lnombrecampo_modificar->setText("");
        file.setFileName(ui->comboarchivos_modificara->currentText());
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
            if(line=="|")
                break;
            QStringList divisiones = line.split(" ");
            bool lla =false;
            if(divisiones[3]=="Sí")
                lla=true;
           camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));

       }
      ui->combocampos_modificar->addItem("Nuevo");
      for(int i=0;i<camposa.count();i++)
          ui->combocampos_modificar->addItem(QString::number(i+1));


}

void modificara::on_pushButton_clicked()
{
    if(camposa.count()>1){
        if(ui->combocampos_modificar->currentText()!="Nuevo"){
        int num = ui->combocampos_modificar->currentText().toInt();
        camposa.removeAt(num-1);
        ui->combocampos_modificar->removeItem(ui->combocampos_modificar->count()-1);
        ui->lnombrecampo_modificar->setText("");
        ui->spintamano_modificar->setValue(1);
    }else{
            ui->ltextos_modificar->setText("Debe seleccionar un campo");
        }
    }else{
        ui->ltextos_modificar->setText("Debe haber al menos un campo");
    }

}

void modificara::on_combocampos_modificar_activated(const QString &arg1)
{
    ui->ltextos_modificar->setText("");
    if(ui->combocampos_modificar->currentText()!="Nuevo"){
          int num = ui->combocampos_modificar->currentText().toInt();
          ui->lnombrecampo_modificar->setText(camposa[num-1].getNombre());
          ui->combotipo_modificar->setCurrentText(camposa[num-1].getTipo());
          ui->spintamano_modificar->setValue(camposa[num-1].getTamano());
          if(camposa[num-1].getEsLlave())
              ui->combollave_modificar->setCurrentText("Sí");
          else
              ui->combollave_modificar->setCurrentText("No");
    }else{
        ui->lnombrecampo_modificar->setText("");
        ui->spintamano_modificar->setValue(1);
        ui->combollave_modificar->setCurrentIndex(0);
    }
}

void modificara::on_pushButton_2_clicked()
{
    if(ui->combocampos_modificar->currentText()!="Nuevo"){
       if(ui->lnombrecampo_modificar->text()!=""){
       int num = ui->combocampos_modificar->currentText().toInt();
       bool hay = false;
       if(ui->combollave_modificar->currentText()=="Sí"){
           for(int i=0;i<camposa.count();i++){
               if(camposa[i].getEsLlave() && i!=num-1)
                   hay=true;
           }
       }
       if(hay){
         ui->ltextos_modificar->setText("El campo no puede ser llave");
       }else{
       camposa[num-1].setNombre(ui->lnombrecampo_modificar->text());
       camposa[num-1].setTipo(ui->combotipo_modificar->currentText());
       camposa[num-1].setTamano(ui->spintamano_modificar->text().toInt());
       if(ui->combollave_modificar->currentText()=="No")
           camposa[num-1].setEsLlave(false);
       else
           camposa[num-1].setEsLlave(true);

       }
    }else{
        ui->ltextos_modificar->setText("El campo necesita un nombre");
    }
    }else{
        ui->ltextos_modificar->setText("Nuevo no es un campo");
    }
    ui->lnombrecampo_modificar->setText("");
    ui->spintamano_modificar->setValue(1);
}

void modificara::on_pushButton_4_clicked()
{
    ui->ltextos_modificar->setText("");
    if(ui->combocampos_modificar->currentText()=="Nuevo"){
        bool hay = false;
        if(ui->combollave_modificar->currentText()=="Sí"){
            for(int i=0;i<camposa.count();i++){
                if(camposa[i].getEsLlave())
                    hay=true;
        }
        }
        if(hay){
            ui->ltextos_modificar->setText("El campo no puede ser llave");
        }else{
            bool nomre = false;
            for(int i=0;i<camposa.count();i++){
                    if(camposa[i].getNombre()==ui->lnombrecampo_modificar->text())
                        nomre=true;
            }
            if(nomre){
             ui->ltextos_modificar->setText("Ese nombre ya existe");
            }else{
            bool llave = true;
            if(ui->combollave_modificar->currentText()=="No")
                llave = false;
            camposa.append(campos(ui->lnombrecampo_modificar->text(),ui->combotipo_modificar->currentText(),ui->spintamano_modificar->text().toInt(),llave));
            ui->combocampos_modificar->addItem(QString::number(camposa.count()));
            }
      }
    }else{
        ui->ltextos_modificar->setText("Debe seleccionar ""Nuevo""");
    }
    ui->lnombrecampo_modificar->setText("");
    ui->spintamano_modificar->setValue(1);
}

void modificara::on_pushButton_3_clicked()
{

    QString mandar;
    foreach (campos k, camposa){
        mandar += k.getNombre()+" "+k.getTipo()+" "+QString::number(k.getTamano())+" ";
        if(k.getEsLlave())
            mandar+="Sí\n";
        else
            mandar+="No\n";

   }
   mandar+="|\n";
   mandar+="-1    \n";
   mandar+="$\n";

   QTextStream out(&file);
   file.seek(0);
   out<<mandar;
   file.resize(file.pos());
   file.close();
   ui->ltextos_modificar->setText("");
   ui->lnombrecampo_modificar->setText("");
   ui->spintamano_modificar->setValue(1);
   ui->combollave_modificar->setCurrentIndex(0);
   ui->combotipo_modificar->setCurrentIndex(0);
   for(int i=ui->comboarchivos_modificara->count()-1;i>=0;i--)
       ui->comboarchivos_modificara->removeItem(i);
   for(int i=ui->combocampos_modificar->count()-1;i>=0;i--)
       ui->combocampos_modificar->removeItem(i);

}
