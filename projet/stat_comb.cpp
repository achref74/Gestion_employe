#include "stat_comb.h"
#include "ui_stat_comb.h"

stat_comb::stat_comb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_comb)
{
    ui->setupUi(this);
}

stat_comb::~stat_comb()
{
    delete ui;
}


//bar chart
/*void stat_comb::choix_bar()
{
QSqlQuery q1,q2,q3,q4;
qreal tot=0,c1=0,c2=0,c3=0;

//q1.prepare("SELECT * FROM SALLES");
//q1.exec();

q2.prepare("SELECT * FROM SALLES WHERE CAPACITE<100");
q2.exec();

q3.prepare("SELECT * FROM SALLES WHERE CAPACITE>100");
q3.exec();

//q4.prepare("SELECT * FROM CRUD WHERE COMBO='choix3' ");
//q4.exec();

while (q1.next()){tot++;}
while (q2.next()){c1++;}
while (q3.next()){c2++;}
//while (q4.next()){c3++;}

c1=c1/tot;
c2=c2/tot;
//c3=c3/tot;


// Assign names to the set of bars used
        QBarSet *set0 = new QBarSet("<100");
        QBarSet *set1 = new QBarSet(">100 ");
       // QBarSet *set2 = new QBarSet("choix 3");

        // Assign values for each bar
        *set0 << c1;
        *set1 << c2;
 //       *set2 << c3;



        // Add all sets of data to the chart as a whole
        // 1. Bar Chart
        QBarSeries *series = new QBarSeries();

        // 2. Stacked bar chart
        series->append(set0);
        series->append(set1);
    //    series->append(set2);


        // Used to define the bar chart to display, title
        // legend,
        QChart *chart = new QChart();

        // Add the chart
        chart->addSeries(series);


        // Adds categories to the axes
       // QBarCategoryAxis *axis = new QBarCategoryAxis();



        // 1. Bar chart
       // chart->setAxisX(axis, series);

        // Used to change the palette
        QPalette pal = qApp->palette();

        // Change the color around the chart widget and text
        pal.setColor(QPalette::Window, QRgb(0xffffff));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));

        // Apply palette changes to the application
        qApp->setPalette(pal);


// Used to display the chart
chartView = new QChartView(chart,ui->label_stat);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(400,400);

chartView->show();
}
*/
//pie chart
    void stat_comb::choix_pie()
    {
    QSqlQuery q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11;
    qreal tot=0,c1=0,c2=0,c3=0,c4=0,c5=0,c6=0,c7=0,c8=0,c9=0,c10=0;

    q1.prepare("SELECT * FROM CLIENT");
    q1.exec();

    q2.prepare("SELECT * FROM CLIENT WHERE NBP='1'");
    q2.exec();

    q3.prepare("SELECT * FROM CLIENT WHERE NBP='2'");
    q3.exec();

    q4.prepare("SELECT * FROM CLIENT WHERE NBP='3' ");
    q4.exec();
    q5.prepare("SELECT * FROM CLIENT WHERE NBP='4' ");
    q5.exec();
    q6.prepare("SELECT * FROM CLIENT WHERE NBP='5' ");
    q6.exec();
    q7.prepare("SELECT * FROM CLIENT WHERE NBP='6' ");
    q7.exec();
    q8.prepare("SELECT * FROM CLIENT WHERE NBP='7' ");
    q8.exec();
    q9.prepare("SELECT * FROM CLIENT WHERE NBP='8' ");
    q9.exec();
    q10.prepare("SELECT * FROM CLIENT WHERE NBP='9' ");
    q10.exec();
    q11.prepare("SELECT * FROM CLIENT WHERE NBP='10' ");
    q11.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    while (q5.next()){c4++;}
   while (q6.next()){c5++;}
   while (q7.next()){c6++;}
  while (q8.next()){c7++;}
    while (q9.next()){c8++;}
      while (q10.next()){c9++;}
        while (q11.next()){c10++;}
    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;
      c4=c4/tot;
        c5=c5/tot;
          c6=c7/tot;
  c7=c7/tot;
    c8=c8/tot;
      c9=c9/tot;
        c10=c10/tot;

    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("points  fidélité =1",c1);
    series->append("points  fidélité =2",c2);
    series->append("points  fidélité =3",c3);
    series->append("points  fidélité =4",c4);
    series->append("points fidélité =5",c5);
    series->append("points fidélité ",c6);
    series->append("points fidélité =7",c7);
    series->append("points  fidélité =8",c8);
    series->append("points  fidélité =9",c9);
    series->append("points  fidélité =10",c10);



    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(1500,1000);
    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

       // for(auto slice : series->slices())


        //series->append("under 100",c1);
        //series->append("over 100",c2);

    chartView->show();
    }

