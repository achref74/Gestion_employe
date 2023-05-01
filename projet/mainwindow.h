#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include "emp.h"
#include "oublier.h"
#include "gestions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_seconnecter_2_clicked();

    void on_oublie_2_clicked();

  //  void on_creercmpt_clicked();









private:
    Ui::MainWindow *ui;
    emp *e;
    oublier *o;
    Gestions *g;

};
#endif // MAINWINDOW_H
