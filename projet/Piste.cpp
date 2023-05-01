#include "Piste.h"

Piste::Piste()
{

}
Piste::Piste(int a, QString b, QString c, QString d){
     CODE =a;
     FINANCE=b;
     BORNE=c;
     DISPONIBILITE=d ;

}
bool Piste::ajouter(){
    QSqlQuery query;
    QString res = QString::number(CODE);

    query.prepare("insert into PISTE(CODE ,FINANCE,BORNE,DISPONIBILITE)""values(:CODE,:FINANCE,:BORNE,:DISPONIBILITE)");

    query.bindValue(":CODE",CODE);
    query.bindValue(":FINANCE",FINANCE);
    query.bindValue(":BORNE",BORNE);
    query.bindValue(":DISPONIBILITE",DISPONIBILITE);



    return query.exec();


}
QSqlQueryModel * Piste::afficherecherch(QString a, QString b)
 {
   QSqlQueryModel * model = new QSqlQueryModel();

   model->setQuery("select * from PISTE WHERE "+a+" LIKE '%"+b+"%'");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("FINANCE"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("BORNE_RECHARGE"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
    return model;
 }
QSqlQueryModel * Piste::affichertri(QString a)
 {  QSqlQueryModel * model = new QSqlQueryModel();


    model->setQuery("select * from PISTE order by "+a+" desc");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("FINANCE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("BORNE_RECHARGE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
    return model;
 }
QSqlQueryModel * Piste::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from PISTE ");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("FINANCE"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("BORNE_RECHARGE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("DISPONIBILITE"));



     return  model;

}

bool Piste::supprimer(int code){
    QSqlQuery query;
    QString res=QString::number(code);

    query.prepare("delete from PISTE where CODE= :CODE");
    query.bindValue(":CODE",res);

    return query.exec();

}

QSqlQueryModel * Piste::setid()
 {

     QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select DISTINCT CODE from PISTE");
     model->setHeaderData(0,Qt::Horizontal,"CODE");

     return model;
 }
QSqlQueryModel * Piste::setnom()
 {

     QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select DISTINCT BORNE from PISTE");
     model->setHeaderData(0,Qt::Horizontal,"BORNE");

     return model;
 }

bool Piste::modifier(){
    QSqlQuery query;
    query.prepare("UPDATE PISTE SET  FINANCE=:FINANCE , BORNE=:BORNE , DISPONIBILITE=:DISPONIBILITE where CODE=:CODE ");
    query.bindValue(":CODE",CODE);
    query.bindValue(":FINANCE",FINANCE);
    query.bindValue(":BORNE",BORNE);
    query.bindValue(":DISPONIBILITE",DISPONIBILITE);

    return    query.exec();
}
