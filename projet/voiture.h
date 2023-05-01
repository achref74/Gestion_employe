#ifndef VOITURE_H
#define VOITURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class Voiture
{
public:

    Voiture();
    QSqlQueryModel * setmatricule();
    bool ajouter();
    bool supprimer(QString);
    bool modifier(QString);
    QSqlQueryModel * afficher() ;
    void set_matricule(QString m)
    {
        matricule=m;
    }
    Voiture(QString,QString,int,QString,double,double,double,QDate);

  QSqlQueryModel * afficherTri(QString);
   QSqlQueryModel * afficherRech(QString,QString);
    int nb_marque(QString);
    void update() ;
 void deletee ();
    private:
    QString matricule;
    QString marque;
    int puissance;
    QString type_voltage;
    int etat_initial;
    double charge;
    double dimension_benne;
    QDate date_recharge;


};

#endif // VOITURE_H
