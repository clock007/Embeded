#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H
#include "httprequesthandler.h"
#include "httpsessionstore.h"

using namespace stefanfrings;

class requestmapper : public HttpRequestHandler
{
public:
    requestmapper(QObject* parent=nullptr);
    void service(HttpRequest& request,HttpResponse& response);
   static HttpSessionStore* sessionStore;
};



#endif // REQUESTMAPPER_H
