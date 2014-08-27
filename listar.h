#ifndef LISTAR_H
#define LISTAR_H
#include <fstream>
using namespace std;
#include <QDialog>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "campos.h"
namespace Ui {
class listar;
}

class listar : public QDialog
{
    Q_OBJECT

public:
    explicit listar(QWidget *parent = 0);
    ~listar();

private slots:
    void on_pushButton_clicked();

    void on_comboarchivos_listar_activated(const QString &arg1);

private:
    Ui::listar *ui;
    QList<campos> camposa;
    int endoffsetestruc;
};

#endif // LISTAR_H
