#ifndef NUEVO_H
#define NUEVO_H
#include <QString>
#include <QList>
#include <QDialog>
#include "campos.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <QFile>

using namespace std;
namespace Ui {
class nuevo;
}

class nuevo : public QDialog
{
    Q_OBJECT

public:
    explicit nuevo(QWidget *parent = 0);
    ~nuevo();

private slots:
    void on_bagregar_nuevo_clicked();

    void on_bcrear_nuevo_clicked();

private:

    QList<campos> listacampos;
    Ui::nuevo *ui;
};

#endif // NUEVO_H
