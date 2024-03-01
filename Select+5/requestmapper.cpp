#include "requestmapper.h"
//#include "logincontroller.h"
#include "listdatacontroller.h"
#include "httpsessionstore.h"
//#include "errorhandler.h"
//#include "cookiecontroller.h"
//#include "dbcontext.h"
//#include "filterresponse.h"
//#include "getlog.h"

extern QByteArray AllowAceess;

//HttpSessionStore* RequestMapper::sessionStore=0;

HttpSessionStore* requestmapper ::sessionStore=nullptr;

requestmapper::requestmapper(QObject* parent):HttpRequestHandler (parent)
{

}

void requestmapper::service(HttpRequest &request, HttpResponse &response)
{

    QByteArray path=request.getPath();
    QHostAddress ip=request.getPeerAddress();
    QByteArray sessionId=sessionStore->getSessionId(request,response);
   // if(sessionId.isEmpty() && path!="/login" ){
   //     qDebug("RequestMapper: redirect to login page");
//
      //  response.redirect("/login");
        return;
        //logincontroller().service(request,response);
      //  dbc.service(request,response);

  //  }
//
 //   else if(AllowAceess=="true" && path=="/log"){
   //  else if(path=="/log"){

     //   ListDataController().service(request,response);
      //  listdatacontroler.service(request,response);
 //   }
  //  else if(path=="/xml")
   // {
        //HomeControler().service(request,response);
       // homeconrolersudo .service(request,response);
  //  }
   // else if (path=="/login") {
      // logincontroller().service(request, response);
   // }
  //  else if(path=="/error")
    //{
     //   Errorhandler().service(request,response);
   // }
    //else if(path== "/cookie")
   // {
     //   CookieController().service(request,response);
  //  }
  //  else if(path=="/list")
   // {
    //    DbContext().service(request,response);
   // }
   // else if(path=="/filter")
   // {
   //     FilterResponse().service(request,response);
   // }
   // else if(path=="/getlog")
   // {
    //   GetLog().service(request,response);
  //  }
    //else {
   //  response.setStatus(404,"Not Found");

    // response.write("The URL is wrong, no such document.",true);
  //  }

}

