#include "cookiecontroller.h"

CookieController::CookieController(QObject* parent)
{

}
void CookieController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray cookievalue=request.getCookie("MYCookie");
    if(!cookievalue.isEmpty())
    {
        response.write("cookie value : "+cookievalue,true);
    }
    else {
        HttpCookie cookie("MYCookie","123456789",60);
        response.setCookie(cookie);
        response.write("new cookie has been created",true);
    }
}
