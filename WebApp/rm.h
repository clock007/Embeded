#ifndef RM_H
#define RM_H
#include "httprequesthandler.h"
using namespace stefanfrings;


class RM:public HttpRequestHandler
{

public:
    RM(QObject* parent=0);
};

#endif // RM_H
