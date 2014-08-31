#ifndef COMPACTAR_H
#define COMPACTAR_H

#include <QFile>
#include <QDialog>
#include <QTextStream>

namespace Ui {
class compactar;
}

class compactar : public QDialog
{
    Q_OBJECT

public:
    explicit compactar(QWidget *parent = 0);
    ~compactar();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::compactar *ui;
};

#endif // COMPACTAR_H
