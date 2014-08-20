#ifndef CAMPOS_H
#define CAMPOS_H
#include <QString>
class campos
{
public:
    campos(QString,QString,int,bool);
    campos();
    QString getNombre();
    QString getTipo();
    int getTamano();
    bool getEsLlave();

    void setNombre(QString);
    void setTipo(QString);
    void setTamano(int);
    void setEsLlave(bool);

private:
    QString nombre;
    QString tipo;
    int tamano;
    bool esllave;



};

#endif // CAMPOS_H
