#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include "httprequesthandler.h"

using namespace stefanfrings;

class Errorhandler:HttpRequestHandler
{
public:
    Errorhandler(QObject* parent=0);
    void service(HttpRequest& request,HttpResponse& response);
};

#endif // ERRORHANDLER_H
