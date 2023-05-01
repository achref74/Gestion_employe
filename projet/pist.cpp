#include "pist.h"
#include "ui_pist.h"

#include "Piste.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QString>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include "connexion.h"
#include <QPainter>
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
#include "arduino.h"

pist::pist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pist)
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
    ui->tableView->setModel(Etmp.afficher());
    ui->comboBox->setModel(Etmp.setid());
    ui->comboBox_3->setModel(Etmp.setid());
    ui->comboBox_5->setModel(Etmp.setnom());
}

pist::~pist()
{
    delete ui;
}


void pist::on_pushButtonajouter_clicked()
{
    int code=ui->lineEdit_code->text().toInt();
    QString finance=ui->lineEdit_f->text();
    QString borne_recharge=ui->lineEdit_b->text();
    QString disponibilite=ui->lineEdit_d->text();

   Piste p(code,finance, borne_recharge, disponibilite);



        bool test=p.ajouter();

        if(test){
        ui->tableView->setModel(Etmp.afficher());
        ui->comboBox->setModel(Etmp.setid());
        ui->comboBox_3->setModel(Etmp.setid());
            QMessageBox::information(nullptr, QObject::tr("cancel"),QObject::tr("Ajout effectué\n" "click cancel to exit."), QMessageBox::Cancel);

        }

            else QMessageBox::critical(nullptr ,QObject::tr("cancel"),QObject::tr("ajout non effectué. \n" " click cancel to exit") );

}

void pist::on_supprimer_clicked()
{
    int code=ui->comboBox->currentText().toInt();
    bool test=Etmp.supprimer(code);

    if(test){
        //actualiser
ui->tableView->setModel(Etmp.afficher());
ui->comboBox_3->setModel(Etmp.setid());
ui->comboBox->setModel(Etmp.setid());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectué\n" "click cancel to exit."), QMessageBox::Cancel);

    }

        else QMessageBox::critical(nullptr ,QObject::tr("not ok"),QObject::tr("suppression non effectué. \n" " click cancel to exit") );

}



/*void pist::on_comboBox_2_activated(const QString &arg1)
{
    QSqlQuery query;

        query.prepare("select * from  PISTE  where CODE=:CODE ");

        query.bindValue(":CODE",ui->comboBox_2->currentText().toInt());

        if(query.exec())

            while(query.next())

    {
        ui->lineEditNN->setText(query.value(1).toString()) ;
        ui->lineEdit_P->setText(query.value(2).toString()) ;
        ui->lineEdit_A->setText(query.value(3).toString()) ;
    }
}*/

void pist::on_pushButtonMODIFIER_clicked()
{
    Piste e(ui->comboBox_3->currentText().toInt(),ui->lineEditf->text(),ui->lineEdit_bb->text(),ui->lineEdit_dd->text());
    bool test=e.modifier();




    if(test){
        //actualiser
        ui->tableView->setModel(Etmp.afficher());
       QMessageBox::information(nullptr, QObject::tr("cancel"),QObject::tr("modification effectué\n" "click cancel to exit."), QMessageBox::Cancel);

    }

        else QMessageBox::critical(nullptr ,QObject::tr("cancel"),QObject::tr("modification non effectué. \n" " click cancel to exit") );
}

/*void pist::on_comboBox_2_activated(int index)
{
    QSqlQuery query;

        query.prepare("select * from  PISTE  where CODE=:CODE ");

        query.bindValue(":CODE",ui->comboBox_2->currentText().toInt());

        if(query.exec())

            while(query.next())

    {
        ui->lineEditNN->setText(query.value(1).toString()) ;
        ui->lineEdit_P->setText(query.value(2).toString()) ;
        ui->lineEdit_A->setText(query.value(3).toString()) ;
    }
}*/

void pist::on_comboBox_3_activated(int index)
{
    QSqlQuery query;

        query.prepare("select * from  PISTE  where CODE=:CODE ");

        query.bindValue(":CODE",ui->comboBox_3->currentText().toInt());

        if(query.exec())

            while(query.next())

    {
        ui->lineEditf->setText(query.value(1).toString()) ;
        ui->lineEdit_bb->setText(query.value(2).toString()) ;
        ui->lineEdit_dd->setText(query.value(3).toString()) ;
    }
}

void pist::on_lineEdit_textChanged(const QString &arg1)
{
    Piste Etmp;
        ui->tableView->setModel(Etmp.afficherecherch(ui->comboBox_2->currentText(),ui->lineEdit->text()));
}

void pist::on_pushButton_clicked()
{
    Piste Etmp;
     ui->tableView->setModel(Etmp.affichertri(ui->comboBox_4->currentText()));
}

void pist::on_pushButton_2_clicked()
{
    QPdfWriter pdf("C:/Users/ben turkia/OneDrive/Bureau/ska/PDF/piste.pdf");
    QPainter painter(&pdf);

    // set background color
    painter.setBackground(QBrush(QColor("#464646")));
    painter.eraseRect(0, 0, pdf.width(), pdf.height());

    int v = 4000;
    painter.setPen(QPen(QColor("#ffc34a")));
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    painter.drawText(2000, 1400, "LISTE DES PISTES");

    painter.setPen(QPen(QColor("#ffc34a")));
    painter.setFont(QFont("Arial", 15));
    painter.drawRect(100, 100, 9400, 2500);
    painter.drawRect(100, 3000, 9400, 500);


    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.setPen(QPen(QColor("#ffc34a")));
    painter.drawText(500, 3300, "CODE ");
    painter.drawText(1000, 3300, "FINANCE ");
    painter.drawText(2000, 3300, "BORNE");
    painter.drawText(5000, 3300, "DISPONIBILITE");


    QSqlQuery query;
    query.prepare("select * from PISTE");
    query.exec();
    while (query.next())
    {
        painter.setFont(QFont("Arial", 10));
        painter.setPen(QPen(QColor("#ffc34a")));
        painter.drawText(500, v, query.value(0).toString());
        painter.drawText(1000, v, query.value(1).toString());
        painter.drawText(2000, v, query.value(2).toString());
        painter.drawText(5000, v, query.value(3).toString());


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

void pist::on_pushButton_3_clicked()
{
    s=new stat_comb();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();
}

void pist::on_comboBox_5_activated(const QString &arg1)
{
    QSqlQuery query;

           query.prepare("select * from  PISTE  where BORNE=:BORNE ");

           query.bindValue(":BORNE",ui->comboBox_5->currentText());

           if(query.exec())

               while(query.next())

       {
        QString nom,sp;
       // QString sp;

           //ui->lineEdit->setText(query.value(3).toString()) ;
           nom = query.value(3).toString();
           //sp = query.value(3).toString();


           data.append(QString("%1,.").arg(nom));
            A.write_to_arduino(data);

       }
}


