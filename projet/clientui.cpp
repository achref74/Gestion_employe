#include "clientui.h"
#include "ui_clientui.h"

#include "client.h"
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
#include "qrcodegen.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QBuffer>
#include <QDir>
#include <QDebug>

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>

#include <QMenu>


clientui::clientui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientui)
{
    ui->setupUi(this);

   ui->tableView->setModel(Etmp.afficher());
      ui->comboBox123->setModel(Etmp.setcinc());
     ui->comboBox->setModel(Etmp.setcinc());
 ui->lineEdit->setMaxLength(8);
     ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
      ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));
       ui->lineEdit_3->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));
       ui->lineEdit_16->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));
        ui->lineEdit_17->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));
 ui->lineEdit_19->setValidator(new QRegExpValidator(QRegExp("[2-3]*")));
   ui->lineEdit_20->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));
           ui->lineEdit_6 ->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));
           //
//ard

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


           QSqlQuery query("SELECT code FROM piste");
           while (query.next()) {
               QString code = query.value(0).toString();
               ui->comboBox_2->addItem(code);
           }
           QSqlQuery query2("SELECT NUM_SERVICE FROM ACTIVITE");
           while (query2.next()) {
               QString code = query2.value(0).toString();
               ui->comboBox_3->addItem(code);
           }
//cam
QString data;
           mCamera =new QCamera(this);
               mCameraViewfinder = new QCameraViewfinder(this);
               mCameraImageCapture = new QCameraImageCapture(mCamera,this);
               m = new QVBoxLayout;
               mOptionsmenu = new QMenu("Ouvrir",this);
               mOuvrir = new QAction("Ouvrir",this);
               mCapturer = new QAction("Capturer",this);
               mSauv = new QAction("Sauvegarder",this);

               mOptionsmenu->addActions({mOuvrir,mCapturer,mSauv});
               ui->Camera->setMenu(mOptionsmenu);
                mCamera->setViewfinder(mCameraViewfinder);
               m->addWidget(mCameraViewfinder);
               m->setMargin(0);
                ui->scrollArea->setLayout(m);
                data="";
                 //while (data=="")
                     //data=A.read_from_arduino();
                  data=data.simplified();
                   data.replace(" ","");
                    qInfo()<<"test= "<<data<<endl;
            //

                connect(mOuvrir,&QAction::triggered, [&](){

                    mCamera->start();



                });
                connect(mCapturer,&QAction::triggered, [&](){
                mCamera->stop();
                });
                connect(mSauv,&QAction::triggered, [&](){
                auto filename= QFileDialog::getSaveFileName(this,"Capture","/",
                                             "(*.Jpg;*.Jpeg)");
                if (filename.isEmpty())
                {return ;}
                mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
                QImageEncoderSettings imageEncoderSettings;
                imageEncoderSettings.setCodec("image.jpeg");
                imageEncoderSettings.setResolution(1600, 1200);
                mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
                mCamera->setCaptureMode(QCamera::CaptureStillImage);
                mCamera->start();
                mCamera->searchAndLock();
                mCameraImageCapture->capture(filename);
                mCamera->unlock();


});
}

clientui::~clientui()
{
    delete ui;
}


//ajouter
void clientui::on_pushButton_3_clicked()
{
    //
    int total=0;
    QSqlQuery   query("SELECT POINT_VIDANGE,POINTS_CAFE,POINT_LAVAGE FROM ACTIVITE where NUM_SERVICE= "+ ui->lineEdit_nums->text() );

               while (query.next()) {
                   int vidange = query.value(0).toInt();
                   int cafe = query.value(1).toInt();
                   int lavage = query.value(2).toInt();
                    total=vidange+cafe+lavage;

               }
               QSqlQuery   query2("SELECT FINANCE FROM PISTE where CODE= "+ ui->lineEdit_code->text() );

                          while (query.next()) {
                              int N = query.value(0).toInt();

                              if (N>50) total+=3; else total+=2;

                          }

    //
                          int nbp=total;
             //
    int cinc=ui->lineEdit->text().toInt();
    QString nomc=ui->lineEdit_2->text();
    QString prenomc=ui->lineEdit_3->text();
    QString adressec=ui->lineEdit_4->text();

    QString paiement=ui->lineEdit_6->text();
     QString code=ui->lineEdit_code->text();
 int num_service=ui->lineEdit_nums->text().toInt();
    client c(cinc, nomc, prenomc, adressec,nbp , paiement, code,num_service );

QRegExp regex_email("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,}");
        if (!regex_email.exactMatch(adressec)) {
            QMessageBox::warning(this, "Erreur", "L'email n'est pas valide.");
            return;
        }

        bool test=c.ajouter();

        if(test){
        ui->tableView->setModel(Etmp.afficher());
      ui->comboBox123->setModel(Etmp.setcinc());
      //  ui->comboBox_2->setModel(Etmp.setcinc());
            QMessageBox::information(nullptr, QObject::tr("cancel"),QObject::tr("Ajout effectué\n" "click cancel to exit."), QMessageBox::Cancel);

        }

            else QMessageBox::critical(nullptr ,QObject::tr("cancel"),QObject::tr("ajout non effectué. \n" " click cancel to exit") );

       // QLineEdit* lineEdit_5 = new QLineEdit();
      //  QIntValidator* validator = new QIntValidator();
       // lineEdit_5->setValidator(validator);
}


