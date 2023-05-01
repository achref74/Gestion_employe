#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class employe
{public:


    QSqlQueryModel * setid();
    bool ajouter();
    bool supprimer(int );
    bool modifier();
    QSqlQueryModel * afficher() ;
    employe();
    employe(int , QString , QString, QString, QString,QString);
    employe(int , QString , QString, QString, QString,QString,QString,QString,QString);

    QSqlQueryModel * afficher5(QString a);
     QSqlQueryModel * afficher4(QString a,QString b);

private:
    int CIN;
    QString NOM;
    QString PRENOM;
    QString ADRESSE ;
    QString MAIL ;
    QString ABSENCE;
    QString mdp;
    QString Role;
    QString Rfid;
};

#endif // EMPLOYE_H
