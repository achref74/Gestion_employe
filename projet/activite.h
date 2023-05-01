#ifndef AVTIVITE_H
#define AVTIVITE_H
#include <QString>
#include <qstring.h>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include <QDate>
#include <QtWidgets>
#include <QDate>
class activite
{
public:
    activite();
    activite(int,double,QString,int,int,int,QDate);

    bool ajouter();
    QSqlQueryModel * afficher();
      bool supprimer(int d);
      bool update(int );
      QSqlQueryModel * tri_id();
      QSqlQueryModel *rechercher (QString );
      QStringList listeadresses(QString val);
        int calcul_adresses(QString adresse,QString var);
        QSqlQueryModel * afficher_calendar(QString x);





    int getnum_service(){return num_service;}
    double getfrais(){return frais;}
    QString getparking(){return parking;}
    int getpoint_cafe(){return point_cafe;}
    int getpoint_lavage(){return point_lavage;}
    int getpoint_vidange(){return point_vidange;}
    QDate getDtae(){return datee;}

    void setnum_service(int val) {num_service=val;}
    void setfrais(double val){ frais =val;}
    void setparking(QString val){ parking =val;}

    void setpoint_cafe(int val){ point_cafe =val;}
    void setlpoint_lavage(int val){ point_lavage =val;}
    void setpoint_vidange(int val){ point_vidange =val;}
    void setdate(QDate val){ datee =val;}



private:
  int num_service;
  double frais;
  QString parking;
  int point_cafe;
  int point_lavage;
  int point_vidange;
  QDate datee;
};




#endif // AVTIVITE_H
