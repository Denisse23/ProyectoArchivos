#ifndef EXPORTAR_H
#define EXPORTAR_H

#include <QDialog>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <fstream>
#include "campos.h"
using namespace std;
namespace Ui {
class exportar;
}

class exportar : public QDialog
{
    Q_OBJECT

public:
    explicit exportar(QWidget *parent = 0);
    ~exportar();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboarchivos_exportar_activated(const QString &arg1);

private:
    QList<campos> camposa;
    QFile file;
    Ui::exportar *ui;
};

#endif // EXPORTAR_H
