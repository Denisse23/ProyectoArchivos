#ifndef MODIFICARA_H
#define MODIFICARA_H

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
class modificara;
}

class modificara : public QDialog
{
    Q_OBJECT

public:
    explicit modificara(QWidget *parent = 0);
    ~modificara();

private slots:
    void on_bcargar_modificara_clicked();

    void on_comboarchivos_modificara_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_combocampos_modificar_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:

    QList<QString> archivos;
    QList<campos> camposa;
    QFile file;
    Ui::modificara *ui;
};

#endif // MODIFICARA_H
