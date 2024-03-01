#ifndef FILTERRESPONSE_H
#define FILTERRESPONSE_H
#include <QList>
#include <QString>
#include <QtSql>
#include "httprequesthandler.h"
using namespace stefanfrings;

class Recordlog2
{
public:
    QString Name;
    QString family;
    QString datetime;
};

class FilterResponse : HttpRequestHandler
{
public:
    FilterResponse(QObject* parent=0);
    void service(HttpRequest& request,HttpResponse& response);
private:
    QList<QString> list;
    QList<Recordlog2> ListOfclass;
    QSqlDatabase devicedb;
};

#endif // FILTERRESPONSE_H
