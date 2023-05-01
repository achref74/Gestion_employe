#include "voit.h"
#include "ui_voit.h"
#include <QMessageBox>
#include "voiture.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QTextStream>
#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>
#include <QFile>
#include <cmath>
#include"notification.h"
notification N;
using namespace QtCharts;

voit::voit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::voit)
{
    ui->setupUi(this);
    ui->tableView->setModel(v.afficher());
    int ret=A.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
}

voit::~voit()
{
    delete ui;
}

void voit::on_pushButton_2_clicked()
{
    QString matricule=ui->lineEdit_10->text();
    QString marque=ui->comboBox_2->currentText();
    int puissance=ui->lineEdit_12->text().toInt();
    QString type_voltage=ui->lineEdit_13->text();
int etat_initial=ui->comboBox_7->currentText().toInt();
double charge=ui->lineEdit_15->text().toDouble();
    double dimension_benne=ui->lineEdit_16->text().toDouble();
QDate date_recharge=ui->dateEdit->date();

   Voiture v(matricule,marque,puissance,type_voltage,etat_initial,charge,dimension_benne,date_recharge );



        bool test=v.ajouter();

        if(test){A.write_to_arduino("1");
            if(ui->comboBox_7->currentText().toInt()==1)
           {
                N.notification_ajoutvoiture();}
        ui->tableView->setModel(v.afficher());


            QMessageBox::information(nullptr, QObject::tr("cancel"),QObject::tr("Ajout effectué\n" "click cancel to exit."), QMessageBox::Cancel);

            QString nomFile ="His";
                                QFile file("C:/Users/LENOVO/Documents/"+nomFile+".txt");

                                QString finalmsg="fichier ajouter avec succes";
                                 if(!file.exists()){
                                 finalmsg="fichier cree avec succes";
                                 }
                                file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                                QTextStream txt(&file);
                                  QString d_info = QDateTime::currentDateTime().toString();

                                QString message2=d_info+" - Une voiture a été ajoutée avec une matricule:  "+ matricule +"\n";
                                txt << message2;


        }

            else QMessageBox::critical(nullptr ,QObject::tr("cancel"),QObject::tr("ajout non effectué. \n" " click cancel to exit") );

}
void voit::on_pushButton_clicked()
{
    QString matricule=ui->lineEdit_19->text();
    bool test=v.supprimer(matricule);

    if(test){
        N.notification_supprimervoiture();
        //actualiser
ui->tableView->setModel(v.afficher());

        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectué\n" "click cancel to exit."), QMessageBox::Cancel);
        QString nomFile ="His";
                            QFile file("C:/Users/LENOVO/Documents/"+nomFile+".txt");

                            QString finalmsg="fichier ajouter avec succes";
                             if(!file.exists()){
                             finalmsg="fichier cree avec succes";
                             }
                            file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                            QTextStream txt(&file);
                              QString d_info = QDateTime::currentDateTime().toString();

                            QString message2=d_info+" - Une voiture a été supprimé avec une matricule:  "+ matricule +"\n";
                            txt << message2;

    }

        else QMessageBox::critical(nullptr ,QObject::tr("not ok"),QObject::tr("suppression non effectué. \n" " click cancel to exit") );


}






