#include "activite.h"

activite::activite()
{
    num_service=0;
     frais=0;
     parking="";
     point_cafe=0;
     point_lavage=0;
     point_vidange=0;

}

activite::activite(int n,double f,QString p,int pc,int pl,int pv,QDate d)
{
    num_service=n;
     frais=f;
     parking=p;
     point_cafe=pc;
     point_lavage=pl;
     point_vidange=pv;
     datee=d;
}

bool activite:: ajouter()
{
    QSqlQuery query;
    QString num = QString::number(num_service);
    QString pc = QString::number(point_cafe);
    QString pl = QString::number(point_lavage);
    QString pv = QString::number(point_vidange);


          query.prepare("INSERT INTO activite(num_service,frais,parking,point_cafe,point_lavage,point_vidange,datee)"
                        "VALUES (:num_service, :frais, :parking, :point_cafe, :point_lavage, :point_vidange,:datee )");
          query.bindValue(":num_service", num_service);
          query.bindValue(":frais", frais);
          query.bindValue(":parking", parking);
          query.bindValue(":point_cafe", point_cafe);
          query.bindValue(":point_lavage", point_lavage);
          query.bindValue(":point_vidange", point_vidange);
query.bindValue(":datee", datee);
        return  query.exec();


}

QSqlQueryModel * activite ::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select *  from activite");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_service"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("frais"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("parking"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("point_cafe "));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("point_lavage"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("point_vidange"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("date"));
    return model;
}

bool activite::supprimer(int num_service){
    QSqlQuery query;
    QString res=QString::number(num_service);
    query.prepare("Delete from activite where num_service= :id");
    query.bindValue(":id",res);
    return query.exec();
}

bool activite::update(int num_service)
{    QSqlQuery query;


           query.prepare("UPDATE activite set num_service=:num_service,frais= :frais,parking= :parking,point_cafe= :point_cafe,point_lavage= :point_lavage, point_vidange= :point_vidange, datee= :datee  where  num_service= :num_service");
           query.bindValue(":num_service", num_service);
           query.bindValue(":frais", frais);
           query.bindValue(":parking", parking);
           query.bindValue(":point_cafe", point_cafe);
           query.bindValue(":point_lavage", point_lavage);
           query.bindValue(":point_vidange", point_vidange);
           query.bindValue(":datee", datee);




         return  query.exec();




}

QSqlQueryModel * activite ::tri_id(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select *  from activite order by num_service");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_service"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("frais"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("parking"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("point_cafe "));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("point_lavage"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("point_vidange"));



    return model;
}

QSqlQueryModel *activite::rechercher(QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM activite WHERE num_service LIKE'"+rech+"%'");
    return model;


}

QStringList activite::listeadresses(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from activite");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int activite::calcul_adresses(QString frais,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from activite  WHERE "+val+"=:frais");
     query.bindValue(":frais", frais );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}
QSqlQueryModel * activite::afficher_calendar(QString x)

{QSqlQueryModel * model= new QSqlQueryModel();



model->setQuery("SELECT * FROM activite WHERE TO_CHAR(datee, 'YYYY-MM-DD') = '" +x+ "' ");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_SERVICE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("FRAIS"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PARKING"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("POINT_CAFE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("POINT_LAVAGE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("POINT_VIDANGE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE"));



    return model;

}
