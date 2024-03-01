#include "myhomecontroler.h"

MyHomeControler::MyHomeControler(QObject* parent):HttpRequestHandler(parent)
{

}
void MyHomeControler::service(HttpRequest &request, HttpResponse &response) {
    response.write("My Db",true);

}
