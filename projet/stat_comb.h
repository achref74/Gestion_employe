#ifndef STAT_COMB_H
#define STAT_COMB_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class stat_comb;
}

class stat_comb : public QDialog
{
    Q_OBJECT

public:
    explicit stat_comb(QWidget *parent = nullptr);
    ~stat_comb();

    QChartView *chartView ;
    void choix_bar1();
    void choix_pie();

private:
    Ui::stat_comb *ui;
};

#endif // STAT_COMB_H
