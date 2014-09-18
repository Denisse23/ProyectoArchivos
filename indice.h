#ifndef INDICE_H
#define INDICE_H
#include <QString>
class indice
{

   QString llave;
   QString RRN;
public:
    indice();
    indice(QString,QString);
    QString getLlave();
    int getllave(int);
    QString getRRN(char);
    void setLLave(QString);
    void setRRN(QString);

};

#endif // INDICE_H
