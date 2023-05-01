#include "oublier.h"
#include "ui_oublier.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "connexion.h"
#include <QDebug>

oublier::oublier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oublier)
{
    ui->setupUi(this);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
              switch(ret){
              case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                  break;
              case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();

                  break;
              case(-1):qDebug() << "arduino is not available";
              }
               QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

}

oublier::~oublier()
{
    delete ui;
}
void oublier::on_Submit_clicked()
{



    QSqlQueryModel model;
QString RFID,cin,role,nom;


    QSqlQuery query("SELECT RFID,CIN,ROLE,NOM from EMPLOYEE WHERE RFID= '"+ui->RFID->text()+"';");

     while (query.next()) {
         RFID = query.value(0).toString();
         cin = query.value(1).toString();
         role =query.value(2).toString();
          nom=query.value(3).toString();
     }
A.write_to_arduino(nom.toUtf8());


if (ui->mdp_in->text()!=ui->mdp_in_2->text())
{
    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                    QObject::tr("Passwords don't match.\n"
                                "Click to retry."), QMessageBox::Retry);

}
    else if ((RFID!="") && (ui->mdp_in->text()!=""))
{

    query.prepare("UPDATE EMPLOYEE SET MDP= :mdp2   where cin= :cin2 ;");
    query.bindValue(":mdp2",ui->mdp_in->text() );
    query.bindValue(":cin2",cin );

    if (query.exec()) {QMessageBox::information(nullptr, QObject::tr("Done"),
                                            QObject::tr("Password changed.\n"
                                                        "Click OK to Continue."), QMessageBox::Ok);
this->hide();
        A.getserial()->close();
        g=new Gestions(nullptr,role);
 g->exec();}
    else
    {QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                               QObject::tr("Contact your administrator.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}
}
else    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                QObject::tr("Some fields are empty!.\n"
                            "Click to to retry."), QMessageBox::Retry);





}

void oublier::on_Submit_2_clicked()
{
    this->hide();

}


void oublier::on_Scan_clicked()
{


QString at=A.read_from_arduino();

  at=at.simplified();
  at.replace(" ","");

  if (at!="") ui->RFID->setText(at);

}
