#include "nodo.h"

nodo::nodo()
{
    QList<int> so;
    for(int i=0;i<64;i++){
        so.append(-1);
    }
    sons=so;
    QList<indice> in;
    for(int i=0;i<63;i++){
        in.append(indice("",""));
    }
    data = in;

}


QList < indice> nodo::getData(){
    return data;
}

QList<int > nodo:: getSons(){

    return sons;
}

void nodo::setData(QList < indice> d){
    data = d;
}

void nodo::setSons(QList<int> s){
    sons=s;
}

void nodo::setIndice(indice i,int lugar){
   if(lugar!=-1){
       data.replace(lugar,i);
   }

}

void nodo::setSon(int so, int lugar){
    if(lugar!=-1){
        sons.replace(lugar,so);
    }
}

bool nodo::hayhijos(){
    bool hay = false;
    for(int i=0;i<sons.count();i++){
        if(sons[i]!=-1){
            hay = true;
            break;
         }
    }
    return hay;

}

int  nodo::getHijoIzquiero(int lugar){
    return sons[lugar];
}

int nodo::getHijoDerecho(int lugar){
    return sons[lugar+1];
}
int nodo::lugardisponible(indice l,int tipo){
    int num=0;
    if(tipo==1){
    for(int i=0;i<data.count();i++){
        if(data[i].getLlave()!=""){
        if(l.getLlave()<data[i].getLlave()){
           num=i;
           break;
          }
        }else if(data[i].getLlave()==""){
            num=i;
            break;
        }

    }
    }else{
        for(int i=0;i<data.count();i++){
            if(data[i].getLlave()!=""){
            if(l.getLlave().toInt()<data[i].getLlave().toInt()){
               num=i;
               break;
              }
            }else if(data[i].getLlave()==""){
                num=i;
                break;
            }

        }
    }
    return num;
}
int nodo::haylugar(){
    int hay = -1;
    for(int i=0;i<62;i++){
        if(data[i].getLlave()==""){
            int hay=i;
            break;
         }
    }

    return hay;
}

int nodo::inserttempdata(indice in,int tipo){
    int temp = 63;
    if(tipo==1){
    for(int i=0;i<data.count();i++){
        if(in.getLlave()<data[i].getLlave()){
            temp=i;
            break;
         }
    }
    data.insert(temp,in);
    }else{
        for(int i=0;i<data.count();i++){
            if(in.getLlave().toInt()<data[i].getLlave().toInt()){
                temp=i;
                break;
             }
        }
    }
    return temp;
}

void nodo::inserttempson(int lugar,int nson){
    sons.insert(lugar+1,nson);
}

indice nodo::removemitad(){
    int mitad = (data.count()/2)-2;
    indice temp = data[mitad];
    data.removeAt(mitad);
    return temp;
}

void nodo::insertindice(indice in,int lugar){
    data.insert(lugar,in);
    data.removeAt(63);
}

void nodo::insertson(int s,int lugar){
    sons.insert(lugar,s);
    sons.removeAt(64);
}

