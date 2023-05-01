#ifndef ACTIV_H
#define ACTIV_H

#include <QDialog>

#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
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
#include "activite.h"


namespace Ui {
class activ;
}

class activ : public QDialog
{
    Q_OBJECT

public:
    explicit activ(QWidget *parent = nullptr);
    ~activ();
private slots:


    void on_valider_clicked();

    void on_delete_2_clicked();

    void on_update_clicked();


    void on_tri_clicked();

    void on_recherche_textChanged(const QString &arg1);


    void on_pdf_clicked();

    void on_stat_clicked();

    void on_calendarWidget_selectionChanged();

    void on_pushButton_m_clicked();

private:
    Ui::activ *ui;
    activite a;
       QByteArray data;
};

#endif // ACTIV_H
