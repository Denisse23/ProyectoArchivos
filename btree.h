#ifndef BTREE_H
#define BTREE_H
#include <QString>
#include "indice.h"
#include "nodo.h"
#include <QList>
class btree
{
    QList<nodo> nodos;

public:
    btree();
    QList<nodo> getNodos();
    void setNodos(QList<nodo>);
    int insertIndice(indice,int,int);
    int dividir(int,int);


};

#endif // BTREE_H
