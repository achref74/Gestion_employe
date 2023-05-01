#include "voiture.h"
#include "notification.h"



Voiture::Voiture()
{

}
Voiture::Voiture(QString mat, QString mar,int p,QString typev,double etat, double cap, double dim , QDate d ){
    matricule=mat;
    marque=mar;
    puissance=p;
    type_voltage=typev;
    etat_initial=etat;
   charge=cap;
    dimension_benne=dim;
    date_recharge=d;
}


bool Voiture::ajouter(){
    QSqlQuery query;

    query.prepare("insert into VOITURE(matricule,marque,puissance,type_voltage,etat_initial,charge,dimension_benne,date_recharge)""values(:matricule,:marque,:puissance,:type_voltage,:etat_initial,:charge,:dimension_benne,:date_recharge)");

    query.bindValue(":matricule",matricule);
    query.bindValue(":marque",marque);
    query.bindValue(":puissance",puissance);
    query.bindValue(":type_voltage",type_voltage);
    query.bindValue(":etat_initial",etat_initial);
    query.bindValue(":charge",charge);
     query.bindValue(":dimension_benne",dimension_benne);

     query.bindValue(":date_recharge",date_recharge);


    return query.exec();


}

QSqlQueryModel * Voiture::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from Voiture ");
     /*model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("puissance"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("type_voltage"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat_initial"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("charge"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("dimension_benne"));

 model->setHeaderData(8,Qt::Horizontal,QObject::tr("date recharge"));*/
     return  model;

}
bool Voiture::supprimer(QString matricule){
    QSqlQuery query;


    query.prepare("delete from Voiture where matricule= :matricule");
    query.bindValue(":matricule",matricule);

    return query.exec();

}
    bool Voiture::modifier(QString matricule){

        QSqlQuery query;


        query.prepare(" UPDATE voiture SET marque=:marque,puissance=:puissance,type_voltage=:type_voltage,etat_initial=:etat_initial,charge=:charge,dimension_benne=:dimension_benne,date_recharge=:date_recharge where matricule= :matricule");
        query.bindValue(":matricule",matricule);
        query.bindValue(":marque",marque);
        query.bindValue(":puissance",puissance);
        query.bindValue(":type_voltage",type_voltage);
        query.bindValue(":etat_initial",etat_initial);
        query.bindValue(":charge",charge);
         query.bindValue(":dimension_benne",dimension_benne);

         query.bindValue(":date_recharge",date_recharge);

        return    query.exec();
        //notification::checkNotification(matricule, etat_initial, charge);

    }
    QSqlQueryModel * Voiture::afficherTri(QString critere)
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("select *from Voiture order by "+critere);
        return model;
    }
    QSqlQueryModel * Voiture::afficherRech(QString critere,QString rech)
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("select *from Voiture where "+critere+" like '"+rech+"%'");
        return model;
    }


 int Voiture::nb_marque(QString marque)
    {
        QSqlQuery query;

        query.prepare("SELECT COUNT(*) FROM Voiture WHERE marque = :marque");
        query.bindValue(":marque", marque);
        if (query.exec() && query.next())
        {
            return query.value(0).toInt();
        }
        else
        {
            return -1;
        }
    }

/* void Voiture::updateEtatInitial(QString matricule, double charge, int etatInitial) {
     if (charge >= 20 && etatInitial == 0) {
         QSqlQuery query;
         query.prepare("UPDATE voiture SET etat_initial = 1 WHERE matricule = :matricule");
         query.bindValue(":matricule", matricule);
         query.exec();

         notification::sendNotification(matricule);
     }
 }
 void Voiture::updateCharge(QString matricule, double charge) {
     QSqlQuery query;
     query.prepare("UPDATE voiture SET charge = :charge WHERE matricule = :matricule");
     query.bindValue(":charge", charge);
     query.bindValue(":matricule", matricule);
     query.exec();



     updateEtatInitial(matricule, charge, etat_initial);
 }
*/
void Voiture::update()
{QSqlQuery query;
           query.exec( "UPDATE voiture SET etat_initial = 1 WHERE charge = 100");
}

