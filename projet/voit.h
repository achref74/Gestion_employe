#ifndef VOIT_H
#define VOIT_H

#include <QDialog>

#include "voiture.h"
#include <arduino.h>

namespace Ui {
class voit;
}

class voit : public QDialog
{
    Q_OBJECT

public:
    explicit voit(QWidget *parent = nullptr);
    ~voit();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();




    void on_pushButton_5_clicked();





    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();


    void on_pushButton_13_clicked();





    void on_tabWidget_currentChanged(int index);

private:
    Ui::voit *ui;
    Voiture v;
       Arduino A;
            QByteArray data;
};

#endif // VOIT_H
