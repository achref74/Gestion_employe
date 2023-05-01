#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QBuffer>
#include <QDir>
class client
{
public:
    client();
    QSqlQueryModel * setcinc();
    bool ajouter();
     void setPAIEMENT(const QString& value); // nouvelle fonction ajoutée
    bool supprimer(int );
    bool modifier();
    QSqlQueryModel * afficher() ;
     QSqlQueryModel * tri(QString a);
     QSqlQueryModel * rechercher(QString a,QString b) ;
    client(int , QString , QString, QString, int,QString,QString ,int );

private:
    int CINC;
    QString NOMC;
    QString PRENOMC;
    QString ADRESSEC ;
    int NBP ;
    QString  PAIEMENT  ;
    QString CODE  ;
    int NUM_SERVICE ;



};

#endif // CLIENT_H
