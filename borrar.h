#ifndef BORRAR_H
#define BORRAR_H

#include <QDialog>

namespace Ui {
class borrar;
}

class borrar : public QDialog
{
    Q_OBJECT

public:
    explicit borrar(QWidget *parent = 0);
    ~borrar();

private:
    Ui::borrar *ui;
};

#endif // BORRAR_H
