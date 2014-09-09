#include "registros.h"
#include "ui_registros.h"

static void process_line(const QByteArray &)
{
}

static void process_line(const QString &)
{
}

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

void registros::llenarllaves(){
    int avance =0;
    for(int l=0;l<campollave;l++){
         avance+=camposa[l].getTamano();
    }
    if(campollave!=-1){
        file.seek(0);
        QTextStream in1(&file);
        QString line1 = in1.readLine();
        bool empezar = false;
        while (!line1.isNull()) {
            line1 = in1.readLine();
              if(empezar){
               if(line1[0]!='*'){
                   llaves.append(line1.mid(avance,camposa[campollave].getTamano()));

                }
            }
            if(line1=="$"){
                empezar = true;

            }
    }

  }
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
    head = 0;
    endoffsetestruc=0;
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

    file.close();
    ui->lnumre_registros->setText("0");
    ui->lnombrecampo_registros->setText("");
    ui->lnumcampo_registros->setText("");
    ui->ltipocampo_registros->setText("");
    ui->ltamanocampo_registros->setText("");
    ui->lentradacampo_registros->setText("");
    ui->lesllave_registros->setText("");
    llaves.clear();
    camposa.clear();
    camposllenados.clear();
    head = 0;
    endoffsetestruc=0;
    campollave = -1;
    offsethead = 0;
    file.setFileName(ui->comboarchivos_registros->currentText());
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QTextStream in(&file);
        QString line = in.readLine();
        QStringList divisiones = line.split(" ");
        bool lla =false;
        if(divisiones[3]=="Sí"){

            lla=true;
            campollave = camposa.count();
        }
        endoffsetestruc+= line.length()+1;
        camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
        while (!line.isNull()) {
            line = in.readLine();
            process_line(line);
            endoffsetestruc+= line.length()+1;
           if(line=="|")
                break;
            QStringList divisiones = line.split(" ");
            bool lla =false;
            if(divisiones[3]=="Sí"){
                lla=true;
                campollave = camposa.count();
            }
            camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));

       }
       offsethead = endoffsetestruc+1;
       line = in.readLine();
       endoffsetestruc+=line.length()+1;
       head = line.toInt();
       endoffsetestruc+=2;
       ui->lnumcampo_registros->setText("1");
       ui->lnombrecampo_registros->setText(camposa[0].getNombre());
       ui->ltipocampo_registros->setText(camposa[0].getTipo());
       ui->ltamanocampo_registros->setText(QString::number(camposa[0].getTamano()));
       if(camposa[0].getEsLlave())
           ui->lesllave_registros->setText("Sí");
       else
           ui->lesllave_registros->setText("No");

       QString mask;
           if(camposa[0].getTipo()=="Entero"){
              for(int i=0;i<camposa[0].getTamano();i++)
                  mask+="0";
              ui->lentradacampo_registros->setInputMask(mask+"\0");
           }else{
               ui->lentradacampo_registros->setInputMask("");
               ui->lentradacampo_registros->setMaxLength(camposa[0].getTamano());
           }

          llenarllaves();


}

void registros::on_boton_agregar_campo_clicked()
{

    if((ui->lentradacampo_registros->text()=="" && ui->lesllave_registros->text()=="Sí" ) ){
        ui->lbanuncios_registros->setText("Llenar campo");
    }else{
       ui->lbanuncios_registros->setText("");
       bool disponible = true;
       QString cam = ui->lentradacampo_registros->text();
       for(int q=cam.length();q<camposa[ui->lnumcampo_registros->text().toInt()-1].getTamano();q++)
              cam+=' ';

       if(ui->lesllave_registros->text()=="Sí"){
          for(int comp=0;comp<llaves.count();comp++){
            if(llaves[comp]==cam){
                ui->lbanuncios_registros->setText("El registro ya existe");
                disponible = false;
            }
        }
        }
        if(disponible){
           int nc = ui->lnumcampo_registros->text().toInt();
           camposllenados.append(cam);
           if(ui->lnumcampo_registros->text().toInt()<camposa.count()){
            ui->lnumcampo_registros->setText(QString::number(nc+1));
            }else{
            ui->lnumcampo_registros->setText("1");
            nc=0;
            ui->lnumre_registros->setText(QString::number(ui->lnumre_registros->text().toInt()+1));
            QString mandar;
            for(int q=0;q<camposllenados.count();q++)
                 mandar+=camposllenados[q];
            mandar+='\n';
            if(head==-1){
                 QTextStream out(&file);
                 file.seek(file.size());
                 out << mandar;
                 out.flush();
            }else{
                int offsetin=0;
                for(int i=0;i<camposa.count();i++){
                    offsetin += camposa[i].getTamano();
                }
                offsetin++;
                offsetin *= (head-1);
                offsetin+=endoffsetestruc+1;
                      ////////////Escribir en archivo

                    QTextStream in1(&file);
                    QString line ;
                    file.seek(offsetin);
                    line = in1.readLine();
                    file.seek(offsetin);
                    in1<<mandar;
                    in1.flush();
                    QStringList nuevohead = line.split("*");
                    head = nuevohead[1].toInt();

                    file.seek(offsethead);
                    in1<<nuevohead[1];
                    in1.flush();


           }
             camposllenados.clear();
             llaves.clear();
             llenarllaves();

           }
           ui->lnombrecampo_registros->setText(camposa[nc].getNombre());
           ui->ltipocampo_registros->setText(camposa[nc].getTipo());
           ui->ltamanocampo_registros->setText(QString::number(camposa[nc].getTamano()));
           if(camposa[nc].getEsLlave())
               ui->lesllave_registros->setText("Sí");
           else
               ui->lesllave_registros->setText("No");
           QString mask;
            ui->lentradacampo_registros->setText("");
           if(camposa[nc].getTipo()=="Entero"){
            for(int i=0;i<camposa[nc].getTamano();i++)
                mask+="0";
                ui->lentradacampo_registros->setInputMask(mask+"\0");
           }else{
                ui->lentradacampo_registros->setInputMask("");
                ui->lentradacampo_registros->setMaxLength(camposa[nc].getTamano());
           }


         }
    }
}
