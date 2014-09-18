#ifndef REINDEXAR_H
#define REINDEXAR_H
#include "campos.h"
#include "indice.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QList>
#include "btree.h"
#include "nodo.h"
namespace Ui {
class reindexar;
}

class reindexar : public QDialog
{
    Q_OBJECT

public:
    explicit reindexar(QWidget *parent = 0);
    ~reindexar();

private slots:

    void on_pushButton_clicked();

    void on_comboarchivos_reindexar_activated(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    void Insercion();
    void InsercionE();
    QList<campos> camposa;
    QList<indice> indices;
    btree arbol;
    int campollave;
    Ui::reindexar *ui;
};

#endif // REINDEXAR_H
