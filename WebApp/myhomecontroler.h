#ifndef MYHOMECONTROLER_H
#define MYHOMECONTROLER_H
#include<httprequesthandler.h>

using namespace stefanfrings;

class MyHomeControler:public HttpRequestHandler
{

public:
    MyHomeControler(QObject* parent=0);
     //void service(HttpRequest& request, HttpResponse& response);
    void service(HttpRequest& request,HttpResponse& response);
};

#endif // MYHOMECONTROLER_H
