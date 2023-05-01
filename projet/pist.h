#ifndef PIST_H
#define PIST_H

#include <QDialog>

#include "Piste.h"
#include <QMainWindow>
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
#include <QMediaPlayer>
#include <QVideoWidget>
#include "stat_comb.h"
#include "arduino.h"

namespace Ui {
class pist;
}

class pist : public QDialog
{
    Q_OBJECT

public:
    explicit pist(QWidget *parent = nullptr);
    ~pist();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonajouter_clicked();

    void on_supprimer_clicked();

   // void on_med_clicked();

   // void on_comboBox_2_activated(const QString &arg1);

    void on_pushButtonMODIFIER_clicked();

   // void on_comboBox_2_activated(int index);

    void on_comboBox_3_activated(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_5_activated(const QString &arg1);

private:
    Ui::pist *ui;
    Piste Etmp;
        stat_comb *s;
        QByteArray data; // variable contenant les données reçues

        Arduino A;
};

#endif // PIST_H