//modifier



void clientui::on_pushButton_clicked()
{   //int cinc=ui->lineEdit->text().toInt();
    QString nomc=ui->lineEdit_16->text();
    QString prenomc=ui->lineEdit_17->text();

    QString adressec=ui->lineEdit_18->text();
    client c(ui->comboBox123->currentText().toInt(),ui->lineEdit_16->text(),ui->lineEdit_17->text(),ui->lineEdit_18->text(),ui->lineEdit_19->text().toInt(),ui->lineEdit_20->text(),ui->lineEdit_21->text(),ui->lineEdit_9->text().toInt());


    QRegExp regex_email("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,}");
            if (!regex_email.exactMatch(adressec)) {
                QMessageBox::warning(this, "Erreur", "L'email n'est pas valide.");
                return;
            }



    bool test=c.modifier();




    if(test){
        //actualiser
    ui->tableView->setModel(Etmp.afficher());
       QMessageBox::information(nullptr, QObject::tr("cancel"),QObject::tr("modification effectué\n" "click cancel to exit."), QMessageBox::Cancel);

    }

        else QMessageBox::critical(nullptr ,QObject::tr("cancel"),QObject::tr("modification non effectué. \n" " click cancel to exit") );
}



/*void clientui::on_comboBox_2_activated(int index)
{
    QSqlQuery query;

        query.prepare("select * from  CLIENT  where CINC=:CINC ");

        query.bindValue(":CINC",ui-> comboBox_2 ->currentText().toInt());

        if(query.exec())

            while(query.next())

    {


        ui->lineEdit_16 ->setText(query.value(1).toString()) ;
        ui->lineEdit_17 ->setText(query.value(2).toString()) ;
        ui->lineEdit_18->setText(query.value(3).toString()) ;
        ui->lineEdit_19->setText(query.value(4).toString()) ;
        ui->lineEdit_20->setText(query.value(5).toString()) ;
        ui->lineEdit_21->setText(query.value(6).toString()) ;


    }   }*/

/*void clientui::on_pushButton_2_clicked()
{
    int cinc=ui->comboBox_2->currentText().toInt();
    bool test=Etmp.supprimer(cinc);

    if(test){
        //actualiser
ui->tableView->setModel(Etmp.afficher());
ui->comboBox_2->setModel(Etmp.setcinc());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectué\n" "click cancel to exit."), QMessageBox::Cancel);

    }

        else QMessageBox::critical(nullptr ,QObject::tr("not ok"),QObject::tr("suppression non effectué. \n" " click cancel to exit") );

}*/



void clientui::on_comboBox123_activated(const QString &arg1)
{
    QSqlQuery query;


        query.prepare("select * from  CLIENT  where CINC=:CINC ");

        query.bindValue(":CINC",ui-> comboBox123 ->currentText().toInt());


        if(query.exec())

            while(query.next())

    {


        ui->lineEdit_16->setText(query.value(1).toString()) ;
        ui->lineEdit_17 ->setText(query.value(2).toString()) ;
        ui->lineEdit_18->setText(query.value(3).toString()) ;
        ui->lineEdit_19->setText(query.value(4).toString()) ;
        ui->lineEdit_20->setText(query.value(5).toString()) ;
        ui->lineEdit_21->setText(query.value(6).toString()) ;
        ui->lineEdit_9->setText(query.value(7).toString()) ;


    }
}

void clientui::on_comboBox_activated(const QString &arg1)

