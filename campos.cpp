#include "campos.h"

campos::campos(){
}


campos::campos(QString n,QString t,int l,bool es){
    nombre=n;
    tipo=t;
    longitud=l;
    esllave=es;

}//fin del constructor

QString campos:: getNombre(){

     return nombre;
}

QString campos:: getTipo(){

        return tipo;
}

int campos::getLongitud(){
        return longitud;
}

bool campos::getEsLlave(){
        return esllave;
}

void campos::setNombre(QString x){
        nombre=x;
}

void campos::setTipo(QString t){
        tipo=t;
}

void campos::setlongitud(int l){

        longitud=l;
}

void campos::setEsLlave(bool b){
          esllave=b;
}


