#ifndef BUSCAR_H
#define BUSCAR_H

#include <QDialog>
#include <QStringList>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <QFile>
#include <QTextStream>
#include <QStringRef>

namespace Ui {
class buscar;
}

class buscar : public QDialog
{
    Q_OBJECT

public:
    explicit buscar(QWidget *parent = 0);
    ~buscar();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //void on_comboarchivos_buscar_activated(const QString &arg1);

    void on_comboarchivos_buscar_activated(const QString &arg1);

private:
    Ui::buscar *ui;

};



#endif // BUSCAR_H
