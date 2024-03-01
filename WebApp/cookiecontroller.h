#ifndef COOKIECONTROLLER_H
#define COOKIECONTROLLER_H
#include "httprequesthandler.h"
using namespace stefanfrings;

class CookieController:public HttpRequestHandler
{
public:
    CookieController(QObject* parent=0);
    void service(HttpRequest& request,HttpResponse& response );
};

#endif // COOKIECONTROLLER_H
