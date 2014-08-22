#ifndef REGISTROS_H
#define REGISTROS_H

#include <QDialog>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <fstream>
#include <QList>
#include "campos.h"
using namespace std;

namespace Ui {
class registros;
}

class registros : public QDialog
{
    Q_OBJECT

public:

    QFile mainfile;
    explicit registros(QWidget *parent = 0);
    void Operate();
    void setFile(QString);
    ~registros();

private slots:
    void on_pushButton_clicked();

    void on_comboarchivos_registros_activated(const QString &arg1);

    void on_boton_agregar_campo_clicked();

private:
    QList<QString> llaves;
    QList<campos> camposa;
    QList<QString> camposllenados;
    Ui::registros *ui;
};

#endif // REGISTROS_H
