#include "btree.h"

btree::btree()
{
}


QList<nodo> btree::getNodos(){
    return nodos;
}

void btree::setNodos(QList<nodo> n){
    nodos=  n;
}

void btree::insertNodo(nodo nod){
    nodos.append(nod);
}

int btree::insertIndice(indice in,int pos,int tipo){
    int pa = pos;
if(tipo==1){
  if(nodos.count()>0){
    if(!(nodos[pos].getSons()[0]==-1)){
        for(int i=0;i<nodos[pos].getData().count();i++){
            if(nodos[pos].getData()[i].getLlave()!=""){
                if(nodos[pos].getHijoIzquiero(i)!=-1 && in.getLlave()<nodos[pos].getData()[i].getLlave()){
                    insertIndice(in,nodos[pos].getHijoIzquiero(i),1);
                 }else if(i==nodos[pos].getData().count()-1){
                    insertIndice(in,nodos[pos].getHijoDerecho(i),1);
                }
            }else{
                insertIndice(in,nodos[pos].getHijoIzquiero(i),1);
                break;
            }

        }


    }else if(nodos[pos].getData()[61].getLlave()==""){
        nodos[pos].insertindice(in,nodos[pos].lugardisponible(in,1));
    }else{

        int lugarhijo = nodos[pos].inserttempdata(in,1);
        nodos[pos].inserttempson(lugarhijo,-1);
        pa = dividir(pos,1);

    }
  }else{
    nodos.append(nodo());
    nodos[pos].setIndice(in,0);
  }
 }else{
    if(nodos.count()>0){
      if(!(nodos[pos].getSons()[0]==-1)){
          for(int i=0;i<nodos[pos].getData().count();i++){
              if(nodos[pos].getData()[i].getLlave()!=""){
                  if(nodos[pos].getHijoIzquiero(i)!=-1 && in.getLlave().toInt()<nodos[pos].getData()[i].getLlave().toInt()){
                      insertIndice(in,nodos[pos].getHijoIzquiero(i),2);
                   }else if(i==nodos[pos].getData().count()-1){
                      insertIndice(in,nodos[pos].getHijoDerecho(i),2);
                  }
              }else{
                  insertIndice(in,nodos[pos].getHijoIzquiero(i),2);
                  break;
              }

          }


      }else if(nodos[pos].getData()[61].getLlave()==""){
          nodos[pos].insertindice(in,nodos[pos].lugardisponible(in,2));
      }else{

          int lugarhijo = nodos[pos].inserttempdata(in,2);
          nodos[pos].inserttempson(lugarhijo,-1);
          pa = dividir(pos,2);

      }
    }else{
      nodos.append(nodo());
      nodos[pos].setIndice(in,0);
    }
 }
  return pa;
}


