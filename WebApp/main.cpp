#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QSettings>
#include <QFile>
#include <QDir>
#include<QString>
#include "httplistener.h"
#include "httprequesthandler.h"
#include "myhomecontroler.h"
#include "listdatacontroller.h"
#include "requestmapper.h"

QString searchConfigFile() {
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QFile file;
    file.setFileName(binDir+"/webapp1.ini");
    if (!file.exists()) {
        file.setFileName(binDir+"/etc/webapp1.ini");
        if (!file.exists()) {
            file.setFileName(binDir+"/../etc/webapp1.ini");
            if (!file.exists()) {
                file.setFileName(binDir+"/../"+appName+"/etc/webapp1.ini");
                if (!file.exists()) {
                    file.setFileName(binDir+"/../../"+appName+"/etc/webapp1.ini");
                    if (!file.exists()) {
                        file.setFileName(binDir+"/../../../../../"+appName+"/etc/webapp1.ini");
                        if (!file.exists()) {
                            file.setFileName(QDir::rootPath()+"etc/webapp1.ini");
                        }
                    }
                }
            }
        }
    }
    if (file.exists()) {
        QString configFileName=QDir(file.fileName()).canonicalPath();
        qDebug("using config file %s", qPrintable(configFileName));
        return configFileName;
    }
    else {
        qFatal("config file not found");
    }
}



class test1
{
public:
    QString Name;
    QString family;
    QDateTime datetime;
};

using namespace stefanfrings;
int main(int argc, char *argv[])
{
    test1 t;
    t.Name="amin";

    QCoreApplication a(argc, argv);
    std::cout<<"Start Service...\n";
    qDebug()<<"Press any key to continue...";
  //  std::cin>>x;
   // std::cout<<x*4;
    qDebug()<<"Press any key to continue...";
        QString configFileName="/root/WebApp/WebApp/etc/webapp1.ini";
         qDebug() <<configFileName;

    //QSettings* listenerSettings= new QSettings("../MyFirstWebApp/etc/webapp1.ini",QSettings::IniFormat,&a);
        QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&a);
        sessionSettings->beginGroup("sessions");
        requestmapper::sessionStore=new HttpSessionStore(sessionSettings,&a);


       //HTTP Servevr
      QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, &a);

      qDebug("config file loaded");
      listenerSettings->beginGroup("listener");
       // Start the HTTP server
       // new HttpListener(listenerSettings, new HttpRequestHandler(&a), &a);
       //new HttpListener(listenerSettings, new MyHomeControler (&a), &a);
      new HttpListener(listenerSettings, new requestmapper(&a), &a);

    return a.exec();
}
