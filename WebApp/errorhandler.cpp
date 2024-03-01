#include "errorhandler.h"


Errorhandler::Errorhandler(QObject* parent)
{

}

void Errorhandler::service(HttpRequest &request, HttpResponse &response)
{
    response.write("Error");

}
