#ifndef CLIENTUI_H
#define CLIENTUI_H

#include <QDialog>

#include "client.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <QVector>
//#include  <QPrinter>
//#include <QPrintDialog>
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
//#include <QMediaPlayer>
//#include <QVideoWidget>
#include "stat_comb.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>



#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "arduino.h"

namespace Ui {
class clientui;
}
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class QMediaPlayer;

class clientui : public QDialog
{
    Q_OBJECT

public:
    explicit clientui(QWidget *parent = nullptr);
    ~clientui();
private slots:
    void on_pushButton_clicked();
   // void on_comboBox_activated(int index);
    void on_pushButton_8_clicked();
    void on_pushButton_3_clicked();
 //void on_actionInsert_Image_triggered();

  //  void on_comboBox_2_activated(int index);

    void on_pushButton_2_clicked();

    //void on_comboBox_2_activated(const QString &arg1);

    void on_comboBox123_activated(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    //void on_lineEdit_chercher_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_chercher_textChanged(const QString &arg1);
    void on_supprimer_clicked();
    void on_pushButton_4_clicked();

     void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();
   // void on_pushButton_8_clicked();

    void on_pushButton_QR_clicked();



    void on_comboBox_2_activated(int index);

    void on_comboBox_3_activated(int index);


private:
    Ui::clientui *ui;
    client Etmp;
   stat_comb *s;
   QByteArray imageData;
   Arduino A;

   QCamera *mCamera;
      QCameraViewfinder *mCameraViewfinder;
      QCameraImageCapture *mCameraImageCapture;
      QVBoxLayout *m;
      QMenu *mOptionsmenu;
      QAction *mOuvrir;
      QAction *mCapturer;
      QAction *mSauv;


      QMediaPlayer *mMediaPlayer;
};

#endif // CLIENTUI_H
