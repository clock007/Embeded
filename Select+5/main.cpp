#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlQueryModel>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QDebug>
#include "database.h"
#include "listmodel.h"
#include <fingersign.h>
#include <verify.h>
#include <spi.h>
#include <qdateconvertor.h>
#include "systemproperties.h"


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
#include "myhomecontroller.h"
#include "listdatacontroller.h"
#include "requestmapper.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    DataBase database;
    database.connectToDataBase();
    ListModel *model = new ListModel();
    Verify *Ver=new Verify;
    FingerSign *Fingers=new FingerSign;
    SPi *Spi=new SPi;
    QDateConvertor *DateConvert=new QDateConvertor;
    Systemproperties *Sp=new Systemproperties;


    engine.rootContext()->setContextProperty("myModel", model);
    engine.rootContext()->setContextProperty("database", &database);
    engine.rootContext()->setContextProperty("Ver", Ver);
    engine.rootContext()->setContextProperty("Fingers", Fingers);
    engine.rootContext()->setContextProperty("Spi", Spi);
    engine.rootContext()->setContextProperty("Sp", Sp);
    engine.rootContext()->setContextProperty("DateConvert", DateConvert);
    engine.addImageProvider("ID1",Fingers);
    engine.addImageProvider("ID2",Ver);
    engine.addImageProvider("ID3",Sp);




    //qmlRegisted<Verify>("QML.Dotwaves", 1, 0, "Verify");
    //qmlRegisterType<FingerSign>("FingerSign", 1, 0, "FingerSign");
    //qmlRegisterType<SPi>("SPi", 1, 0, "SPi");

//

    //*************** Setup GPIO in Linux **********************************

       //QFile exportFile("/sys/class/gpio/export");
       //exportFile.open(QIODevice::WriteOnly);
       //exportFile.write("5");

       //unexportFile.setFileName("/sys/class/gpio/unexport");
       //unexportFile.open(QIODevice::WriteOnly);

       //QFile directionFile("/sys/class/gpio/gpio5/direction");
       // directionFile.open(QIODevice::WriteOnly);
       // directionFile.write("in");

      //QFile valFile("/sys/class/gpio/gpio5/value");
      //valFile.open(QIODevice::WriteOnly);
      //valFile.write("0");
      //valFile.write("true");

      // QFile edgeFile("/sys/class/gpio/gpio5/edge");
      // edgeFile.open(QIODevice::ReadWrite);
      // edgeFile.write("body");
      //*********************************************************************

       //************************ Start Service *******************************
        std::cout<<"Start Service...\n";          QString configFileName="/home/pi4/webapp1.ini";
       //++++++++++++++++++++++++++++++++++++++++++

      //QSettings* listenerSettings= new QSettings("../MyFirstWebApp/etc/webapp1.ini",QSettings::IniFormat,&a);
          QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
          sessionSettings->beginGroup("sessions");
          requestmapper::sessionStore=new HttpSessionStore(sessionSettings,&app);


          //HTTP Servevr
          QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, &app);

          qDebug("config file loaded");
          listenerSettings->beginGroup("listener");
          // Start the HTTP server
          // new HttpListener(listenerSettings, new HttpRequestHandler(&a), &a);
          //new HttpListener(listenerSettings, new MyHomeControler (&a), &a);
          new HttpListener(listenerSettings, new requestmapper(&app), &app);






    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
