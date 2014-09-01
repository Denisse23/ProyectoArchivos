#ifndef BORRAR_H
#define BORRAR_H

#include <QDialog>

#include <QDialog>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <fstream>
#include <QList>
#include "campos.h"
namespace Ui {
class borrar;
}

class borrar : public QDialog
{
    Q_OBJECT

public:
    explicit borrar(QWidget *parent = 0);
    ~borrar();

private slots:
    void on_pushButton_clicked();

    void on_comboarchivos_borrar_activated(const QString &arg1);


    void on_pushButton_2_clicked();


    void on_combocampos_borrar_activated(const QString &arg1);

private:
    QList<campos> camposa;
    Ui::borrar *ui;
};

#endif // BORRAR_H
