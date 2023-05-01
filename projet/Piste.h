#ifndef PISTE_H
#define PISTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Piste
{public:


    QSqlQueryModel * setid();
    QSqlQueryModel * setnom();
    bool ajouter();
    bool supprimer(int );
    bool modifier();
    QSqlQueryModel * afficher() ;
    QSqlQueryModel * afficherecherch(QString a,QString b);
    QSqlQueryModel * affichertri(QString a);
    Piste();
    Piste(int , QString , QString, QString);

private:
    int CODE;
    QString FINANCE;
    QString BORNE;
    QString DISPONIBILITE ;

};

#endif
