#ifndef VER_H
#define VER_H

#include <QDialog>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <QList>
#include "campos.h"
using namespace std;
namespace Ui {
class ver;
}

class ver : public QDialog
{
    Q_OBJECT

public:
    explicit ver(QWidget *parent = 0);
    ~ver();

private slots:
    void on_pushButton_clicked();

    void on_comboarchivos_ver_activated(const QString &arg1);

private:
    QList<campos> camposa;
    Ui::ver *ui;
};

#endif // VER_H
