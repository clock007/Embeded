#include "getlog.h"
#include <QtSql>

GetLog::GetLog(QObject* parent)
{

}
void GetLog::service(HttpRequest &request, HttpResponse &response)
{
    devicedb=QSqlDatabase::addDatabase("QSQLITE");
    devicedb.setDatabaseName("/root/IOdb.db");
    devicedb.open();
    QSqlQuery qry;
    QSqlQuery query("SELECT * FROM RecordLog",devicedb );
    bool isFirstWhereClause=true;
    QByteArray userid=request.getParameter("user");
    if(userid != nullptr){
        query.prepare(query.lastQuery()+ " where id = :uid");
        isFirstWhereClause=false;
    }
    QByteArray day=request.getParameter("day");
    if(day != nullptr){
        if(isFirstWhereClause){
            query.prepare(query.lastQuery()+ " where datetime >= date('now',:day)");
        }
        else{
            query.prepare(query.lastQuery() + " and datetime >= date('now',:day)");
        }
        isFirstWhereClause = false;
    }

    if(userid !=nullptr)
    query.bindValue(":uid",userid.toInt());
    if(day !=nullptr)
        query.bindValue(":day", "-" + day + " day");
    if(query.exec())
    {

            while (query.next()) {

                 QString Name =query.value(0).toString() +"--"+ query.value(1).toString()+"--" +query.value(3).toString();

                    recordlog3 t;
                    t.id=query.value(0).toString();
                    t.fullname=query.value(1).toString();
                    t.cardno=query.value(2).toString();
                    t.datetime=query.value(3).toString();
                    t.type=query.value(4).toString();
                    ListOfclass.append(t);
             }
    }
    response.setHeader("Content-Type", "application/json; charset=utf-8;");
    response.write("{\n");

    response.write("\"time\": \"");
   QString now=QTime::currentTime().toString("HH:mm:ss");
    response.write(now.toUtf8() );
    response.write("\", \n");
    response.write("\"Count\" : \"");
    response.write(QByteArray::number(ListOfclass.count()));
    response.write("\" , \n");
    response.write("\"data\": \n[\n");

    for(int i=0; i<ListOfclass.count(); i++) {
        QString number=QString::number(i);


        QString number1=QString::number(i);
        QString id=ListOfclass.at(i).id ;
        QString fullname=ListOfclass.at(i).fullname ;
        QString cardno=ListOfclass.at(i).cardno;
        QString Type=ListOfclass.at(i).type;
        //QString =ListOfclass.at(i).family ;
        QString datetime=ListOfclass.at(i).datetime;

        response.write("{\n");
        response.write("\"");
        response.write("row\" :");
        response.write("\"");
        response.write(number.toLatin1());
        response.write("\",");
        response.write("\n");
        response.write("\"");
        response.write("PersonNo\":");
        response.write("\"");
        response.write(id.toLatin1());
        response.write("\",\n");
        response.write("\"Family\":");
        response.write("\"");
        response.write(fullname.toLatin1());
        response.write("\",\n");
        response.write("\"log\":");
        response.write("\"");
        response.write(datetime.toLatin1());

        response.write("\",\n");
        response.write("\"Type\":");
        response.write("\"");
        response.write(Type.toLatin1());
        response.write("\"");
        response.write("}");

        if((ListOfclass.count())-i > 1)
            response.write(", \n");
    }

    response.write("\n]\n");

    response.write("}\n");


}
