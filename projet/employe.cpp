#include "employe.h"

employe::employe()
{

}
employe::employe(int a, QString b, QString c, QString d, QString e,QString f){
     CIN =a;
     NOM=b;
     PRENOM=c;
     ADRESSE=d ;
     MAIL=e ;
     ABSENCE=f;
}

employe::employe(int a, QString b, QString c, QString d, QString e,QString f,QString m,QString r,QString rf){
     CIN =a;
     NOM=b;
     PRENOM=c;
     ADRESSE=d ;
     MAIL=e ;
     ABSENCE=f;
     mdp =m;
     Role=r;
     Rfid=rf;
}

bool employe::ajouter(){
    QSqlQuery query;
    QString res = QString::number(CIN);

    query.prepare("insert into employee(CIN,NOM,PRENOM,ADRESSE,MAIL,ABSENCE,MDP,RFID,ROLE)""values(:CIN,:NOM,:PRENOM,:ADRESSE,:MAIL,:ABSENCE,:MDP,:RFID,:ROLE)");

    query.bindValue(":CIN",CIN);
    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":ADRESSE",ADRESSE);
    query.bindValue(":MAIL",MAIL);
        query.bindValue(":ABSENCE",ABSENCE);
        query.bindValue(":MDP",mdp);
        query.bindValue(":RFID",Rfid);
         query.bindValue(":ROLE",Role);


    return query.exec();


}
QSqlQueryModel * employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select CIN,NOM,PRENOM,ADRESSE,MAIL,ABSENCE,ROLE from employee ");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));
 model->setHeaderData(5,Qt::Horizontal,QObject::tr("ABSENCE"));
  model->setHeaderData(6,Qt::Horizontal,QObject::tr("ROLE"));


     return  model;

}

bool employe::supprimer(int cin){
    QSqlQuery query;
    QString res=QString::number(cin);

    query.prepare("delete from employee where CIN= :CIN");
    query.bindValue(":CIN",res);

    return query.exec();

}

QSqlQueryModel * employe::setid()
 {

     QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select DISTINCT CIN from employee");
     model->setHeaderData(0,Qt::Horizontal,"CIN");

     return model;
 }

bool employe::modifier(){
    QSqlQuery query;
    query.prepare("UPDATE employee SET  NOM=:NOM , PRENOM=:PRENOM , ADRESSE=:ADRESSE , MAIL=:MAIL, ABSENCE=:ABSENCE where CIN=:CIN ");

    query.bindValue(":CIN",CIN);
    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":ADRESSE",ADRESSE);
    query.bindValue(":MAIL",MAIL);
    query.bindValue(":ABSENCE",ABSENCE);
    return    query.exec();
}
QSqlQueryModel * employe::afficher5(QString a)
 {  QSqlQueryModel * model = new QSqlQueryModel();


    model->setQuery("select * from employee order by "+a+" desc");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ABSENCE"));
    return model;
 }
QSqlQueryModel * employe::afficher4(QString a,QString b)
{
  QSqlQueryModel * model = new QSqlQueryModel();

  model->setQuery("select * from employee WHERE "+a+" LIKE '%"+b+"%'");

  model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("ABSENCE"));
   return model;
}