{
    int cinc=ui->comboBox->currentText().toInt();
    bool test=Etmp.supprimer(cinc);

    if(test){
        //actualiser
ui->tableView->setModel(Etmp.afficher());
ui->comboBox->setModel(Etmp.setcinc());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectué\n" "click cancel to exit."), QMessageBox::Cancel);

    }

        else QMessageBox::critical(nullptr ,QObject::tr("not ok"),QObject::tr("suppression non effectué. \n" " click cancel to exit") );
}
void clientui::on_supprimer_clicked()
{
    int cinc=ui->comboBox->currentText().toInt();
        bool test=Etmp.supprimer(cinc);

        if(test){
            //actualiser
    ui->tableView->setModel(Etmp.afficher());
    ui->comboBox->setModel(Etmp.setcinc());
            QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectué\n" "click cancel to exit."), QMessageBox::Cancel);

        }

            else QMessageBox::critical(nullptr ,QObject::tr("not ok"),QObject::tr("suppression non effectué. \n" " click cancel to exit") );




}
void clientui::on_pushButton_6_clicked()
{
    client Etmp;
     ui->tableView->setModel(Etmp.tri(ui->comboBox_tri->currentText()));
}


void clientui::on_pushButton_7_clicked()
{
    ui->tableView->setModel(Etmp.afficher());
}

void clientui::on_lineEdit_chercher_textChanged(const QString &arg1)
{
    client Etmp;
        ui->tableView->setModel(Etmp.rechercher(ui->comboBox_chercher->currentText(),ui->lineEdit_chercher->text()));
}
void clientui::on_pushButton_2_clicked()
{
   ui->lineEdit_chercher->clear();
}
void clientui::on_pushButton_5_clicked()
{
    s=new stat_comb();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();
}

void clientui::on_pushButton_4_clicked()
{
    QPdfWriter pdf("PDF");
    QPainter painter(&pdf);

    // set background color
    painter.setBackground(QBrush(QColor("#464646")));
    painter.eraseRect(0, 0, pdf.width(), pdf.height());

    int v = 4000;
    painter.setPen(QPen(QColor("#ffc34a")));
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    painter.drawText(2000, 1400, "LISTE DES CLIENTS");

    painter.setPen(QPen(QColor("#ffc34a")));
    painter.setFont(QFont("Arial", 15));
    painter.drawRect(100, 100, 9400, 2500);
    painter.drawRect(100, 3000, 9400, 500);


    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.setPen(QPen(QColor("#ffc34a")));
    painter.drawText(500, 3300, "CINC ");
    painter.drawText(2000, 3300, "NOMC");
    painter.drawText(4000, 3300, "PRENOMC");
    painter.drawText(6000, 3300, "ADRESSEC");
    painter.drawText(8000, 3300, "NBP");
    painter.drawText(10000, 3300, "PAIEMENT");
    painter.drawText(12000, 3300, "CODE");

    QSqlQuery query;
    query.prepare("select * from CLIENT");
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
         painter.drawText(10000, v, query.value(5).toString());
          painter.drawText(12000, v, query.value(6).toString());
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



void clientui::on_pushButton_QR_clicked()
{
    QString text ="detail d un client  :"+ ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString()
                        +" /"+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toString()
                        +"/ "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2)).toString()
                        +"/ "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString()
                        +"/ "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4)).toString()
                        +"/ "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5)).toString()
                        +"/ "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),6)).toString()
                        +"/ "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),7)).toString();



               using namespace qrcodegen;
                 QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                 qint32 sz = qr.getSize();
                 QImage im(sz,sz, QImage::Format_RGB32);
                   QRgb black = qRgb(0, 0, 0);
                   QRgb white = qRgb(255,255,255);
                 for (int y = 0; y < sz; y++)
                   for (int x = 0; x < sz; x++)
                     im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                 ui->label_13->setPixmap( QPixmap::fromImage(im.scaled(71,81,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void clientui::on_pushButton_8_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Open Image"), "Pictures/image", tr("Image Files (*.png *.jpg *.bmp)"));
       if (!fileName.isEmpty()) {
           ui->lineEdit_6->setText(fileName);
       }
}




void clientui::on_comboBox_2_activated(int index)
{
    ui->lineEdit_code->setText(ui->comboBox_2->currentText());
}


void clientui::on_comboBox_3_activated(int index)
{
    ui->lineEdit_nums->setText(ui->comboBox_3->currentText());
}


