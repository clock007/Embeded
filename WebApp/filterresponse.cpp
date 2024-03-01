#include "filterresponse.h"
#include <QtSql>

FilterResponse::FilterResponse(QObject* parent)
{

}
void FilterResponse::service(HttpRequest &request, HttpResponse &response)
{

    devicedb=QSqlDatabase::addDatabase("QSQLITE");
    devicedb.setDatabaseName("/root/IOdb.db");
    devicedb.open();
    QSqlQuery filteredQuery;
    QSqlQuery qry;
    QSqlQuery query("SELECT * FROM RecordLog", devicedb);
    QSqlQuery queryCount;

    bool isFirstWhereClause = true;
    QByteArray userid=request.getParameter("user");
    if(userid != nullptr) {
      query.prepare(query.lastQuery() + " where id = :uid");
      isFirstWhereClause = false;
    }

    QByteArray day=request.getParameter("day");
    if(day != nullptr) {
        if(isFirstWhereClause) {
            query.prepare(query.lastQuery() + " where datetime >= date('now',:day)");
        }
        else {
            query.prepare(query.lastQuery() + " and datetime >= date('now',:day)");
        }
      isFirstWhereClause = false;
    }

    if(userid != nullptr)
        query.bindValue(":uid", userid.toInt());
    if(day    != nullptr)
        query.bindValue(":day", "-" + day + " day");

    QString str = query.lastQuery();

    //query.exec();//+"and datetime>= date(''now'',''-100 day'')" );
    if(query.exec())
    {

            while (query.next()) {

                 QString Name =query.value(0).toString() +"--"+ query.value(1).toString()+"--" +query.value(3).toString();
                    list.append(Name);
                    Recordlog2 t;
                    t.Name=query.value(0).toString();
                    t.family=query.value(1).toString();
                    //t.datetime=query.value(3).toDateTime();
                    t.datetime=query.value(3).toString();
                    ListOfclass.append(t);
             }
    }

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
    for(int i=0; i<list.size(); i++) {
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
