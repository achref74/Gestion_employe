#include "activ.h"
#include "ui_activ.h"

#include <QIntValidator>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QCloseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include<QSystemTrayIcon>
#include<QPrinter>

activ::activ(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activ)
{
    ui->setupUi(this);
    ui->num->setValidator(new QIntValidator(0,9999999, this));
    ui->pc->setValidator(new QIntValidator(0,20,this));
    ui->pl->setValidator(new QIntValidator(0,20,this));
    ui->pv->setValidator(new QIntValidator(0,20, this));


    ui->tab_activite->setModel(a.afficher());
}

activ::~activ()
{
    delete ui;
}

void activ::on_valider_clicked()
{
    int id=ui->num->text().toInt();
    double frai=ui->fr->text().toDouble();
    QString parking=ui->pr->text();
    int point_c=ui->pc->text().toInt();
    int point_l=ui->pl->text().toInt();
    int point_v=ui->pv->text().toInt();
    QDate datee=ui->dateEdit->date();
   activite a(id,frai,parking,point_c,point_l,point_v,datee);
   bool test=a.ajouter();
    if (test)
    {
        //actualiser pour l'affichage
        QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("Ajout effectué\n" "Click Cancel to exit"), QMessageBox::Cancel);
        ui->tab_activite->setModel(a.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n"
                                                                           "Click Cancel to exit"), QMessageBox::Cancel);

}
void activ::on_delete_2_clicked()
{
    activite a1;
    a1.setnum_service(ui->num_3->text().toInt());

    bool test=a1.supprimer(a1.getnum_service());

    if (test)
    {
        //actualiser pour l'affichage
        QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("suppression avec succes\n" "Click Cancel to exit"), QMessageBox::Cancel);
        ui->tab_activite->setModel(a.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("echec de suppression\n"
                                                                           "Click Cancel to exit"), QMessageBox::Cancel);

}
//modifier
void activ::on_update_clicked()
{
    int num_service=ui->num_2->text().toInt();
    double frais=ui->fr_2->text().toDouble();
    QString parking=ui->pr_2->text();
    int point_c=ui->pc_2->text().toInt();
    int point_l=ui->pl_2->text().toInt();
    int point_v=ui->pv->text().toInt();
    QDate datee=ui->dateEdit_m->date();;
    activite C(num_service,frais,parking,point_c,point_l,point_v,datee);

        bool test=C.update(num_service);

         if(test)
        {
            //actualiser pour l'affichage
            ui->tab_activite->setModel(C.afficher());
                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}

void activ::on_tri_clicked()
{
    ui->tab_activite->setModel(activite().tri_id());

}

void activ::on_recherche_textChanged(const QString &arg1)
{
    ui->tab_activite->setModel(a.rechercher(arg1));

}
void activ::on_pdf_clicked()
{
    {
            QString strStream;
                                        QTextStream out(&strStream);

                                        const int rowCount = ui->tab_activite->model()->rowCount();
                                        const int columnCount = ui->tab_activite->model()->columnCount();

                                        out <<  "<html>\n"
                                            "<head>\n"
                                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                            <<  QString("<title>%1</title>\n").arg("strTitle")
                                            <<  "</head>\n"
                                            "<body bgcolor=#ffffff link=#5000A0>\n"

                                           //     "<align='right'> " << datefich << "</align>"
                                            "<center> <H1>listes des evenement </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                        // headers
                                        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                        for (int column = 0; column < columnCount; column++)
                                            if (!ui->tab_activite->isColumnHidden(column))
                                                out << QString("<th>%1</th>").arg(ui->tab_activite->model()->headerData(column, Qt::Horizontal).toString());
                                        out << "</tr></thead>\n";

                                        // data table
                                        for (int row = 0; row < rowCount; row++) {
                                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                            for (int column = 0; column < columnCount; column++) {
                                                if (!ui->tab_activite->isColumnHidden(column)) {
                                                    QString data = ui->tab_activite->model()->data(ui->tab_activite->model()->index(row, column)).toString().simplified();
                                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                }
                                            }
                                            out << "</tr>\n";
                                        }
                                        out <<  "</table> </center>\n"
                                            "</body>\n"
                                            "</html>\n";

                                  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                   QPrinter printer (QPrinter::PrinterResolution);
                                    printer.setOutputFormat(QPrinter::PdfFormat);
                                   printer.setPaperSize(QPrinter::A4);
                                  printer.setOutputFileName(fileName);

                                   QTextDocument doc;
                                    doc.setHtml(strStream);
                                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                    doc.print(&printer);
        }



}

void activ::on_stat_clicked()
{
    QPieSeries *series = new QPieSeries();


        QStringList list=a.listeadresses("frais");



        for (int i =0; i< list.size();i++)
        {
            series->append(list[i],a.calcul_adresses(list[i],"frais"));

        }
        QPieSlice *slice = series->slices().at(1);
        slice->setLabelVisible();
        slice->setExploded();


        QtCharts::QChart *chart =new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques");
        chart->setAnimationOptions(QChart::AllAnimations);
        QChartView *chartview=new QChartView(chart);
        QGridLayout *mainLayout=new QGridLayout();
        mainLayout->addWidget(chartview,0,0);
        ui->afficherstat->setLayout(mainLayout);
}
void activ::on_calendarWidget_selectionChanged()
{
    QString x=ui->calendarWidget->selectedDate().toString();
       QDate d=ui->calendarWidget->selectedDate();
           //ui->lineEdit_calendar->setText(x);
           ui->dateEdit_7->setDate(d);
           QString dateString = d.toString("yyyy-MM-dd");
           ui->tableView_calendar->setModel(a.afficher_calendar(dateString));
}
void activ::on_pushButton_m_clicked()
{
    int num_service=ui->label_id->text().toInt();
           QSqlQuery query;
           query.prepare("SELECT num_service,frais,parking,point_cafe,point_lavage,point_vidange,datee FROM activite WHERE num_service = :num_service");
           query.bindValue(":num_service",num_service);
           if (!query.exec()) {
               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                           QObject::tr("connection failed.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
           }

           while (query.next()) {

               int num_service =query.value(0).toInt();
                double frais = query.value(1).toDouble();
        QString parking = query.value(2).toString();
 int point_c = query.value(3).toInt();
        int point_l = query.value(4).toInt();
         int point_v = query.value(5).toInt();
    QDate datee =query.value(6).toDate();
               // Afficher les données dans les QLineEdit correspondants

               ui->num_2->setText(QString::number(num_service));
             ui->fr_2->setText(QString::number(frais));
                 ui->pr_2->setText(parking);
                      ui->pc_2->setText(QString::number(point_c));
                      ui->pl_2->setText(QString::number(point_l));
                      ui->pv_2->setText(QString::number(point_v));

                              ui->dateEdit_m->setDate(datee);




           }
}

