#ifndef REGISTROS_H
#define REGISTROS_H

#include <QDialog>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFile>

using namespace std;

namespace Ui {
class registros;
}

class registros : public QDialog
{
    Q_OBJECT

public:

    QFile mainfile;
    explicit registros(QWidget *parent = 0);
    void Operate();
    void setFile(QString);
    ~registros();

private:
    Ui::registros *ui;
};

#endif // REGISTROS_H
