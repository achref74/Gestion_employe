#include "client.h"

client::client()
{

}
client::client(int a, QString b, QString c, QString d, int e,QString f, QString g ,int h   ){
     CINC =a;
     NOMC=b;
     PRENOMC=c;
     ADRESSEC=d ;
     NBP=e ;
     PAIEMENT=f ;
     CODE=g ;
     NUM_SERVICE =h  ;
}
void client::setPAIEMENT(const QString& value)
{
    PAIEMENT = value;
}
bool client::ajouter(){
    QSqlQuery query;
    QString res = QString:: number(CINC);


    query.prepare("insert into CLIENT(CINC,NOMC,PRENOMC,ADRESSEC,NBP,PAIEMENT,CODE,NUM_SERVICE)""values(:CINC,:NOMC,:PRENOMC,:ADRESSEC,:NBP,:PAIEMENT,:CODE,:NUM_S)");

    query.bindValue(":CINC",CINC);
    query.bindValue(":NOMC",NOMC);
    query.bindValue(":PRENOMC",PRENOMC);
    query.bindValue(":ADRESSEC", ADRESSEC);
    query.bindValue(":NBP",NBP);
       query.bindValue(":PAIEMENT", PAIEMENT);

    query.bindValue(":CODE",CODE);
    query.bindValue(":NUM_S",NUM_SERVICE);
    return query.exec();


}
QSqlQueryModel * client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from CLIENT ");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CINC"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMC"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOMC"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSEC"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("NBP"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("PAIEMENT"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("CODE"));
  model->setHeaderData(7,Qt::Horizontal,QObject::tr("NUM_SERVICE"));
     return  model;

}
QSqlQueryModel * client::tri(QString a)
 {  QSqlQueryModel * model = new QSqlQueryModel();


    model->setQuery("select * from CLIENT order by "+a+" desc");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CINC"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMC"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOMC"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSEC"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NBP"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("PAIEMENT"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("CODE"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_SERVICE"));
    return model;
 }
QSqlQueryModel * client::rechercher(QString a,QString b)
{
  QSqlQueryModel * model = new QSqlQueryModel();

  model->setQuery("select * from CLIENT WHERE "+a+" LIKE '%"+b+"%'");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("CINC"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMC"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOMC"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSEC"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("NBP"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("PAIEMENT"));
  model->setHeaderData(6,Qt::Horizontal,QObject::tr("CODE"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUM_SERVICE"));
  return model;
}

bool client::supprimer(int cinc){
    QSqlQuery query;
    QString res=QString::number(cinc);

    query.prepare("delete from CLIENT where CINC= :CINC");
    query.bindValue(":CINC",res);

    return query.exec();

}


QSqlQueryModel * client::setcinc()
 {

     QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select DISTINCT CINC from CLIENT");
     model->setHeaderData(0,Qt::Horizontal,"CINC");

     return model;
 }


bool client::modifier(){
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET  NOMC=:NOMC , PRENOMC=:PRENOMC , ADRESSEC=:ADRESSEC , NBP=:NBP , PAIEMENT=:PAIEMENT , CODE=:CODE,NUM_SERVICE=:NUM_SERVICE where CINC=:CINC ");

    query.bindValue(":CINC",CINC);
    query.bindValue(":NOMC",NOMC);
    query.bindValue(":PRENOMC",PRENOMC);
    query.bindValue(":ADRESSEC",ADRESSEC);
    query.bindValue(":NBP",NBP);
    query.bindValue(":PAIEMENT",PAIEMENT);
    query.bindValue(":CODE",CODE);
    query.bindValue(":NUM_SERVICE",NUM_SERVICE);

    return    query.exec();
}
