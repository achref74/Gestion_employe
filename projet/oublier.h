#ifndef OUBLIER_H
#define OUBLIER_H

#include <QDialog>
#include "emp.h"
#include "gestions.h"
#include "arduino.h"

namespace Ui {
class oublier;
}

class oublier : public QDialog
{
    Q_OBJECT

public:
    explicit oublier(QWidget *parent = nullptr);
    ~oublier();
private slots:
    void on_Submit_clicked();


    void on_Submit_2_clicked();

    void on_Scan_clicked();

private:
    Ui::oublier *ui;
    Gestions *g;
    emp *e;
    Arduino A;
};

#endif // OUBLIER_H
