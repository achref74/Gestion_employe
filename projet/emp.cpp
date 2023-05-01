#include "emp.h"
#include "ui_emp.h"
#include "employe.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QString>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include "connexion.h"
//#include "webaxwidget.h"
#include <QPainter>

//#include "salle.h"
#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QTextDocument>
#include <QDebug>
//#include <temperature.h>

emp::emp(QWidget *parent,const QString& str) :
    QDialog(parent),
    ui(new Ui::emp)
{
    ui->setupUi(this);
       //




    ui->Connected->setText("Connecté en tant que: "+ str);
    if (str!="Admin")
    {ui->tabWidget->removeTab(0);
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(1);
}


    //ui->tableView->setModel(Etmp.afficher());
    ui->comboBox->setModel(Etmp.setid());
    ui->comboBox_2->setModel(Etmp.setid());
    ui->lineEdit_cin->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
    ui->lineEdit_nom->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(
            QRegularExpression("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}")
    );
    ui->lineEdit_mail->setValidator(validator);
 ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));

 ///arduino
 ///
 ///
 int ret=A.connect_arduino(); // lancer la connexion à arduino
           switch(ret){
           case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
               break;
           case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
              break;
           case(-1):qDebug() << "arduino is not available";
           }
            QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
            //
}




emp::~emp()
{
    delete ui;
}

void emp::on_pushButtonajouter_clicked()
{
    int cin=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString adresse=ui->lineEdit_ad->text();
    QString mail=ui->lineEdit_mail->text();
        QString absence=ui->lineEdit->text();
        QString mdp=ui->motdepasse->text();
        QString mdp_2=ui->motdepasse_2->text();
        QString role=ui->Role->currentText();
        QString rfid=ui->RFID->text();
if (mdp==mdp_2)
        {
    employe e(cin, nom, prenom, adresse, mail,absence,mdp,role,rfid);



        bool test=e.ajouter();

        if(test){
        ui->tableView->setModel(Etmp.afficher());
        ui->comboBox->setModel(Etmp.setid());
        ui->comboBox_2->setModel(Etmp.setid());
            QMessageBox::information(nullptr, QObject::tr("cancel"),QObject::tr("Ajout effectué\n" "click cancel to exit."), QMessageBox::Cancel);

        }

            else QMessageBox::critical(nullptr ,QObject::tr("cancel"),QObject::tr("ajout non effectué. \n" " click cancel to exit") );

}
else
    QMessageBox::critical(nullptr, QObject::tr("Password error"),
                          QObject::tr("Passwords don't match.\n"
                                      "Click to Retry."), QMessageBox::Retry);
}

void emp::on_supprimer_clicked()
{
    int cin=ui->comboBox->currentText().toInt();
    bool test=Etmp.supprimer(cin);

    if(test){
        //actualiser
ui->tableView->setModel(Etmp.afficher());
ui->comboBox_2->setModel(Etmp.setid());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectué\n" "click cancel to exit."), QMessageBox::Cancel);

    }

        else QMessageBox::critical(nullptr ,QObject::tr("not ok"),QObject::tr("suppression non effectué. \n" " click cancel to exit") );

}



void emp::on_comboBox_2_activated(const QString &arg1)
{
    QSqlQuery query;

        query.prepare("select * from  employee  where CIN=:CIN ");

        query.bindValue(":CIN",ui->comboBox_2->currentText().toInt());

        if(query.exec())

            while(query.next())

    {


        ui->lineEditNN->setText(query.value(1).toString()) ;
        ui->lineEdit_P->setText(query.value(2).toString()) ;
        ui->lineEdit_A->setText(query.value(3).toString()) ;
        ui->lineEdit_OO->setText(query.value(4).toString()) ;
         ui->lineEdit_3->setText(query.value(5).toString()) ;



    }
}

