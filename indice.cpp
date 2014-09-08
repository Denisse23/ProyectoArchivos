#include "indice.h"

indice::indice()
{
}

indice::indice(QString llav,QString R){
    llave = llav;
    RRN = R;
}

QString indice::getLlave(){
    return llave;
}

QString indice::getRRN(){
    QString compRRN = "      ";
    for(int i=0;i<RRN.length();i++){
        compRRN[i]=RRN[i];
    }
    return compRRN;
}

void indice::setLLave(QString llav){
    llave = llav;
}

void indice::setRRN(QString R){
    RRN=R;
}
