#include "logincontroller.h"
#include "listdatacontroller.h"
//#include <Qtime>
#include "requestmapper.h"
#include <QtNetwork>
#include<QDebug>

 QByteArray AllowAceess;



logincontroller::logincontroller(QObject* parent):HttpRequestHandler(parent)
{

}
void logincontroller::service(HttpRequest &request, HttpResponse &response) {
    HttpSession session=requestmapper::sessionStore->getSession(request,response,true);
    QByteArray username=request.getParameter("username");
    QByteArray password=request.getParameter("password");
xx=10;
    QByteArray val1=request.getParameter("val1");

    response.write("<html><body>");
    if (session.contains("username")) {
        QByteArray username=session.get("username").toByteArray();
        QTime logintime=session.get("logintime").toTime();
        response.write("You are already logged in.<br>");
        response.write("Your name is: "+username+"<br>");
        response.write("You logged in at: "+logintime.toString("HH:mm:ss").toLatin1()+"<br>");
    }
    else {
    if (username=="az" and password=="az") {
        AllowAceess="true";
      response.write("Yes, correct");
   //   response .redirect("/login");
        session.set("username",username);
        session.set("logintime",QTime::currentTime());
      return;
    }
       else {
        response.write("<form method='POST' action='/login'>");
        if (!username.isEmpty()) {
            response.write("No, that was wrong!<br><br>");
            response.write(username);
            response.write("<br>");
            response.write(val1);
            response.write("<br>");
        }
        response.write("Please log in:<br>");
        response.write("Name     :  <input type='text' name='username'><br>");
        response.write("Password :  <input type='password' name='password'><br>");
        response.write("DeviceNo :  <input type='text' name='val1'><br> ");
        response.write("<input type='submit'>");
        response.write("</form");
    }
}
    response.write("</body></html>",true);
}
