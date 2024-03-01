#ifndef LISTDATACONTROLLER_H
#define LISTDATACONTROLLER_H
#include <QList>
#include <QString>
#include <QtSql>

#include "httprequesthandler.h"

using namespace  stefanfrings;
class Recordlog
{
public:
    QString Name;
    QString family;
    QString datetime;
};
class ListDataController :public HttpRequestHandler
{

public:
    ListDataController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
private:
    QList<QString> list;
    QList<Recordlog> ListOfclass;
     QSqlDatabase devicedb;
};

#endif // LISTDATACONTROLLER_H
