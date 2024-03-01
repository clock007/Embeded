#ifndef DBCONTEXT_H
#define DBCONTEXT_H
#include <QList>
#include <QString>
#include <QtSql>

#include "httprequesthandler.h"
using namespace stefanfrings;

class Recordlog3
{
public:
    QString Name;
    QString family;
    QString datetime;
};

class DbContext : public HttpRequestHandler
{
public:
    DbContext(QObject* parent=0);
    void service(HttpRequest& request,HttpResponse& response );
private:
    QList<QString> list;
    QList<Recordlog3> ListOfclass;
     QSqlDatabase devicedb;
};

#endif // DBCONTEXT_H
