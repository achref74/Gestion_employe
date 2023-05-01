#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include<QRegExpValidator>
#include "connexion.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_seconnecter_2_clicked()
{
    connexion c;
QString Nom,mdp,role;

    c.createconnexion();
        QSqlQuery query("SELECT MDP, CONCAT(NOM,PRENOM),ROLE AS NOM_UT FROM EMPLOYEE WHERE NOM || PRENOM = '" + ui->nomut_in_2->text() + "'");

            while (query.next()) {
                mdp = query.value(0).toString();
                 Nom = query.value(1).toString();
                role = query.value(2).toString();

            }




       if ((mdp==ui->mdp_in_2->text()) && (Nom==ui->nomut_in_2->text()))
       {
           bool test=true;
           test=c.createconnexion();
           if(test)
           {
               QMessageBox::information(nullptr, QObject::tr("database is open"),
                                        QObject::tr("connection successful.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);

        this->hide();
               g=new Gestions(nullptr,role);

               g->exec();


           }
           else
               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                     QObject::tr("connection failed.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);



       }
       else {

           QMessageBox::critical(nullptr, QObject::tr("Password or username incorrect"),
                                 QObject::tr("Please check your password and username or try again later.\n"
                                             ), QMessageBox::Retry);



       }



}

void MainWindow::on_oublie_2_clicked()
{


    o= new oublier();
    o->show();


}






