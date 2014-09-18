#ifndef NODO_H
#define NODO_H
#include <QString>
#include "indice.h"
#include <QList>
class nodo
{
    QList<indice> data;
    QList<int> sons;
public:
    nodo();
    QList < indice> getData();
    QList<int> getSons();
    void setData(QList < indice>);
    void setSons(QList<int>);
    void setIndice(indice,int);
    void setSon(int, int);
    bool hayhijos();
    int  getHijoIzquiero(int);
    int getHijoDerecho(int);
    int lugardisponible(indice,int);
    int haylugar();
    int inserttempdata(indice,int);
    void inserttempson(int,int);
    indice removemitad();
    void insertindice(indice,int);
    void insertson(int,int);

};
#endif // NODO_H
