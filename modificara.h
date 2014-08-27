#ifndef MODIFICARA_H
#define MODIFICARA_H

#include <QDialog>

namespace Ui {
class modificara;
}

class modificara : public QDialog
{
    Q_OBJECT

public:
    explicit modificara(QWidget *parent = 0);
    ~modificara();

private:
    Ui::modificara *ui;
};

#endif // MODIFICARA_H