void emp::on_pushButtonMODIFIER_clicked()
{
    employe e(ui->comboBox_2->currentText().toInt(),ui->lineEditNN->text(),ui->lineEdit_P->text(),ui->lineEdit_A->text(),ui->lineEdit_OO->text(),  ui->lineEdit_3->text());
    bool test=e.modifier();




    if(test){
        //actualiser
    ui->tableView->setModel(Etmp.afficher());
       QMessageBox::information(nullptr, QObject::tr("cancel"),QObject::tr("modification effectué\n" "click cancel to exit."), QMessageBox::Cancel);

    }

        else QMessageBox::critical(nullptr ,QObject::tr("cancel"),QObject::tr("modification non effectué. \n" " click cancel to exit") );
}
/*
void emp::on_mod1_clicked()
{
    employe e(ui->comboBox_2->currentText().toInt(),ui->lineEditNN->text(),ui->lineEdit_P->text(),ui->lineEdit_A->text(),ui->lineEdit_OO->text(),ui->lineEdit_3->text());
    bool test=e.modifier();




    if(test){
        //actualiser
    ui->tableView->setModel(Etmp.afficher());
       QMessageBox::information(nullptr, QObject::tr("cancel"),QObject::tr("modification effectué\n" "click cancel to exit."), QMessageBox::Cancel);

    }

        else QMessageBox::critical(nullptr ,QObject::tr("cancel"),QObject::tr("modification non effectué. \n" " click cancel to exit") );
}*/



void emp::on_pushButton_4_clicked()
{
    {
        employe Etmp;
         ui->tableView->setModel(Etmp.afficher5(ui->comboBox_4->currentText()));
    }
}


void emp::on_pushButton_5_clicked()
{
    ui->tableView->setModel(Etmp.afficher());
}



//void emp::on_lineEdit_textChanged(const QString &arg1)
//{
    //employe Etmp;
   // ui->tableView->setModel(Etmp.afficher4(ui->comboBox_3->currentText(),ui->lineEdit->text()));
//}
void emp::on_pushButton1_clicked()
{
   ui->lineEdit_2->clear();
}

void emp::on_pushButton_2_clicked()

{
    QPdfWriter pdf("C:/Users/akrem/Downloads/achref/achref/achref/PDF/emplyee.pdf");
    QPainter painter(&pdf);

    // set background color
    painter.setBackground(QBrush(QColor("#464646")));
    painter.eraseRect(0, 0, pdf.width(), pdf.height());

    int v = 4000;
    painter.setPen(QPen(QColor("#ffc34a")));
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    painter.drawText(2000, 1400, "LISTE DES EMPLOYES");

    painter.setPen(QPen(QColor("#ffc34a")));
    painter.setFont(QFont("Arial", 15));
    painter.drawRect(100, 100, 9400, 2500);
    painter.drawRect(100, 3000, 9400, 500);


    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.setPen(QPen(QColor("#ffc34a")));
    painter.drawText(500, 3300, "CIN");
    painter.drawText(2000, 3300, "NOM");
    painter.drawText(4000, 3300, "PRENOM");
    painter.drawText(6000, 3300, "ADRESSE");
    painter.drawText(8000, 3300, "MAIL");
    painter.drawText(8500, 3300, "ABSENCE");

    QSqlQuery query;
    query.prepare("select * from employee");
    query.exec();
    while (query.next())
    {
        painter.setFont(QFont("Arial", 10));
        painter.setPen(QPen(QColor("#ffc34a")));
        painter.drawText(500, v, query.value(0).toString());
        painter.drawText(2000, v, query.value(1).toString());
        painter.drawText(4000, v, query.value(2).toString());
        painter.drawText(6000, v, query.value(3).toString());
        painter.drawText(8000, v, query.value(4).toString());
        painter.drawText(8500, v, query.value(5).toString());
        //painter.drawText(8500, v, query.value(5).toString());

        // Draw horizontal line after writing text for each row
        painter.setPen(QPen(QColor("#ffc34a")));
        painter.drawLine(100, v+50, 9500, v+50);

        v = v + 350;
    }

    // Move this line to the end of the while loop
    painter.setPen(QPen(QColor("#ffc34a")));
    painter.drawRect(100, 3000, 9400, 9000);

    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
        QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}



void emp::on_lineEdit_2_textChanged(const QString &arg1)
{
    employe Etmp;
     ui->tableView->setModel(Etmp.afficher4(ui->comboBox_3->currentText(),ui->lineEdit_2->text()));
}

void emp::on_pushButton_3_clicked()
{
    s=new stat_comb();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();
}



void emp::on_tabWidget_currentChanged(int index)
{
    ui->tableView->setModel(Etmp.afficher());
}


void emp::on_pushButtonajouter_2_clicked()
{
    QString at=A.read_from_arduino();

      at=at.simplified();
      at.replace(" ","");

      if (at!="") ui->RFID->setText(at);
}

