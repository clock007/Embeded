#include "dbcontext.h"
#include <QtSql>

DbContext::DbContext(QObject* parent)
{
    devicedb=QSqlDatabase::addDatabase("QSQLITE");
    devicedb.setDatabaseName("/root/IOdb.db");
    devicedb.open();
    QSqlQuery qry;
    QSqlQuery query;
    QSqlQuery queryCount;
    query.exec("SELECT * FROM RecordLog ");
    if(qry.exec("select * from RecordLog" ) )
    {
        int count=0;
        while (qry.next() ) {
            count++;
        }
        if (count>0)
        {
            while (query.next()) {

                 QString Name =query.value(0).toString() +"--"+ query.value(1).toString()+"--" +query.value(3).toString();

                    list.append(Name);
                    Recordlog3 t;
                    t.Name=query.value(0).toString();
                    t.family=query.value(1).toString();
                    //t.datetime=query.value(3).toDateTime();
                    t.datetime=query.value(3).toString();
                    ListOfclass.append(t);
             }
        }
    }
}

void DbContext::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
    response.write("<html><body>");

    response.write("The time is ");
    QString now=QTime::currentTime().toString("HH:mm:ss");
    response.write(now.toUtf8());
    response.write("<p>List of names:");
    //QString CountOfRecord =QString::number(ListOfclass.count());
    response.write("<p> Count  Of  Records : ");
    response.write( QByteArray::number( ListOfclass.count()));
    response.write("</P>");
    response.write("<table border='1' cellspacing='1'>");
    for(int i=0; i< ListOfclass.count(); i++) {
        QString number=QString::number(i);
        QString name=ListOfclass.at(i).Name ;
        QString family=ListOfclass.at(i).family ;
        QString recordlog=ListOfclass.at(i).datetime;
        response.write("<tr><td>");
        response.write(number.toLatin1());
        response.write("</td><td>");
        response.write(name.toLatin1());
        response.write("</td><td>");
        response.write(family.toLatin1());
        response.write("</td><td>");
        response.write(recordlog.toLatin1());
        response.write("</td></tr>");
    }
    response.write("</table>");
    response.write("</body></header>",true);
}
