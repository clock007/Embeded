#ifndef GETLOG_H
#define GETLOG_H
#include <QList>
#include <QString>
#include <QtSql>


#include "httprequesthandler.h"
using namespace stefanfrings;

class recordlog3
{
public:
    QString id;
    QString fullname;
    QString cardno;
    QString type;
    QString datetime;
};


class GetLog : HttpRequestHandler
{
public:
    GetLog(QObject* parent=0);
    void service(HttpRequest& request,HttpResponse& response);
private:

    QList<recordlog3> ListOfclass;
    QSqlDatabase devicedb;


};

#endif // GETLOG_H
