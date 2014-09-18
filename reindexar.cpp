#include "reindexar.h"
#include "ui_reindexar.h"

reindexar::reindexar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reindexar)
{
    ui->setupUi(this);
}

reindexar::~reindexar()
{
    delete ui;
}
void reindexar::Insercion(){
    int i, j;
    indice temp;
    for (i = 1; i < indices.count(); i++){
        temp = indices[i];
        j = i-1;
    while ( ((j >= 0 &&indices[j].getLlave()> temp.getLlave()) ) ){
        indices[j+1]=indices[j];
        j--;
    }
    indices[j+1]=temp;
    }
}//fin metodo ordenar

//ordenar enteros
void reindexar::InsercionE(){
    int i, j;
    indice temp;
    for (i = 1; i < indices.count(); i++){
        temp = indices[i];
        j = i-1;
    while ( ((j >= 0 &&indices[j].getLlave().toInt()> temp.getLlave().toInt()) ) ){
        indices[j+1]=indices[j];
        j--;
    }
        indices[j+1]=temp;
    }
}//fin metodo ordenar


void reindexar::on_pushButton_clicked()
{
    campollave = -1;
    camposa.clear();
    indices.clear();
    arbol.getNodos().clear();
    ui->comboarchivos_reindexar->clear();
    ui->comboarchivos_reindexar->clear();
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
    //solo cargara archivos con registros
    for(int i=0;i<archivos.count();i++){
        QFile file (archivos[i]);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QTextStream in(&file);
        QString line ;
        int mas = 0;
        bool tienellave = false;
        bool activar = false;
        while (!in.atEnd()){
            line = in.readLine();
            if(line.contains("Sí"))
                tienellave = true;
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

        if(mas>=1 && tienellave){
          ui->comboarchivos_reindexar->addItem(archivos[i]);
        }
        file.close();
      }
}

void reindexar::on_comboarchivos_reindexar_activated(const QString &arg1)
{
    campollave = -1;
    camposa.clear();
    indices.clear();
    btree arboll;
    arbol = arboll;
    QFile file(arg1);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
         return;
     QTextStream in(&file);
     QString line ;
     bool parar = false;
     bool empezar  = false;
     int offllave =0;
     int RRN=0;
     int offsetarbol=0;
     int pa=0;
     while (!in.atEnd()){
         line = in.readLine();
        if(line=="|")
            parar = true;
        //////////leer estructura
          if(parar==false){
          QStringList divisiones = line.split(" ");
          bool lla =false;
          if(divisiones[3]=="Sí"){
              lla=true;
              campollave = camposa.count();
          }
          camposa.append(campos(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
         }//fin leer estructura
          /////////////////leer registros
          if(empezar)
              RRN++;
          if(empezar && line[0]!='*'){
             QString llave  = line.mid(offllave,camposa[campollave].getTamano());
             indices.append(indice(llave.toUpper(),QString::number(RRN)));
             if(camposa[campollave].getTipo()=="Char"){
                 pa= arbol.insertIndice(indices[indices.count()-1],pa,1);
             }else{
                 pa= arbol.insertIndice(indices[indices.count()-1],pa,2);
             }

          }
          if(line=="$"){
              empezar = true;
              for(int i=0;i<campollave;i++){
                  offllave+=camposa[i].getTamano();
              }
           }
          offsetarbol+=line.toUtf8().length()+1;
     }
     file.close();

}

void reindexar::on_pushButton_2_clicked()
{
    if(ui->comboarchivos_reindexar->currentText()!=""){
    //ordenar los indices
    if(camposa[campollave].getTipo()=="Entero")
        InsercionE();
    else
        Insercion();

    QString nombreindicea = ui->comboarchivos_reindexar->currentText()+"x";
    nombreindicea[nombreindicea.length()-5] = 'b',nombreindicea[nombreindicea.length()-4] = 't';
    nombreindicea[nombreindicea.length()-3] = 'i',nombreindicea[nombreindicea.length()-2] = 'd';
    QFile filea(nombreindicea);
    if (!filea.open(QIODevice::ReadWrite | QIODevice::Text))
     return;
    QTextStream outa(&filea);
    QString mandara;
    for(int i=0;i<arbol.getNodos().count();i++){
        for(int j=0;j<arbol.getNodos()[i].getData().count();j++){
            mandara+=arbol.getNodos()[i].getData()[j].getLlave()+arbol.getNodos()[i].getData()[j].getRRN('l');
        }

        for(int j=0;j<arbol.getNodos()[i].getSons().count();j++){
            QString hijo ="    ";
            QString hi=QString::number(arbol.getNodos()[i].getSons()[j]);
            for(int o=0;o<hi.length();o++){
                hijo[o]=hi[o];
            }
           mandara+=hijo;
        }
        mandara+='\n';

    }
     ui->comboarchivos_reindexar->addItem(QString::number(arbol.getNodos().count()));

     outa<<mandara;
     filea.resize(filea.pos());
     filea.close();
    QString nombreindice = ui->comboarchivos_reindexar->currentText();
    nombreindice[nombreindice.length()-4] = 'l',nombreindice[nombreindice.length()-3] = 'i';
    nombreindice[nombreindice.length()-2] = 'd',nombreindice[nombreindice.length()-1] = 'x';
    QFile file(nombreindice);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
         return;
     QTextStream out(&file);
     QString mandar1;

        for(int i=0;i<indices.count();i++){
           mandar1+=(indices[i].getLlave()+indices[i].getRRN('l'))+'\n';
        }
        out<<mandar1;
        file.resize(file.pos());
     file.close();
    ui->comboarchivos_reindexar->clear();
    }
}
