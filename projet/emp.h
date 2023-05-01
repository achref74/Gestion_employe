#ifndef EMP_H
#define EMP_H

#include <QDialog>
#include "employe.h"
#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <QVector>
#include  <QPrinter>
#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPainter>
#include <QDateTime>
#include <QDate>
#include <QSortFilterProxyModel>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QSqlQuery>
#include "arduino.h"

#include "stat_comb.h"

namespace Ui {
class emp;
}

class emp : public QDialog
{
    Q_OBJECT

public:
    explicit emp(QWidget *parent = nullptr,const QString& str = "");
    ~emp();

private slots:
   // void on_pushButton_clicked();

    void on_pushButtonajouter_clicked();

    void on_supprimer_clicked();



    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButtonMODIFIER_clicked();



    //void on_mod1_clicked();

    //void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

   // void on_lineEdit_chercher_textChanged(const QString &arg1);
    void on_pushButton1_clicked();
    void on_pushButton_2_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButtonajouter_2_clicked();

private:
    Ui::emp *ui;
    employe Etmp;
     stat_comb *s;
     Arduino A;

};

#endif // EMP_H