void voit::on_pushButton_3_clicked()
{
   QString matricule=ui->lineEdit_20->text();
        QSqlQuery query;
        query.prepare("SELECT matricule,marque,puissance,type_voltage,etat_initial,charge,dimension_benne,date_recharge  FROM voiture WHERE matricule = :matricule");
        query.bindValue(":matricule",matricule);
        if (!query.exec()) {
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

        while (query.next()) {

            QString matricule =query.value(0).toString();
            QString marque = query.value(1).toString();
    int puissance = query.value(2).toInt();
    QString type_voltage = query.value(3).toString();
 //int etat_initial = query.value(4).toInt();
      double charge = query.value(5).toDouble();
      double dimension_benne = query.value(6).toDouble();
 QDate date_recharge =query.value(7).toDate();
            // Afficher les données dans les QLineEdit correspondants

            ui->lineEdit->setText(matricule);
        //    ui->lineEdit_2->setText(marque);
              ui->lineEdit_3->setText(QString::number(puissance));
                   ui->lineEdit_4->setText(type_voltage);
                     // ui->lineEdit_5->setText(QString::number(etat_initial));
                          ui->lineEdit_6->setText(QString::number(charge));
                                 ui->lineEdit_7->setText(QString::number(dimension_benne));
                           ui->dateEdit_2->setDate(date_recharge);

        }
}

void voit::on_pushButton_4_clicked()
{
    QString matricule=ui->lineEdit->text();
    QString marque=ui->comboBox_3->currentText();
    int puissance=ui->lineEdit_3->text().toInt();
    QString type_voltage=ui->lineEdit_4->text();
   int etat_initial=ui->comboBox_8->currentText().toInt();
    double charge=ui->lineEdit_6->text().toDouble();
    double dimension_benne=ui->lineEdit_7->text().toDouble();
    QDate date_recharge=ui->dateEdit_2->date();
   Voiture v(matricule,marque,puissance,type_voltage,etat_initial,charge,dimension_benne,date_recharge);
   QSqlQuery query;

        bool test=v.modifier(matricule);
       ui->tableView->setModel(v.afficher());
         v.update();
query.prepare("SELECT charge FROM voiture WHERE matricule = :matricule");
 query.bindValue(":matricule",matricule);
if (!query.exec()) {
        qDebug()  <<"Erreur lors de l'exécution de la requête : "  ;
    }
double y = 100;
    double tolerance = 0.00001;
double chargee;
if(query.next())

{ chargee = query.value(0).toDouble();
qDebug() << "Impossible d'exécuter la requête SQL";}

//(ui->comboBox_8->currentText().toInt()==1) && (ui->comboBox_8->currentText().toInt()>=chargee+((chargee*20)/100))
        if(test)
        {

            if(std::fabs(chargee - y) < tolerance)
           { N.notification_modifiervoiture();
                    A.write_to_arduino("0");

}
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            QString nomFile ="His";
                                QFile file("C:/Users/LENOVO/Documents/"+nomFile+".txt");

                                QString finalmsg="fichier ajouter avec succes";
                                 if(!file.exists()){
                                 finalmsg="fichier cree avec succes";
                                 }
                                file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                                QTextStream txt(&file);
                                  QString d_info = QDateTime::currentDateTime().toString();

                                QString message2=d_info+" - Une voiture a été modifiée avec une matricule:  "+ matricule +"\n";
                                txt << message2;

        }
            else
                 {  QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                QObject::tr("connection failed.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        //A.write_to_arduino("0");

}

void voit::on_pushButton_5_clicked()
{
    ui->tableView->setModel(v.afficherTri(ui->comboBox->currentText()));
}


void voit::on_pushButton_6_clicked()
{
    ui->tableView->setModel(v.afficherRech(ui->comboBox->currentText(),ui->lineEdit_8->text()));
}



void voit::on_pushButton_13_clicked()
{
    Voiture v;
   int Hyundai=v.nb_marque("Hyundai");
    int Mercedes=v.nb_marque("Mercedes");
    int BMW=v.nb_marque("BMW");
    int Volswagen=v.nb_marque("Volswagen");

     // Création du graphique
// QPieSeries series = new QPieSeries();
    QPieSeries* series = new QPieSeries();

series->setHoleSize(0.35);
series->append("Mercedes",Mercedes);
QPieSlice* slice=series->append("Hyundai",Hyundai);

slice->setExploded();
slice->setLabelVisible();
series->append("BMW",BMW);
series->append("Volswagen",Volswagen);
QChart* chart = new QChart();
chart->addSeries(series);
chart->setAnimationOptions(QChart::SeriesAnimations);
chart->setTitle("Voitures selon leurs Marques ");
chart->setTheme(QChart::ChartThemeLight);
QChartView* chartview= new QChartView(chart);
chartview->setRenderHint(QPainter::Antialiasing);
chartview->setParent(ui->horizontalFrame);

ui->tabWidget->setCurrentIndex(4);

}




void voit::on_pushButton_7_clicked()
{
    QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->tableView->model()->rowCount();
                   const int columnCount =ui->tableView->model()->columnCount();


                   out <<  "<html>\n"
                           "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg("voiture")
                           <<  "</head>\n"
                           "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                               "<h1>Liste des voitures</h1>"

                               "<table border=1 cellspacing=0 cellpadding=2>\n";

                   // headers
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tableView->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->tableView->isColumnHidden(column)) {
                                      QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                      out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                  }
                              }
                              out << "</tr>\n";
                          }
                          out <<  "</table>\n"
                              "</body>\n"
                              "</html>\n";



                          QTextDocument *document = new QTextDocument();
                                  document->setHtml(strStream);


                                  //QTextDocument document;
                                  //document.setHtml(html);
                                 /* QPrinter printer(QPrinter::PrinterResolution);
                                  printer.setOutputFormat(QPrinter::PdfFormat);
                                  printer.setOutputFileName("mypdffile.pdf");
                                  document->print(&printer);*/


                                  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                   QPrinter printer(QPrinter::PrinterResolution);
                                    printer.setOutputFormat(QPrinter::PdfFormat);
                                   printer.setPaperSize(QPrinter::A4);
                                  printer.setOutputFileName(fileName);

                                   QTextDocument doc;
                                    doc.setHtml(strStream);
                                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                    doc.print(&printer);
                          }


void voit::on_tabWidget_currentChanged(int index)
{
     ui->tableView->setModel(v.afficher());
}