int btree::dividir(int pos,int tipo){
    int pa=pos;
 if(tipo==1){
    indice temp = nodos[pos].removemitad();
    nodo tempiz;
    nodo tempder;
    for(int i=0;i<31;i++){
        if(i<30){
            tempiz.setIndice(nodos[pos].getData()[i],i);
            tempiz.setSon(nodos[pos].getSons()[i],i);
        }else{
            tempiz.setSon(nodos[pos].getSons()[i],i);
        }
    }
    int j =30;
    for(int i=0;i<32;i++){
        if(i<31){
            tempder.setIndice(nodos[pos].getData()[j],i);
            tempder.setSon(nodos[pos].getSons()[j],i);
        }else{
            tempder.setSon(nodos[pos].getSons()[j],i);
        }
        j++;
    }
    nodos.removeAt(pos);
    nodos.insert(pos,tempiz);
    nodos.append(tempder);
    int nuevaconeccion = nodos.count()-1;
    int pospadre=-1;
    for(int i=0;i<nodos.count();i++){
        for(int j=0;j<nodos[i].getSons().count();j++){
            if(nodos[i].getSons()[j]==pos){
                pospadre=i;
            }
        }
    }

    if(pospadre==-1){
        nodos.append(nodo());
        nodos[nodos.count()-1].setIndice(temp,0);
        nodos[nodos.count()-1].setSon(pos,0);
        nodos[nodos.count()-1].setSon(nuevaconeccion,1);
        pa=nodos.count()-1;
    }else{

        if(nodos[pospadre].getData()[62].getLlave()==""){
            int lugar = nodos[pospadre].lugardisponible(temp,1);
            nodos[pospadre].insertindice(temp,lugar);
            nodos[pospadre].insertson(nuevaconeccion,lugar+1);
            pa=pospadre;

        }

       else{
            int lugarhijo = nodos[pospadre].inserttempdata(temp,1);
            nodos[pospadre].inserttempson(lugarhijo,nuevaconeccion);
            dividir(pospadre,1);
        }

    }
 }else{
     indice temp = nodos[pos].removemitad();
     nodo tempiz;
     nodo tempder;
     for(int i=0;i<31;i++){
         if(i<30){
             tempiz.setIndice(nodos[pos].getData()[i],i);
             tempiz.setSon(nodos[pos].getSons()[i],i);
         }else{
             tempiz.setSon(nodos[pos].getSons()[i],i);
         }
     }
     int j =30;
     for(int i=0;i<32;i++){
         if(i<31){
             tempder.setIndice(nodos[pos].getData()[j],i);
             tempder.setSon(nodos[pos].getSons()[j],i);
         }else{
             tempder.setSon(nodos[pos].getSons()[j],i);
         }
         j++;
     }
     nodos.removeAt(pos);
     nodos.insert(pos,tempiz);
     nodos.append(tempder);
     int nuevaconeccion = nodos.count()-1;
     int pospadre=-1;
     for(int i=0;i<nodos.count();i++){
         for(int j=0;j<nodos[i].getSons().count();j++){
             if(nodos[i].getSons()[j]==pos){
                 pospadre=i;
             }
         }
     }

     if(pospadre==-1){
         nodos.append(nodo());
         nodos[nodos.count()-1].setIndice(temp,0);
         nodos[nodos.count()-1].setSon(pos,0);
         nodos[nodos.count()-1].setSon(nuevaconeccion,1);
         pa=nodos.count()-1;
     }else{

         if(nodos[pospadre].getData()[62].getLlave()==""){
             int lugar = nodos[pospadre].lugardisponible(temp,2);
             nodos[pospadre].insertindice(temp,lugar);
             nodos[pospadre].insertson(nuevaconeccion,lugar+1);
             pa=pospadre;

         }

        else{
             int lugarhijo = nodos[pospadre].inserttempdata(temp,2);
             nodos[pospadre].inserttempson(lugarhijo,nuevaconeccion);
             dividir(pospadre,2);
         }

     }
 }
    return pa;

}

QList<int> btree::buscarIndice(QString in,int pos,int tipo){
    int posnodo=-1;
    int posdata = -1;
    if(nodos.count()>0){
    if(tipo==1){
    if(!(nodos[pos].getSons()[0]==-1)){
        for(int i=0;i<nodos[pos].getData().count();i++){
            if(nodos[pos].getData()[i].getLlave()!=""){
                if(nodos[pos].getData()[i].getLlave()!=in){
                if(nodos[pos].getHijoIzquiero(i)!=-1 && in<nodos[pos].getData()[i].getLlave()){
                   buscarIndice(in,nodos[pos].getHijoIzquiero(i),1);
                 }else if(i==nodos[pos].getData().count()-1){
                    buscarIndice(in,nodos[pos].getHijoDerecho(i),1);
                }
                }else{
                    posnodo=pos;
                    posdata=i;
                    break;
                }
            }else{
                buscarIndice(in,nodos[pos].getHijoIzquiero(i),1);
                break;
            }
       }
    }else{
        for(int i=0;i<nodos[pos].getData().count();i++){
            if(nodos[pos].getData()[i].getLlave()==in){
                posnodo=pos;
                posdata=i;
                break;
            }
        }
    }

    }else{
        if(!(nodos[pos].getSons()[0]==-1)){
            for(int i=0;i<nodos[pos].getData().count();i++){
                if(nodos[pos].getData()[i].getLlave()!=""){
                    if(nodos[pos].getData()[i].getLlave()!=in){
                    if(nodos[pos].getHijoIzquiero(i)!=-1 && in.toInt()<nodos[pos].getData()[i].getLlave().toInt()){
                       buscarIndice(in,nodos[pos].getHijoIzquiero(i),2);
                     }else if(i==nodos[pos].getData().count()-1){
                        buscarIndice(in,nodos[pos].getHijoDerecho(i),2);
                    }
                    }else{
                        posnodo=pos;
                        posdata=i;
                        break;
                    }
                }else{
                    buscarIndice(in,nodos[pos].getHijoIzquiero(i),2);
                    break;
                }
            }
        }else{
            for(int i=0;i<nodos[pos].getData().count();i++){
                if(nodos[pos].getData()[i].getLlave().toInt()==in.toInt()){
                    posnodo=pos;
                    posdata=i;
                    break;
                }
            }
        }
    }
    }//fin primer if
    QList<int> mandar;
    mandar.append(posnodo);
    mandar.append(posdata);

    return mandar;

}
