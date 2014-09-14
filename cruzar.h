#ifndef CRUZAR_H
#define CRUZAR_H
#include "campos.h"
#include "QString"
#include <QFile>
#include <QDialog>
#include <QList>
#include <QTextStream>
#include "fstream"
using namespace std;

namespace Ui {
class cruzar;
}

class cruzar : public QDialog
{
    Q_OBJECT

public:
    explicit cruzar(QWidget *parent = 0);
    ~cruzar();

private slots:
    void on_pushButton_clicked();

    void on_combocampos_cruzar_activated(const QString &arg1);

    void on_comboarchivo1_cruzar_activated(const QString &arg1);

    void on_comboarchivo2_cruzar_activated(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    QList <campos> campos1;
    QList <campos> campos2;
    QFile file1;
    QFile file2;
    Ui::cruzar *ui;
};

#endif // CRUZAR_H
