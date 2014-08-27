#include "nuevo.h"
#include "ui_nuevo.h"

nuevo::nuevo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nuevo)
{
    ui->setupUi(this);
}

nuevo::~nuevo()
{
    delete ui;
}

void nuevo::on_bagregar_nuevo_clicked()
{
    ui->tablacampos_nuevo->setEditTriggers(false);
    QString campo = ui->lnombrecampo_nuevo->text();
    QString tipo = ui->combotipo_nuevo->currentText();
    int tamano = ui->spintamano_nuevo->text().toInt();
    bool llave = false;
    if(ui->combollave_nuevo->currentText()=="Sí"){
        llave = true;
        ui->combollave_nuevo->setVisible(false);
        ui->combollave_nuevo->removeItem(1);
    }

    if(campo!=""){
    bool disponible = true;
    foreach(campos k, listacampos){
        if(k.getNombre()==campo)
            disponible = false;
    }

    if(disponible){
        listacampos.append(campos(campo,tipo,tamano,llave));
        int count = ui->tablacampos_nuevo->rowCount();
        ui->tablacampos_nuevo->insertRow(count);
        ui->tablacampos_nuevo->setItem(count,0,new QTableWidgetItem(campo));
        ui->tablacampos_nuevo->setItem(count,1,new QTableWidgetItem(tipo));
        ui->tablacampos_nuevo->setItem(count,2,new QTableWidgetItem(QString::number(tamano)));
        if(llave)
            ui->tablacampos_nuevo->setItem(count,3,new QTableWidgetItem("Sí"));
        else
            ui->tablacampos_nuevo->setItem(count,3,new QTableWidgetItem("No"));
    }
    }
    ui->lnombrecampo_nuevo->setText("");


}

void nuevo::on_bcrear_nuevo_clicked()
{

    if(ui->lnombrearchivo_nuevo->text()!="" && ui->lnombrearchivo_nuevo->text()!="Ingrese un nombre de archivo" && listacampos.count()>0){
       //nombrando el archivo
        nombrearchivo= (ui->lnombrearchivo_nuevo->text()+".txt").toStdString();
        ifstream verificar("archivoscreados.txt");
        bool esta = false;
        while(verificar.good()){
            string comparar;
            verificar >> comparar;
            if(comparar == nombrearchivo)
                esta = true;
        }
        verificar.close();
        if(esta ==false){
            char nombrea[30];
            int lennom = nombrearchivo.length();
            for(int i=0;i<lennom;i++)
                nombrea[i] = nombrearchivo[i];
            if(lennom<30)
             nombrea[lennom]='\0';
        //agregar el nombre del archivo a "archivoscreados"
        ofstream inscribir("archivoscreados.txt", fstream::app);
        inscribir<<nombrea<<endl;
        inscribir.close();
        //limpiar campos
        ui->lnombrearchivo_nuevo->setText("");
        //Crear archivo

        QString mandar;
        foreach (campos k, listacampos){
            mandar += k.getNombre()+" "+k.getTipo()+" "+QString::number(k.getTamano())+" ";
            if(k.getEsLlave())
                mandar+="Sí\n";
            else
                mandar+="No\n";

       }
       mandar+="|\n";
       mandar+="-1    \n";
       mandar+="$\n";
       ofstream file(nombrea);
       file<<mandar.toStdString()<<endl;
       file.close();


        //Borrar tabla

        foreach (campos k, listacampos){
            ui->tablacampos_nuevo->removeRow(0);
            listacampos.removeAt(0);
         }
        if(ui->combollave_nuevo->isVisible()==false){
        ui->combollave_nuevo->setVisible(true);
        ui->combollave_nuevo->addItem("Sí");
        }
        }else{
            ui->lnombrearchivo_nuevo->setText("El nombre ya exista, escoga otro");
        }
        ui->lnombrecampo_nuevo->setText("");
        ui->combollave_nuevo->setEnabled(true);
        ui->combollave_nuevo->setItemText(1,"Si");
    }else{
        if(listacampos.count()==0)
            ui->lnombrecampo_nuevo->setText("Agregar al menos un campo");
        else
            ui->lnombrearchivo_nuevo->setText("Ingrese un nombre de archivo");
    }


}
