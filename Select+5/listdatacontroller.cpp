#include "listdatacontroller.h"
#include <QTime>
#include <QtSql>


ListDataController::ListDataController(QObject* parent):HttpRequestHandler(parent)
{
  //  list.append("a.mahmoodi");
   // list.append("n.rezazadeh");
  //  list.append("o.ebrahimi");
  //  list.append("s.razavi");
     //devicedb=QSqlDatabase::addDatabase("QSQLITE");
    // devicedb.setDatabaseName("/");

      //devicedb.setDatabaseName("/root/IOdb.db");
     // devicedb.setDatabaseName("/home/pi");


      //E:\QT_Project\WebApp\WebApp
//devicedb.open();
      //     if(!devicedb.open())
//        list.append("DataBase close");
//     else
//       list.append("DataBase open");

     QSqlQuery qry;
     QSqlQuery query;
     query.exec("SELECT * FROM RecordLog");
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
                     Recordlog t;
                     t.Name=query.value(0).toString();
                     t.family=query.value(1).toString();
                     //t.datetime=query.value(3).toDateTime();
                       t.datetime=query.value(3).toString();
                     ListOfclass.append(t);
              }
         }
     }
}

void ListDataController::service(HttpRequest &request, HttpResponse &response)
{

//    response.setHeader("Content-Type", "application/json; charset=utf-8;");
//    response.write("{\n");

//    response.write("  time: \"");
//    QString now=QTime::currentTime().toString("HH:mm:ss");
//    response.write(now.toUtf8() );
//    response.write("\", \n");

//    response.write("data: [\n");

//    for(int i=0; i<list.size(); i++) {
//        QString number=QString::number(i);
//        QString name=list.at(i);

//        response.write("{\n");

//        response.write("\"");
//        response.write(number.toLatin1());
//        response.write("\": ");

//        response.write("\"");
//        response.write(name.toLatin1());
//        response.write("\"\n");


//        response.write("}");

//        if(list.size()-i > 1)
//            response.write(", \n");
//    }

//    response.write("]\n");

//    response.write("}\n");

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
        QString name=list.at(i);

        QString number1=QString::number(i);
        QString name1=ListOfclass.at(i).Name ;
        QString family=ListOfclass.at(i).family ;
        QString recordlog=ListOfclass.at(i).datetime;
        response.write("{\n");
        response.write("\"");
        response.write("row\" :");
        response.write("\"");
        response.write(number.toLatin1());
        response.write("\",");
        response.write("\n");
        response.write("\"");
        response.write("Name\":");
        response.write("\"");
        response.write(name1.toLatin1());
        response.write("\",\n");
        response.write("\"Family\":");
        response.write("\"");
        response.write(family.toLatin1());
        response.write("\",\n");
        response.write("\"log\":");
        response.write("\"");
        response.write(recordlog.toLatin1());
        response.write("\"\n");
        response.write("}");

        if((ListOfclass.count())-i > 1)
            response.write(", \n");
    }

    response.write("\n]\n");

    response.write("}\n");


}
