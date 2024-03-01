#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H
#include "httprequesthandler.h"
using namespace stefanfrings;

class logincontroller:public HttpRequestHandler
{
public:
    logincontroller(QObject* parent=0);
     void service(HttpRequest& request,HttpResponse& response);

     int xx;
};

#endif // LOGINCONTROLLER_H
