#include "connexion.h"

connexion::connexion()
{

}

bool connexion::createconnexion()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;

/*
db.setDatabaseName("oumeyma");
db.setUserName("oumeymaaa");//inserer nom de l'utilisateur
db.setPassword("123456789");//inserer mot de passe de cet utilisateur
*/
db.setDatabaseName("Source_Projet2A");
db.setUserName("khalil");//inserer nom de l'utilisateur
db.setPassword("khalil");//inserer mot de passe de cet utilisateur*/
if (db.open())
test=true;





    return  test;
}

void connexion::closeconnexion(){db.close();}
