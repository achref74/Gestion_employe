#include "notification.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSystemTrayIcon>
#include<QString>
#include <QDate>
notification::notification()
{

}

void notification::notification_ajoutvoiture()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

notifyIcon->show();
    notifyIcon->showMessage("Gestion des voitures ","nouvelle voiture initialement chargée est ajoutée ",QSystemTrayIcon::Information,15000);
}

void notification::notification_supprimervoiture(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;


    notifyIcon->show();
    notifyIcon->showMessage("Gestion des voiture ","Cette voiture est supprimée",QSystemTrayIcon::Information,15000);
}


void notification::notification_modifiervoiture(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;


    notifyIcon->show();
    notifyIcon->showMessage("Gestion des voiture ","cette voiture est chargée",QSystemTrayIcon::Information,15000);

}


