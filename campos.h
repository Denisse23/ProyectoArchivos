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
    int getLongitud();
    bool getEsLlave();

    void setNombre(QString);
    void setTipo(QString);
    void setlongitud(int);
    void setEsLlave(bool);

private:
    QString nombre;
    QString tipo;
    int longitud;
    bool esllave;



};

#endif // CAMPOS_H
