#include "gestions.h"
#include "ui_gestions.h"

Gestions::Gestions(QWidget *parent,const QString& str) :
    QDialog(parent),
    ui(new Ui::Gestions)
{
    ui->setupUi(this);
    role =str;
    if (str!="Admin")
    ui->pushButton_emp->hide();
}

Gestions::~Gestions()
{
    delete ui;
}

void Gestions::on_pushButton_emp_clicked()
{
    e=new emp(this,role);
    e->exec();
}






