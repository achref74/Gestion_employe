#ifndef GESTIONS_H
#define GESTIONS_H

#include <QDialog>

#include "emp.h"





namespace Ui {
class Gestions;
}

class Gestions : public QDialog
{
    Q_OBJECT

public:
    explicit Gestions(QWidget *parent = nullptr,const QString& str = "");
    ~Gestions();

private slots:
    void on_pushButton_emp_clicked();








private:
    Ui::Gestions *ui;
    emp *e;




    QString role;

};

#endif // GESTIONS_H
