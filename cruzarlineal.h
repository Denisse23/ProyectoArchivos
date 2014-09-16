#ifndef CRUZARLINEAL_H
#define CRUZARLINEAL_H

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
class cruzarlineal;
}

class cruzarlineal : public QDialog
{
    Q_OBJECT

public:
    explicit cruzarlineal(QWidget *parent = 0);
    ~cruzarlineal();

private slots:
    void on_pushButton_clicked();

    void on_comboarchivo1_cruzarlineal_activated(const QString &arg1);

    void on_comboarchivo2_cruzarlineal_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_combocampos_cruzarlineal_activated(const QString &arg1);

private:
    QList <campos> campos1;
    QList <campos> campos2;
    QFile file1;
    QFile file2;
    Ui::cruzarlineal *ui;
};

#endif // CRUZARLINEAL_H
