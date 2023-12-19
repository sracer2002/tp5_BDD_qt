#include "widget.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");//connexion à la base de donnée
    db.setDatabaseName("jeu");
    db.setUserName("student");
    db.setPassword("crif2024sn");
    if(db.open())
    {
        qDebug()<<"Vous etes maintenant connecte a "<<db.userName();
        QSqlQuery query;
        query.exec("select * FROM `joueur`");//chosir la tableau 'joueur'
        while (query.next())
        {
            QString id = query.value(0).toString();//recuperation des données dans la tableau
            QString prénom = query.value(1).toString();
            QString nom = query.value(2).toString();
            qDebug()<<"-----------------------------------------------";
            qDebug()<<id<<"\t"<<prénom<<"\t"<<nom<<"\t";//affichage de tableau sur la terminale
        }
        qDebug()<<"-----------------------------------------------";
        qDebug()<<"requete ok! : ";
        //db.close();
    }
    else
    {
        qDebug()<<"La connexion a echouee, desole "<<db.lastError().text();
    }

    QSqlTableModel table;//creation de table pour stocker la tableau de BDD
    table.clear();
    table.setTable("joueur");
    table.select();
    QTableView view;//creation d'un table view dans la widget
    QPushButton afficher("Afficher"),note("Note");//creation des boutons "afficher" et "note"
    QHBoxLayout layout;
    //pour faire apparaitre tableview et pushbutton dans la widget
    layout.addWidget(&view);
    layout.addWidget(&afficher);
    layout.addWidget(&note);
    w.setLayout(&layout);

    QObject::connect(&afficher,&QPushButton::clicked,[&](){//si on clique sur la bouton afficher ca affiche la tableau

        view.setModel(&table);
        view.setColumnHidden(0,false);// Affiche la colonne 0 (id)
        view.setColumnHidden(1,false);
        view.setColumnHidden(2,false);
        view.setColumnHidden(3,true);// Cache la colonne 3 (note)
    });

    QObject::connect(&note,&QPushButton::clicked,[&](){//si on clique sur la bouton note ca affiche la colonne de note et on peut modifier les notes en cliquant sur la case


        view.setColumnHidden(0,false);
        view.setColumnHidden(1,false);
        view.setColumnHidden(2,false);
        view.setColumnHidden(3,false);
    });
    w.show();
    return a.exec();
}
