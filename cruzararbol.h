#ifndef CRUZARARBOL_H
#define CRUZARARBOL_H

#include <QDialog>
#include "campos.h"
#include "QString"
#include <QFile>
#include <QDialog>
#include <QList>
#include <QTextStream>
#include "fstream"
using namespace std;
namespace Ui {
class cruzararbol;
}

class cruzararbol : public QDialog
{
    Q_OBJECT

public:
    explicit cruzararbol(QWidget *parent = 0);
    ~cruzararbol();

private slots:
    void on_pushButton_clicked();

    void on_comboarchivo1_cruzararbol_activated(const QString &arg1);

    void on_comboarchivo2_cruzararbol_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_combocampos_cruzararbol_activated(const QString &arg1);

private:
    QList <campos> campos1;
    QList <campos> campos2;
    QFile file1;
    QFile file2;
    Ui::cruzararbol *ui;
};

#endif // CRUZARARBOL_H
