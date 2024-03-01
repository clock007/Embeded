#include "verify.h"
#include <QtDebug>
#include <QtSerialPort>
#include <QTemporaryFile>
#include <QMutex>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QtGui>
#include <QSqlQuery>
#include <QFile>
#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include <unistd.h> // for usleep
#include <wiringPi.h>
#include <QtMultimedia>
#include <QtMultimedia/QMediaPlayer>
#include <QDateTime>
#include <QTime>
#include <cstdlib>
#include <QImage>
#include <QPixmap>
#include <raspicam/raspicam.h>
//#include <raspicam/raspicam_cv.h>
//---------------------------opencv laibraries---------------------------------
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/dnn/dnn.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
//------------------------- c++ in/out Streams---------------------------------
#include <iostream>
#include <fstream>
#include <unistd.h> // for usleep
using namespace std;
using namespace cv;
using namespace cv::face;
using namespace cv::dnn;
using namespace std;


//------------------------------------

#define INTERUPT 5
#define ONSOUND 8
#define ONRFIDFINGER 17
#define ONPRINTER 12
#define BACKLIGH 18
#define DISPLAYVOLTAGE 23
#define SELECT 24
#define FAN 26

int Type;
extern QString MyDate;
QString ip;
QImage image4;

int NoElseShow=0;
int PowerSaverCounter;
int PowerSaverCounter_Lim;
int OddEven=0;
int s;
void myinterupt()
{s++; }

//const std::string caffeConfigFile = "/home/pi/models/deploy.prototxt";
//const std::string caffeWeightFile ="/home/pi/models/res10_300x300_ssd_iter_140000_fp16.caffemodel";
//const std::string tensorflowConfigFile = "/home/pi/pi/models/opencv_face_detector.pbtxt";
//const std::string tensorflowWeightFile = "/home/pi/models/opencv_face_detector_uint8.pb";


Verify::Verify(QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{   Initialize_ServerSetting();

    wiringPiSetupGpio();
    pinMode(10,INPUT);
    digitalWrite(10,HIGH);
    pinMode(ONSOUND,OUTPUT);
    digitalWrite(ONSOUND,HIGH);

    pinMode(ONRFIDFINGER,OUTPUT);
    digitalWrite(ONRFIDFINGER,HIGH);
    pinMode(ONPRINTER,OUTPUT);
    digitalWrite(ONPRINTER,HIGH);
    ERR_UP_BUSY=false; emit ChangedDownBusy();

    //--------------------------------------------   Set Media Files ------------------------------------------------------------------------------
    plNoPerson=new QMediaPlayer;  plNoInternet10=new QMediaPlayer;  plNoMealBegined8=new QMediaPlayer;
    plNoMealDefined7=new QMediaPlayer;   plNoMachineinRest5=new QMediaPlayer;   plNoReservedFood4=new QMediaPlayer;
    plNoRestaurantMember6=new QMediaPlayer;   plFishTakenBefor3=new QMediaPlayer;  plNoConnectToDataBase9=new QMediaPlayer;  plOk=new QMediaPlayer;
    plNoPerson->setMedia(QUrl::fromLocalFile("/home/pi/S1/fail.wav"));
    plOk->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled1.mp3"));
    plFishTakenBefor3->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled1.mp3"));
    plNoInternet10->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled10.mp3"));
    plNoMealBegined8->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled8.mp3"));
    plNoMealDefined7->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled7.mp3"));
    plNoReservedFood4->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled4.mp3"));
    plNoMachineinRest5->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled5.mp3"));
    plNoRestaurantMember6->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled6.mp3"));
    plNoConnectToDataBase9->setMedia(QUrl::fromLocalFile("/home/pi/S1/Untitled9.mp3"));
    //---------------------------------------------------------------------------------------------------------------------------------------------
    Init_Setting();

    //-------------------------------  Serial Port Setting ----------------
    Serial11=new QSerialPort(this);
    Serial12=new QSerialPort(this);
    Serial13=new QSerialPort(this);
    //*************** Setup GPIO in Linux **********************************
    QObject::connect(Serial12,SIGNAL(readyRead()),this,SLOT(readdata12()));

    //*************** Setup GPIO in Linux **********************************
    Controller=1;       Value=1;       emit VALUEChanged();
   // QFile exportFile("/sys/class/gpio/export");
   // exportFile.open(QIODevice::WriteOnly);
   // exportFile.write("5");

   // QFile directionFile("/sys/class/gpio/gpio5/direction");
   // directionFile.open(QIODevice::WriteOnly);
  //  directionFile.write("in");

  //  QFile valFile("/sys/class/gpio/gpio5/value");
  //  valFile.open(QIODevice::WriteOnly);
  //  valFile.write("0");
  // valFile.write("true");

  //  QFile edgeFile("/sys/class/gpio/gpio5/edge");
  //  edgeFile.open(QIODevice::ReadWrite);
  //  edgeFile.write("body");

    //system ("/usr/local/bin/gpio edge 5 rising") ;
    //******************** Setup Serial Ports ************************************************************
    //******************** Setup Serial Port Finger ******************************************************
    Serial11->setPortName("/dev/ttyUSB0"); //COM-port
    Serial11->open(QIODevice::ReadWrite);
    Serial11->setBaudRate(115200);
    Serial11->setStopBits(QSerialPort::OneStop);
    Serial11->setParity(QSerialPort::NoParity);
    Serial11->setDataBits(QSerialPort::Data8);
    //******************** Setup Serial Port RFID *********************************************************
    Serial12->setPortName("/dev/ttyUSB1"); //COM-port
    Serial12->open(QIODevice::ReadWrite);
    Serial12->setBaudRate(9600);
    //******************** Test Connection to Serial Port *************************************************

    TestConnection[0]=0x55; TestConnection[1]=0xaa; TestConnection[2]=0x00; TestConnection[3]=0x00; TestConnection[4]=0x01; TestConnection[5]=0x00;  TestConnection[6]=0x00; TestConnection[7]=0x00;
    TestConnection[8]=0x00; TestConnection[9]=0x00; TestConnection[10]=0x00; TestConnection[11]=0x00;    TestConnection[12]=0x00; TestConnection[13]=0x00; TestConnection[14]=0x00; TestConnection[15]=0x00; TestConnection[16]=0x00; TestConnection[17]=0x00;
    TestConnection[18]=0x00; TestConnection[19]=0x00; TestConnection[20]=0x00; TestConnection[21]=0x00; TestConnection[22]=0x00; TestConnection[23]=0x00; TestConnection[24]=0x00; TestConnection[25]=0x01;
    Serial11->write(TestConnection,26);  Serial11->waitForBytesWritten(500); Serial11->waitForReadyRead(1000); Re_TestConnection=Serial11->readAll();   qDebug()<<"Test Connection"<<Re_TestConnection;
   if(Re_TestConnection[0]!=0xaa && Re_TestConnection[1]!=0x55) {qDebug()<<"ERRRRROR"<<Re_TestConnection; Serial11->close(); Serial12->close(); delay(100);
    Serial11->setPortName("/dev/ttyUSB1");   Serial11->setBaudRate(115200); Serial11->open(QIODevice::ReadWrite);
    Serial12->setPortName("/dev/ttyUSB0");   Serial12->setBaudRate(9600);  Serial12->open(QIODevice::ReadWrite);       }

    //******************** Setup Serial Port Printer *********************************************************
    Serial13->setPortName("/dev/ttyS0"); //COM-port that arduino is connected to
    Serial13->setBaudRate(9600);
    if(Serial13->open(QIODevice::ReadWrite))
    {  qDebug()<<" Printer Serial Opened";}
    if ( Serial13->isReadable())
    {qDebug()<<"Printer is Readable";}
    if ( Serial13->isWritable())
    {qDebug()<<"Printer is Writable";}
    // Serial13->write("a");
    Serial13->write("\x1b\x40");   Serial13->waitForBytesWritten(500);
    //-------   Load Table ------------------------------
    Serial13->write("\x1b\x74\x14");
    //*****************************************  Interrupt Setting ****************************
    setenv("WIRINGPI_GPIOMEM","1",1);
    wiringPiSetupGpio();
    wiringPiISR(5,INT_EDGE_RISING, &myinterupt);
    pinMode(5,INPUT);
    pinMode(5,PUD_OFF);
    //pinMode(6,INPUT);
    //pullUpDnControl(6, PUD_UP);
    // digitalWrite(5,LOW);
 //   watcher.addPath("/sys/class/gpio/gpio5/value");
   // QObject::connect(&watcher, SIGNAL (fileChanged(QString)), \
                //     this, SLOT(readdata11()));
    //****************************** Check Serial ***********************************************
    if(Serial11->isOpen())
    {qDebug()<<"Serial Finger is Open";}
    if(Serial12->isOpen())
    {qDebug()<<"Serial RFID is Open";}
    if(Serial13->isOpen())
    {qDebug()<<"Serial Printer is Open";}
    //************************   Get Protocol Address  ******************************************
    Get_Current_IP();

}//

Verify::~Verify() {}
QImage Verify::requestImage(const QString& id, QSize* size, const QSize& requestedsize)
{ result=image4;   qDebug()<<result.size();
//qimg =QImage((const unsigned char*) camFrames.data, camFrames.cols, camFrames.rows, QImage::Format_Grayscale8);
if(size) {*size = result.size();   }
  return result;}
void Verify::readdata12()
{  PowerSaverCounter=0;
    ERR_ID=0;     ERR_NAME="یافت نشد";   ERR_SECURITY = "";  ERR_CARDNO =0; ERR_FoodName1=""; ERR_FoodName2=""; ERR_FoodName3="";
    ERR_FoodCount1=""; ERR_FoodCount2=""; ERR_FoodCount3=""; ERR_EFood="";
    ERR_STREAM2=ERR_STREAM2+1;
    if(ERR_STREAM2 >10000) ERR_STREAM2=0;
    //------------------------------------------------------------------
    VERR_READRFID=Serial12->readAll();
    qDebug()<<VERR_READRFID;
    VERR_READRFID.remove(QRegExp("[\n\t\r\a\d]"));
    qDebug()<<"RFIDDDD"<<VERR_READRFID;
    qDebug()<<VERR_READRFID;
    QSqlQuery query;          query.prepare("SELECT * From Person WHERE cardno= :cardno ;");
    char fl,fh;
    int fingerNo;

    query.bindValue(":cardno", VERR_READRFID);

    if(query.exec())
    {     while (query.next()) {
            ERR_ID=query.value(0).toInt();
            fl=query.value(4).toInt();
            fh=query.value(5).toInt();    }}
    if(ERR_ID!=0) {Type=0; FingerStep4(fl,fh);}
    if(ERR_ID==0)
    {   plNoPerson->play();
        emit VChangedRFID();   emit NAMEChanged();             emit IDChanged();             emit CARDNOChanged(); emit EFoodChanged();
        emit FoodName1Changed(); emit FoodName2Changed(); emit FoodName3Changed(); emit FoodCount1Changed(); emit FoodCount2Changed(); emit FoodCount3Changed();
        emit Stream2Changed();
    }

}

void Verify::readdata11()
{

    counter=-10;  //ERR_STREAM1=ERR_STREAM1+1; if(ERR_STREAM1 >10000) ERR_STREAM1=0; emit Stream1Changed();
    Value=Value+1;
    if (Value>1000) Value=0;
    if (Controller==1) {
       Controller=0;   FingerStep1();  qDebug() << ("-controller=1");} }



void Verify::FingerStep1() {
   Get[0]=0x55;     Get[1]=0xaa;     Get[2]=0x00;     Get[3]=0x00;     Get[4]=0x20;
   int i=0;
   for (i=5;i<=23;i++)
       Get[i]=0x00;

   Get[24]=0x1F;     Get[25]=0x01;
   qDebug() << Get.toHex();
   Serial11->write(Get,26);     Serial11->waitForBytesWritten(100);     Serial11->waitForReadyRead(1000);     Re_Get=Serial11->readAll();
   qDebug()<<Re_Get.toHex();
   if(Re_Get[8]==0x28){ //ERR_CARDNO=0; ERR_SECURITY=""; ERR_ID=0; ERR_NAME="Nothing On Sensor";
        //digitalWrite(BACKLIGH,LOW);    digitalWrite(DISPLAYVOLTAGE,HIGH);
        //qDebug()<<"--- Display Turned On ---";  emit VALUEChanged();   qDebug()<<Re_Get.toHex();
   }
   if(Re_Get[24]==0x22){ digitalWrite(BACKLIGH,LOW);    digitalWrite(DISPLAYVOLTAGE,HIGH);
      PowerSaverCounter=0; qDebug()<<"--- Display Turned On ---";
  FingerStep2();qDebug()<<"ReadFinger";}
}

void Verify::FingerStep2()
{   Generation[0]=0x55;    Generation[1]=0xaa;    Generation[2]=0x00;    Generation[3]=0x00;    Generation[4]=0x60;
    Generation[5]=0x00;    Generation[6]=0x02;    Generation[7]=0x00;    Generation[8]=0x00;
    int i;
    for (i=9;i<=23;i++)
        Generation[i]=0x00;
    Generation[24]=0x61;    Generation[25]=0x01;    Serial11->write(Generation,26);
    Serial11->waitForBytesWritten(100);    Serial11->waitForReadyRead(1000);
    Re_Generation=Serial11->readAll();    qDebug()<<Re_Generation.toHex();
    if(Re_Generation[24]==0x62){ FingerStep3(); qDebug()<<"2";}}

void Verify::FingerStep3()
{   Search[0]=0x55;    Search[1]=0xaa;    Search[2]=0x00;    Search[3]=0x00;    Search[4]=0x63;
    Search[5]=0x00;    Search[6]=0x06;    Search[7]=0x00;    Search[8]=0x00;    Search[9]=0x00;
    Search[10]=0x01;   Search[11]=0x00;   Search[12]=0xd0;    Search[13]=0x07;
    int i;
    for (i=14;i<=23;i++)
        Search[i]=0x00;

    Search[24]=CheckSum(Search)& 0xff;
    Search[25]=CheckSum(Search) >> 8;


    Serial11->write(Search,26);
    //Serial11->flush();
    Serial11->waitForBytesWritten(100);
    Serial11->waitForReadyRead(1000);
    Re_Search=Serial11->readAll();
    qDebug()<<Search.toHex();
    qDebug()<<Re_Search.toHex();
    char fingerl,fingerh;

    if(Re_Search[6]==0x05){ fingerl=Re_Search[10];  fingerh=Re_Search[11]; Type=1; FingerStep4(fingerl,fingerh);  }
    else if(Re_Search[6]==0x02){VERR_READRFID="ERROR"; plNoPerson->play(); ERR_STREAM2=ERR_STREAM2+1;
        ERR_NAME = "یافت نشد";       ERR_ID=0;     ERR_CARDNO =0;   ERR_SECURITY=""; ERR_FoodName1=""; ERR_FoodName2=""; ERR_FoodName3=""; ERR_EFood="";
        ERR_FoodCount1=""; ERR_FoodCount2=""; ERR_FoodCount3=""; ERR_EFood="";   ERR_SECURITY = "";if(ERR_STREAM2 >1000) ERR_STREAM2=0;
        emit NAMEChanged(); emit CARDNOChanged(); emit SECURITYChanged(); emit IDChanged();   emit EFoodChanged(); emit FoodName1Changed(); emit FoodName2Changed(); emit FoodName3Changed(); emit FoodCount1Changed(); emit FoodName2Changed(); emit FoodCount3Changed(); emit Stream2Changed();}

}

void Verify::FingerStep4(char fingerl,char fingerh)
{
    int matched=0; int  NoElseShow=0; QDateTime Date;    QProcess process1; QSqlQuery query;
    //--------------------get  Current Date
    // QString ERR_date=Date.currentDateTime().toString();

    QString Currentdate=QDate::currentDate().toString();
    QString CurrentTime=QTime::currentTime().toString();
    QString CurrentDate=Currentdate+" "+CurrentTime;
    QString SystemAnswer;
    //-------------------   Set Default ---------------------------------
    ERR_ID=0; ERR_NAME="یافت نشد"; ERR_CARDNO=0; ERR_SECURITY=""; ERR_FoodName1=""; ERR_FoodName2=""; ERR_FoodName3="";
    ERR_FoodCount1=""; ERR_FoodCount2=""; ERR_FoodCount3=""; ERR_EFood="";
    QString returned;
    // plOk->play();
    qDebug()<<"Answer  is :" <<finger;

    query.prepare("SELECT * From Person WHERE FingerIdL=:fl and FingerIdH=:fh ;");
    query.bindValue(":fl", fingerl);
    query.bindValue(":fh", fingerh);
    if(query.exec())
    {while(query.next()){ states=query.value(9).toInt();
           qDebug()<<"State is"<<states;
           ERR_ID = query.value(0).toInt();
           ERR_NAME = query.value(1).toString();
           ERR_CARDNO=query.value(2).toInt();
           ERR_SECURITY = query.value(3).toString();
           QByteArray outByteArray = query.value(7).toByteArray();
           image4.loadFromData( outByteArray );
           if(states==0){matched=1; ERR_STATE=" ";}


        if(states==1){matched=0;
            ERR_STATE="کاربر غیر مجاز";   }}}
            qDebug()<<"ERROR STATE  IS: "<<ERR_STATE;
            qDebug()<<ERR_NAME;
    emit NAMEChanged(); emit IDChanged(); emit CARDNOChanged(); emit SECURITYChanged(); emit StateChanged();
    ERR_STREAM2=ERR_STREAM2+1; if(ERR_STREAM2 >1000) ERR_STREAM2=0;      emit Stream2Changed();
    //-------------------------------------------------------------------------------------------------------




        //-----------------  Insert into DataBase Printed Factor ---------------------
        if(ERR_NAME!="یافت نشد" && states==0){
            query.prepare("INSERT INTO RecordLog (id, Personid, CardNo, DateTime, Type) "
                          "VALUES (:id, :FullName, :CardNo, :DateTime, :Type)");
            query.bindValue(":id", ERR_ID);             query.bindValue(":FullName", ERR_NAME);
            query.bindValue(":CardNo", QString::number(ERR_CARDNO));             query.bindValue(":DateTime", CurrentDate); query.bindValue(":Type", Type);
            //qDebug()<<image5.size();
            if (query.exec()){ qDebug()<<"ok Saved";} }
    //---------------------------------------------------------------------------------

    //---------------------------  Begin Processing All   -----------------------------------------

     //-------------------------------------------------------------------------------------

    //------------------------------  check network  ------------------------------------------

    //if(&&ERR_EFood!="این ماشین در بانک اطلاعاتی ثبت نشده است"&& ERR_EFood== "فیش تحویل داده شده است" && ERR_EFood== "غذا رزرو نشده است"  &&  &&   && ){

}

void Verify::UpFinger()
{ qDebug()<<"-------------------  On Downloading  ---------------------------------";
    int j,k,fl,fh,id2,id3,id4; QString id;
    int length1,length2,length;
    QByteArray FingerData,Command_Packet,Re_Command_Packet;
    QByteArray GEmptyIDs,Re_GEmptyIDs;    QByteArray SStore,Re_SStore;
    QSqlQuery query;
    QString id5,name,cardno,accesstype;
    QFile TemplateFile,CSVFile;  QString buffer;
    QStringList SubCsvToString1,SubCsvToString2;
    QRegExp rx("+++");
    QByteArray byte1,byte2,byte3;
    //------------------------------ Load Data File --------------------------------------------
    CSVFile.setFileName("/media/pi/NEW/Data.csv");

    if(!CSVFile.exists()){
        qDebug()<<"+++++ Unavailabale +++++";  ERR_FAILED_USB="عدم دسترسی به حافظه"; emit ChangedUSB(); ERR_FAILED_USB=" "; emit ChangedUSB();
    }

    if(CSVFile.exists()){
        if(!CSVFile.open(QIODevice::ReadOnly)) return;
        else buffer=CSVFile.readAll(); }


    //---------------------  Divide Main String To Records ---------------------------------------
    SubCsvToString1=buffer.split("+++");

    int i=0;
    while (SubCsvToString1[i]!=""){

        //---------------------- Divide Record(ith) To SubParts ----------------------------------------
        SubCsvToString2=SubCsvToString1[i].split(",");
        qDebug()<<"All Data Size:   "<<SubCsvToString1.length();
        qDebug()<<SubCsvToString2[0];
        qDebug()<<SubCsvToString2[1];
        qDebug()<<SubCsvToString2[2];
        i=i+1;
        fl=SubCsvToString2[4].toInt(); fh=SubCsvToString2[5].toInt();
        id2=fl; id3=fh << 8;  id4=id2+id3;   id5=QString::number(id4);

        //------------------------------------- Moving Templates To FingerPrint id file -------------------------------
        qDebug() << ("Moving Templates To FingerPrint id file:   ")<<id5;
        TemplateFile.setFileName("/media/pi/NEW/"+id5+".dat");
        if(!TemplateFile.open(QIODevice::ReadOnly)) {  return; }
        FingerData=TemplateFile.readAll();
        TemplateFile.close();
        //------------------------------------------ Request For Move of Template To module----------------------------
        DFinger.clear(); DFinger[24]=0; DFinger[25]=0;
        DFinger[0]=0x55;    DFinger[1]=0xaa;    DFinger[2]=0x00;    DFinger[3]=0x00;    DFinger[4]=0x43;
        DFinger[5]=0x00;    DFinger[6]=0x02;    DFinger[7]=0x00;    DFinger[8]= 0xf4;   DFinger[9]=0x01;
        for (j=10;j<=23;j++)
            DFinger[j]=0x00;
        DFinger[24]=CheckSum(DFinger)& 0xff;      DFinger[25]=CheckSum(DFinger) >> 8;
        Serial11->write(DFinger,26);
        //Serial11->flush();
        Serial11->waitForBytesWritten(2000);  Serial11->waitForReadyRead(5000);     Re_DFinger=Serial11->readAll();
        qDebug()<<DFinger.toHex();  qDebug()<<Re_DFinger.toHex();
        delay(200);

        //--------------------------------------------------- Make Ready Data CommandPacket------------------------------
        Command_Packet[0]=0x5a;Command_Packet[1]=0xa5;  Command_Packet[2]=0x00;  Command_Packet[3]=0x00; Command_Packet[4]=0x43; Command_Packet[5]=0x00;
        Command_Packet[6]=0xf4; Command_Packet[7]=0x01; Command_Packet[8]=0x00; Command_Packet[9]=0x00;
        for(j=0;j<=497;j++)
            Command_Packet[j+10]=FingerData[j];
        Command_Packet[508]=CheckSum2(Command_Packet)& 0xff;     Command_Packet[509]=CheckSum2(Command_Packet) >> 8;
        qDebug() << ("Moving Templates To FingerPrint File:   ")<<id5;
        //-----------------------------  Write Command Data Packet To File  --------------------------------------------
        TemplateFile.setFileName("/home/pi/communicate.txt");
        if(!TemplateFile.open(QIODevice::WriteOnly)) return;      TemplateFile.write(Command_Packet);      TemplateFile.close();      delay(200);
        //------------------------------------- Write File To Serial Port ----------------------------------------------
        QFile data;       data.setFileName("/home/pi/communicate.txt");
        if (data.open(QFile::ReadOnly | QFile::Truncate)) {
            qDebug()<<"File Opened";          QByteArray buff2,Re_buff2;          buff2=data.readAll();
            Serial11->write(buff2);          Serial11->waitForBytesWritten(1000);          Serial11->waitForReadyRead(1000);
            Re_buff2=Serial11->readAll();          qDebug()<<"File Copy Answer:    ";          qDebug()<<Re_buff2.toHex();
        } else {          qDebug() << "Failed to open file" << data.error();      }

        //-----------------------------------------------------------------------------------------------------------------
        delay(200);



        //----------------------------Get Empty ID Form moving Template From Buffer To Flash--------------------------------
        GEmptyIDs[0]=0x55;    GEmptyIDs[1]=0xaa;    GEmptyIDs[2]=0x00;    GEmptyIDs[3]=0x00;    GEmptyIDs[4]=0x45;     GEmptyIDs[5]=0x00;    GEmptyIDs[6]=0x04;
        GEmptyIDs[7]=0x00;    GEmptyIDs[8]=0x01;   GEmptyIDs[9]=0x00;     GEmptyIDs[10]=0x88;   GEmptyIDs[11]=0x0B;
        for (k=12;k<=23;k++)
            GEmptyIDs[k]=0x00;
        GEmptyIDs[24]=CheckSum(GEmptyIDs)& 0xff;     GEmptyIDs[25]=CheckSum(GEmptyIDs) >> 8;
        Serial11->write(GEmptyIDs,26);     Serial11->waitForReadyRead(1000);
        int F_ID_L,F_ID_H;  Re_GEmptyIDs=Serial11->readAll();
        if(Re_GEmptyIDs[6]==0x04)  {  F_ID_L=Re_GEmptyIDs[10];  F_ID_H=Re_GEmptyIDs[11];  }
        qDebug()<<"Empty id :    "<<GEmptyIDs.toHex();
        qDebug()<<"Empty id Answer:    "<<Re_GEmptyIDs.toHex();
        //-----------------------------------------------------------------------------------------------------
        //------------------------------------------------------STORE Empty ID --------------------------------
        SStore[0]=0x55;    SStore[1]=0xaa;    SStore[2]=0x00;    SStore[3]=0x00;      SStore[4]=0x40;    SStore[5]=0x00;    SStore[6]=0x04;    SStore[7]=0x00;
        //qDebug()<<"Empty Ids: "<<Re_GEmptyIDs[10]<<Re_GEmptyIDs[11];
        SStore[8]=Re_GEmptyIDs[10];     SStore[9]=Re_GEmptyIDs[11];      SStore[10]=0x00;
        for (j=11;j<=23;j++)
            SStore[j]=0x00;
        SStore[24]= CheckSum(SStore)& 0xff;   SStore[25]=CheckSum(SStore) >> 8;
        Serial11->write(SStore,26);   Serial11->waitForBytesWritten(4000);
        Serial11->waitForReadyRead(1000);   Re_SStore=Serial11->readAll();
        qDebug()<<SStore.toHex();    qDebug()<<Re_SStore.toHex();
        //---------------------------- ----------------------------------
        if(Re_SStore[24]==0x42){

            //------------------  Read All images  -----------------
             QFile file_1("/media/pi/NEW/2"+id+"png");   QFile file_2("/media/pi/NEW/2"+id+"png");    QFile file_3("/media/pi/NEW/2"+id+"png");
             file_1.open(QIODevice::ReadOnly);   byte1=file_1.readAll();    file_1.close();
             file_2.open(QIODevice::ReadOnly);   byte2=file_2.readAll();    file_2.close();
             file_3.open(QIODevice::ReadOnly);   byte3=file_3.readAll();    file_3.close();
            query.prepare("INSERT INTO Person (id, FullName, CardNo, AccessType, FingerIdL, FingerIdH, Image1, Image2, Image3) "
                          "VALUES (:id, :FullName, :CardNo, :AccessType, :FingerIdL, :FingerIdH, :Image1, :Image2, :Image3)");



            qDebug()<<"On Saving";
            id=QString::number(id4);      name=SubCsvToString2[1];        cardno=SubCsvToString2[2];
            accesstype=SubCsvToString2[3]; fl=Re_GEmptyIDs[10]; fh=Re_GEmptyIDs[11];
            query.bindValue(":id", id);
            query.bindValue(":FullName", name);
            query.bindValue(":CardNo", cardno);
            query.bindValue(":AccessType", accesstype);
            query.bindValue(":FingerIdL", F_ID_L);
            query.bindValue(":FingerIdH", F_ID_H);
            query.bindValue(":Image1",byte1);
            query.bindValue(":Image2",byte2);
            query.bindValue(":Image3",byte3 );
            //qDebug()<<image5.size();
            if (query.exec())
                qDebug()<<"Saved";
        }  // End of While-------------------------------------------------------------------------------------
        //   else {       Dele[0]=0x55; Dele[1]=0xaa; Dele[2]=0x00; Dele[3]=0x00; Dele[4]=0x44; Dele[5]=0x00; Dele[6]=0x04; Dele[7]=0x00;
        //      Dele[8]=fl;    Dele[9]=fh;  Dele[10]=fl;    Dele[11]=fh;
        //     int h;
        //      for(h=12;h<=23;h++)
        //       Dele[h]=0x00;
        //     int xo=0x000;
        //   for (int i=0;i<=23 ;i++)
        //      xo+=Dele[i] ;
        //   Dele[24]=xo & 0xff;    Dele[25]=xo >> 8;    Serial11->write(Dele,26);   Serial11->waitForBytesWritten(10000);
        //     Serial11->waitForReadyRead(10000);            Re_Dele=Serial11->readAll();    qDebug()<<Re_Dele.toHex();    }
    }
    //--------------------------------------------- if open means we have a success full --------------------------------------------------------------

    if(CSVFile.exists()) {      ERR_DOWN_BUSY=true; emit ChangedDownBusy();  ERR_DOWN_BUSY=false; emit ChangedDownBusy();}
    qDebug()<< "--------------------------------  Finished ------------------------------------------------------";
    //ERR_DOWN_BUSY=false; emit ChangedDownBusy();
}

//--------------------------------------------------------------------------------------------
void Verify::DownFinger(){
    qDebug()<<"-------------------  On Downloading  ---------------------------------";
    int j,k,fl,fh,id2,id3,id4; QString id;
    int length1,length2,length;
    QByteArray FingerData,Command_Packet,Re_Command_Packet;
    QByteArray GEmptyIDs,Re_GEmptyIDs;    QByteArray SStore,Re_SStore;
    QSqlQuery query;
    QString id5,name,cardno,accesstype;
    QFile TemplateFile,CSVFile;  QString buffer;
    QStringList SubCsvToString1,SubCsvToString2;
    QRegExp rx("+++");
    QByteArray byte1,byte2,byte3;
    //------------------------------ Load Data File --------------------------------------------
    CSVFile.setFileName("/media/pi/New/Data.csv");
    if(CSVFile.exists()){
        if(!CSVFile.open(QIODevice::ReadOnly)) return;
        else buffer=CSVFile.readAll(); }

    //---------------------  Divide Main String To Records ---------------------------------------
    SubCsvToString1=buffer.split("+++");

    int i=0;
    while (SubCsvToString1[i]!=""){

        //---------------------- Divide Record(ith) To SubParts ----------------------------------------
        SubCsvToString2=SubCsvToString1[i].split(",");
        qDebug()<<"All Data Size:   "<<SubCsvToString1.length();
        qDebug()<<SubCsvToString2[0];
        qDebug()<<SubCsvToString2[1];
        qDebug()<<SubCsvToString2[2];
        i=i+1;
        fl=SubCsvToString2[4].toInt(); fh=SubCsvToString2[5].toInt();
        id2=fl; id3=fh << 8;  id4=id2+id3;   id5=QString::number(id4);

        //------------------------------------- Moving Templates To FingerPrint id file -------------------------------
        qDebug() << ("Moving Templates To FingerPrint id file:   ")<<id5;
        TemplateFile.setFileName("/media/pi/New/"+id5+".dat");
        if(!TemplateFile.open(QIODevice::ReadOnly)) { ERR_DOWN_BUSY=true; emit ChangedDownBusy();  ERR_DOWN_BUSY=false; emit ChangedDownBusy(); return; }
        FingerData=TemplateFile.readAll();
        TemplateFile.close();
        //------------------------------------------ Request For Move of Template To module----------------------------
        DFinger.clear(); DFinger[24]=0; DFinger[25]=0;
        DFinger[0]=0x55;    DFinger[1]=0xaa;    DFinger[2]=0x00;    DFinger[3]=0x00;    DFinger[4]=0x43;
        DFinger[5]=0x00;    DFinger[6]=0x02;    DFinger[7]=0x00;    DFinger[8]= 0xf4;   DFinger[9]=0x01;
        for (j=10;j<=23;j++)
            DFinger[j]=0x00;
        DFinger[24]=CheckSum(DFinger)& 0xff;      DFinger[25]=CheckSum(DFinger) >> 8;
        Serial11->write(DFinger,26);
        //Serial11->flush();
        Serial11->waitForBytesWritten(2000);  Serial11->waitForReadyRead(5000);     Re_DFinger=Serial11->readAll();
        qDebug()<<DFinger.toHex();  qDebug()<<Re_DFinger.toHex();
        delay(200);

        //--------------------------------------------------- Make Ready Data CommandPacket------------------------------
        Command_Packet[0]=0x5a;Command_Packet[1]=0xa5;  Command_Packet[2]=0x00;  Command_Packet[3]=0x00; Command_Packet[4]=0x43; Command_Packet[5]=0x00;
        Command_Packet[6]=0xf4; Command_Packet[7]=0x01; Command_Packet[8]=0x00; Command_Packet[9]=0x00;
        for(j=0;j<=497;j++)
            Command_Packet[j+10]=FingerData[j];
        Command_Packet[508]=CheckSum2(Command_Packet)& 0xff;     Command_Packet[509]=CheckSum2(Command_Packet) >> 8;
        qDebug() << ("Moving Templates To FingerPrint File:   ")<<id5;
        //-----------------------------  Write Command Data Packet To File  --------------------------------------------
        TemplateFile.setFileName("/home/pi/communicate.txt");
        if(!TemplateFile.open(QIODevice::WriteOnly)) return;      TemplateFile.write(Command_Packet);      TemplateFile.close();      delay(200);
        //------------------------------------- Write File To Serial Port ----------------------------------------------
        QFile data;       data.setFileName("/home/pi/communicate.txt");
        if (data.open(QFile::ReadOnly | QFile::Truncate)) {
            qDebug()<<"File Opened";          QByteArray buff2,Re_buff2;          buff2=data.readAll();
            Serial11->write(buff2);          Serial11->waitForBytesWritten(1000);          Serial11->waitForReadyRead(1000);
            Re_buff2=Serial11->readAll();          qDebug()<<"File Copy Answer:    ";          qDebug()<<Re_buff2.toHex();
        } else {          qDebug() << "Failed to open file" << data.error();      }

        //-----------------------------------------------------------------------------------------------------------------
        delay(200);



        //----------------------------Get Empty ID Form moving Template From Buffer To Flash--------------------------------
        GEmptyIDs[0]=0x55;    GEmptyIDs[1]=0xaa;    GEmptyIDs[2]=0x00;    GEmptyIDs[3]=0x00;    GEmptyIDs[4]=0x45;     GEmptyIDs[5]=0x00;    GEmptyIDs[6]=0x04;
        GEmptyIDs[7]=0x00;    GEmptyIDs[8]=0x01;   GEmptyIDs[9]=0x00;     GEmptyIDs[10]=0x88;   GEmptyIDs[11]=0x0B;
        for (k=12;k<=23;k++)
            GEmptyIDs[k]=0x00;
        GEmptyIDs[24]=CheckSum(GEmptyIDs)& 0xff;     GEmptyIDs[25]=CheckSum(GEmptyIDs) >> 8;
        Serial11->write(GEmptyIDs,26);     Serial11->waitForReadyRead(1000);
        int F_ID_L,F_ID_H;  Re_GEmptyIDs=Serial11->readAll();
        if(Re_GEmptyIDs[6]==0x04)  {  F_ID_L=Re_GEmptyIDs[10];  F_ID_H=Re_GEmptyIDs[11];  }
        qDebug()<<"Empty id :    "<<GEmptyIDs.toHex();
        qDebug()<<"Empty id Answer:    "<<Re_GEmptyIDs.toHex();
        //-----------------------------------------------------------------------------------------------------
        //------------------------------------------------------STORE Empty ID --------------------------------
        SStore[0]=0x55;    SStore[1]=0xaa;    SStore[2]=0x00;    SStore[3]=0x00;      SStore[4]=0x40;    SStore[5]=0x00;    SStore[6]=0x04;    SStore[7]=0x00;
        //qDebug()<<"Empty Ids: "<<Re_GEmptyIDs[10]<<Re_GEmptyIDs[11];
        SStore[8]=Re_GEmptyIDs[10];     SStore[9]=Re_GEmptyIDs[11];      SStore[10]=0x00;
        for (j=11;j<=23;j++)
            SStore[j]=0x00;
        SStore[24]= CheckSum(SStore)& 0xff;   SStore[25]=CheckSum(SStore) >> 8;
        Serial11->write(SStore,26);   Serial11->waitForBytesWritten(4000);
        Serial11->waitForReadyRead(1000);   Re_SStore=Serial11->readAll();
        qDebug()<<SStore.toHex();    qDebug()<<Re_SStore.toHex();
        //---------------------------- ----------------------------------
        if(Re_SStore[24]==0x42){

            //------------------  Read All images  -----------------
             QFile file_1("/media/pi/New/2"+id+"png");   QFile file_2("/media/pi/New/2"+id+"png");    QFile file_3("/media/pi/New/2"+id+"png");
             file_1.open(QIODevice::ReadOnly);   byte1=file_1.readAll();    file_1.close();
             file_2.open(QIODevice::ReadOnly);   byte2=file_2.readAll();    file_2.close();
             file_3.open(QIODevice::ReadOnly);   byte3=file_3.readAll();    file_3.close();
            query.prepare("INSERT INTO Person (id, FullName, CardNo, AccessType, FingerIdL, FingerIdH, Image1, Image2, Image3) "
                          "VALUES (:id, :FullName, :CardNo, :AccessType, :FingerIdL, :FingerIdH, :Image1, :Image2, :Image3)");



            qDebug()<<"On Saving";
            id=QString::number(id4);      name=SubCsvToString2[1];        cardno=SubCsvToString2[2];
            accesstype=SubCsvToString2[3]; fl=Re_GEmptyIDs[10]; fh=Re_GEmptyIDs[11];
            query.bindValue(":id", id);
            query.bindValue(":FullName", name);
            query.bindValue(":CardNo", cardno);
            query.bindValue(":AccessType", accesstype);
            query.bindValue(":FingerIdL", F_ID_L);
            query.bindValue(":FingerIdH", F_ID_H);
            query.bindValue(":Image1",byte1);
            query.bindValue(":Image2",byte2);
            query.bindValue(":Image3",byte3 );
            //qDebug()<<image5.size();
            if (query.exec())
                qDebug()<<"Saved";
        }  // End of While-------------------------------------------------------------------------------------
        //   else {       Dele[0]=0x55; Dele[1]=0xaa; Dele[2]=0x00; Dele[3]=0x00; Dele[4]=0x44; Dele[5]=0x00; Dele[6]=0x04; Dele[7]=0x00;
        //      Dele[8]=fl;    Dele[9]=fh;  Dele[10]=fl;    Dele[11]=fh;
        //     int h;
        //      for(h=12;h<=23;h++)
        //       Dele[h]=0x00;
        //     int xo=0x000;
        //   for (int i=0;i<=23 ;i++)
        //      xo+=Dele[i] ;
        //   Dele[24]=xo & 0xff;    Dele[25]=xo >> 8;    Serial11->write(Dele,26);   Serial11->waitForBytesWritten(10000);
        //     Serial11->waitForReadyRead(10000);            Re_Dele=Serial11->readAll();    qDebug()<<Re_Dele.toHex();    }
    }
    //-----------------------------------------------------------------------------------------------------------
    qDebug()<< "--------------------------------  Finished ------------------------------------------------------";
    ERR_DOWN_BUSY=true; emit ChangedDownBusy();  ERR_DOWN_BUSY=false; emit ChangedDownBusy();
    //ERR_DOWN_BUSY=false; emit ChangedDownBusy();
}

void Verify::PrintUnit(QStringList list,int printed,int let,int paper_hase)
{
    for (int i=0;i<list.count();i++)
    { qDebug()<<"index "<<i<< "is:"<<list[i]; }

    if(printed!=1 && let==1) {  //-------------------------------------------------------
        //align Center
        Serial13->write("\x1b\x61\x01");
        //Set Size
        Serial13->write("\x1d\x21\x01");
        //-------------------------------------------------
        Serial13->write("\x0a");
        //---------------------   Line 1 -----------------------------------
        PrintLetter(list[1]);
        Serial13->write("\x0c");
        Serial13->write("\x20");
        Serial13->write("\x0c");
        PrintLetter("رستوران");
        Serial13->write("\x0a");
        //Extract Restaurant Name

        //------------------  Line 2 -------------------------------------------------
        //-----align right ----
        Serial13->write("\x1b\x61\x02");
        if (list[4]=="1") {   PrintLetter("صبحانه");   }
        if (list[4]=="2") {   PrintLetter("نهار");     }
        if (list[4]=="3") {   PrintLetter("شام");      }
        if (list[4]=="6") {   PrintLetter("میان وعده");      }
        Serial13->write("\x20");
        Serial13->write("\x0c");
        Serial13->write(":");
        Serial13->write("\x0c");
        //Extract Restaurant Name
        PrintLetter(":وعده");
        Serial13->write("\x0c");
        Serial13->write("\x0a");
        //---------------------- 3 ------------------------------

        usleep(500);
        Serial13->write("\x1b\x40");
        Serial13->write("\x1b\x61\x02");
        PrintLetter(list[2]);
        Serial13->write(":");
        Serial13->write("\x0c");
        PrintLetter(" نام شخص");
        Serial13->write("\x0a");
    }

    //-------------------------------------------
    int cn=5;
    QString sss;
    QByteArray History;
    // ----   Reset Printer



    while ((cn+4) < list.size()-1 ) {
        //-----------------------------------------------------------------------------
        if(NoElseShow!=2)
        {if (cn==5) { ERR_FoodName1=list[8];  ERR_FoodCount1=list[9]; }
            if (cn==12) {ERR_FoodName2=list[15];  ERR_FoodCount2=list[16]; }
            if (cn==19) { ERR_FoodName3=list[22];  ERR_FoodCount3=list[23]; }
            //if (cn==26) { ERR_FoodName3=list[26];  ERR_FoodCount3=list[27]; }
        }
        if(NoElseShow==1) { NoElseShow=2;ERR_EFood== "تایید شد"; emit EFoodChanged();}

        qDebug()<<"--------------------  +++   ------     "<<ERR_FoodName1<<ERR_FoodName2<<ERR_FoodName3;

        //------------------  Line 3 -------------------------------------------------
        if(printed!=1 && let==1) {
            sss=list[cn];
            History=sss.toLocal8Bit();
            Serial13->write(History);
            Serial13->write("\x0c");
            Serial13->write(":");
            Serial13->write("\x0c");
            PrintLetter("تاریخ");
            Serial13->write("\x0c");
            Serial13->write("\x20\x20\x20");

            PrintLetter(list[cn+1]);
            Serial13->write("\x0c");
            Serial13->write(":");
            Serial13->write("\x0c");
            PrintLetter("روز");
            Serial13->write("\x0a");
            // Serial13->write("\x20\x20\x20");
            //  Serial13->write("\x0c");
            usleep(500);
            PrintLetter(list[cn+3]);
            Serial13->write(":");
            Serial13->write("\x0c");
            PrintLetter("نام غذا");
            Serial13->write("\x0a");
            //-----------------------------------------

            sss=list[cn+5];
            History=sss.toLocal8Bit();
            Serial13->write(History);
            Serial13->write("\x0c");
            // Serial13->write("\x20");
            Serial13->write("\x0c");
            Serial13->write(":");
            Serial13->write("\x0c");
            PrintLetter("ساعت");

            Serial13->write("\x20");
            sss=list[cn+2];
            History=sss.toLocal8Bit();
            Serial13->write(History);
            Serial13->write("\x0c");
            // Serial13->write("\x20");
            Serial13->write("\x0c");
            Serial13->write(":");
            Serial13->write("\x0c");
            qDebug()<<"قیمت";
            PrintLetter("قیمت");
            Serial13->write("\x0c");
            Serial13->write("\x20");
            Serial13->write("\x0c");
            sss=list[cn+4];
            History=sss.toLocal8Bit();
            Serial13->write(History);
            // PrintLetter(list[cn]);
            Serial13->write(":");
            Serial13->write("\x0c");
            PrintLetter("تعداد");
            Serial13->write("\x0a");
        }
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        cn=cn+7;
        usleep(500);
    } //end of while
    if(printed!=1 && let==1) {
        Serial13->write("\x0a");
        Serial13->write("................................");
        Serial13->write("\x0a");
        Serial13->write("\x0a"); }




}// end of let



void Verify::OpenSerialports()
{

    Serial11->open(QIODevice::ReadWrite);    qDebug()<<"Opened SRials in Verify";
    Serial12->open(QIODevice::ReadWrite);    qDebug()<<"Opened SRials in Verify";
    Serial13->open(QIODevice::ReadWrite);    qDebug()<<"Opened SRials in Verify";
    Serial11->write(TestConnection,26);  Serial11->waitForBytesWritten(500); Serial11->waitForReadyRead(1000); Re_TestConnection=Serial11->readAll();   qDebug()<<"Test Connection"<<Re_TestConnection;
   if(Re_TestConnection[0]!=0xaa && Re_TestConnection[1]!=0x55) {qDebug()<<"ERRRRROR"<<Re_TestConnection; Serial11->close(); Serial12->close(); delay(100);
    Serial11->setPortName("/dev/ttyUSB1");   Serial11->setBaudRate(115200); Serial11->open(QIODevice::ReadWrite);
    Serial12->setPortName("/dev/ttyUSB0");   Serial12->setBaudRate(9600);  Serial12->open(QIODevice::ReadWrite);}

    if(Serial11->isOpen())
    {qDebug()<<"Serial1 is Open";}
    if(Serial12->isOpen())
    {qDebug()<<"Serial2 is Open";}
    if(Serial13->isOpen())
    {qDebug()<<"Serial3 is Open";}
    Controller=1;


}

void Verify::DeleteAll()
{
    Dele[0]=0x55; Dele[1]=0xaa; Dele[2]=0x00; Dele[3]=0x00; Dele[4]=0x44; Dele[5]=0x00; Dele[6]=0x04; Dele[7]=0x00;
    Dele[8]=0x01; Dele[9]=0x00;    Dele[10]=0xD0; Dele[11]=0x07;
    int i;
    for(i=12;i<=23;i++)
        Dele[i]=0x00;
    int xo=0x000;
    for (int i=0;i<=23 ;i++)
        xo+=Dele[i] ;
    Dele[24]=xo & 0xff;
    Dele[25]=xo >> 8;
    Serial11->write(Dele,26);     Serial11->waitForBytesWritten(10000);
    Serial11->waitForReadyRead(10000); Re_Dele=Serial11->readAll();    qDebug()<<Re_Dele.toHex();
    if(Re_Dele[8]==0x00){
        qDebug()<<"Done";
        QSqlQuery query; query.prepare("Delete From Person");  if (query.exec()) { qDebug()<<"All Deleted";}
        query.prepare("Delete From RecordLog");  if (query.exec()) { qDebug()<<"All Deleted";}
        // QFile::remove("/home/pi/ImageDatabase/*.*"); QFile::remove("/home/pi/LBPH.xml"); QFile::remove("/home/pi/Fisher.xml");
    }}

QString Verify::Deleteone(QString id)
{    QSqlQuery query;     int controller=0; int fl,fh;
     int temp=id.toInt();     qDebug()<<id;    QString message="Failed";
      query.prepare("SELECT * From Person WHERE id=:temp");
       query.bindValue(":temp", temp);
        if(query.exec())
        { while (query.next()) {
                fl=query.value(4).toInt();
                fh=query.value(5).toInt();}}
        //id2=query.value(0).toInt();
        qDebug()<<"Successsssss";
         Dele[0]=0x55; Dele[1]=0xaa; Dele[2]=0x00; Dele[3]=0x00; Dele[4]=0x44; Dele[5]=0x00; Dele[6]=0x04; Dele[7]=0x00;
          Dele[8]=fl;    Dele[9]=fh;
           Dele[10]=fl;    Dele[11]=fh;
            int i;
             for(i=12;i<=23;i++)
                 Dele[i]=0x00;
              int xo=0x000;
               for (int i=0;i<=23 ;i++)
                   xo+=Dele[i] ;
                Dele[24]=xo & 0xff;
                 Dele[25]=xo >> 8;
                  Serial11->write(Dele,26);
                   Serial11->waitForBytesWritten(10000);
                    Serial11->waitForReadyRead(10000);
                     Re_Dele=Serial11->readAll();
                      qDebug()<<Re_Dele.toHex();
                       query.prepare("DELETE From Person WHERE id="+id+" ");
                        if (Re_Dele[6]==0x02){if(query.exec()){ message="Succcess";}}

                        return  message;}

void Verify::CloseSerialports()
{ Serial11->clear(); Serial12->clear();  Serial13->close();
    Serial11->close(); if (!Serial11->isOpen()) { qDebug()<<"Closed1"; }
    Serial12->close();  qDebug()<<"Closed2"; qDebug()<<"Closed3"; }
//----------------------------------
void Verify::ClearALL()
{ERR_STATE=1;
 VERR_READRFID=""; ERR_SAVEDPIC1=""; ERR_NAME=""; ERR_SECURITY="";
 emit VChangedRFID(); emit SavedPic1Changed(); emit SECURITYChanged(); emit NAMEChanged();
     counter2=0; ; emit SavedPic1Changed();}

//----------------------------------------------------------

void Verify::PrintLetter(QString name){
    qDebug()<<"-----------====";
    int cc=0;
    QByteArray Printtest;
    QByteArray AnswerPrinttest;
    QByteArray name1=name.toLocal8Bit();
    qDebug()<<"Length at "<<name1.toHex();


    for(int i=0;i<=1;i++)
    {  qDebug()<<name1<<name1.toHex();
    }
    for (int i=name1.size();i>0;i--)
    {   // if (name1[i]==0xd8 || name1[i]==0xd9) continue;
        //------------------  +   ------------
        if (name1[i]==0x2b)  {Serial13->write("+"); Serial13->write("\x0c"); continue; }
        //--------------------------------------------
        if (name1[i]==0x20)  { Serial13->write("\xff"); continue; }


        //  آ ا
        if (name1[i]==0xa2)  {Serial13->write("\x8d"); Serial13->write("\x0c"); continue; }
        if(i>2){if (name1[i]==0xa7 && name1[i-2]==0x20 && name1[i-1]==0xd8  )  {Serial13->write("\x90"); Serial13->write("\x0c"); cc=1; }}
        if(cc==1) {cc=0; continue; }
        if(i>2){if (name1[i]==0xa7 && ( name1[i+2]==0xaf || name1[i+2]==0xb0  || name1[i+2]==0xb1 ||name1[i+2]==0xb2|| name1[i+2]==0xaf || name1[i-2]==0xb0  || name1[i-2]==0xb1 ||name1[i-2]==0xb2||name1[i-1]==0x98||name1[i+2]==0x3a))  {Serial13->write("\x90"); Serial13->write("\x0c"); cc=1; }}
        if(cc==1) {cc=0; continue; }
        if (name1[i]==0xa7 && (name1[i-1]==0x20 ))  {Serial13->write("\x90"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xa7 && (name1[i-1]==0xd8 &&  name1[i+1]==0xd9 ))  {Serial13->write("\x90"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xa7 && name1[i-1]==0xd9)  {Serial13->write("\x90"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xa7)  {Serial13->write("\x91"); Serial13->write("\x0c"); continue;}

        //----  ---------------------------------------------------------
        if (name1[i]==0x20)  {Serial13->write("\xff"); Serial13->write("\x0c"); continue;}

        //  ب با   ------------------------------------------------
        if (name1[i]==0xa8 &&(i==name1.size()-1 ||  name1[i-1]==0x20))  {Serial13->write("\x92"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xa8)  {Serial13->write("\x93"); Serial13->write("\x0c"); continue;}

        //  پ   ------------------------------------------------
        if (name1[i]==0xbe &&  name1[i+1]==0x20)  {Serial13->write("\x94"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xbe &&  i==name1.size()-1)  {Serial13->write("\x94"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xbe)     {Serial13->write("\x95"); Serial13->write("\x0c"); continue;}
        //  ت  ------------------------------------------------
        if (name1[i]==0xaa && name1[i+1]==0x20)  {Serial13->write("\x96"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xaa &&  i==name1.size()-1)  {Serial13->write("\x96"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xaa)  {Serial13->write("\x97"); Serial13->write("\x0c"); continue; }
        //  ج   ------------------------------------------------
        if (name1[i]==0xac && name1[i+1]==0x20 )  {Serial13->write("\x9a"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xac && i==name1.size()-1 )  {Serial13->write("\x9a"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xac)  {Serial13->write("\x9b"); Serial13->write("\x0c"); continue;}
        // چ   ------------------------------------------------

        if (name1[i]==0xda && name1[i+1]==0x20)  {Serial13->write("\x9c"); Serial13->write("\x0c"); continue;}
        if (name1[i-1]==0xda && name1[i]==0x86)  {Serial13->write("\x9d"); Serial13->write("\x0c"); continue;}
        //if (name1[i]==0xda)  {Serial13->write("\x869d"); Serial13->write("\x0c"); continue;}
        //if (name1[86]==0xda  )  {Serial13->write("\x9d"); Serial13->write("\x0c"); continue;}
        //  ح  ------------------------------------------------
        if (name1[i]==0xad  && name1[i+1]==0x20  )  {Serial13->write("\x9e"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xad  && i==name1.size()-1  )  {Serial13->write("\x9e"); Serial13->write("\x0c"); continue; }
        if (name1[i]==0xad)  {Serial13->write("\x9f"); Serial13->write("\x0c"); continue; }
        //  خ  ------------------------------------------------
        if (name1[i]==0xae && name1[i+1]==0x20 )  {Serial13->write("\xa0"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xae &&  i==name1.size()-1 )  {Serial13->write("\xa0"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xae)  {Serial13->write("\xa1"); Serial13->write("\x0c"); continue;}
        // د -------------------------------------------------------------------
        if (name1[i]==0xaf)  {Serial13->write("\xa2"); Serial13->write("\x0c"); continue;}
        // ذ------------------------------------------------------------------
        if (name1[i]==0xb0)  {Serial13->write("\xa3"); Serial13->write("\x0c"); continue;}
        // ر -------------------------------------------------------------------
        if (name1[i]==0xb1)  {Serial13->write("\xa4"); Serial13->write("\x0c"); continue;}
        // ز -------------------------------------------------------------------
        if ((name1[i-1]==0xd8 || name1[i-1]==0xd9)  && name1[i]==0xb2)  {Serial13->write("\xa5"); Serial13->write("\x0c"); continue; }
        // ژ -------------------------------------------------------------------
        if (name1[i]==0x98)  {Serial13->write("\xa6"); Serial13->write("\x0c"); continue;}
        // س -------------------------------------------------------------------
        if (name1[i]==0xb3 && name1[i+1]==0x20 )  {Serial13->write("\xa7"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xb3 && i==name.size()-1)  {Serial13->write("\xa7"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xb3 && name1[i+1]==0x29)  {Serial13->write("\xb3\xa7\xb3"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xb3)  {Serial13->write("\xa8"); Serial13->write("\x0c"); continue; }
        // ش -------------------------------------------------------------------

        if (i==name1.size()-1 && name1[i]==0xb4) {Serial13->write("\xa9"); Serial13->write("\x0c"); continue;}
        if (name1[i+1]==0x20 && name1[i]==0xb4) {Serial13->write("\xa9"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xb4)  {Serial13->write("\xaa"); Serial13->write("\x0c"); continue;}
        // ص -------------------------------------------------------------------
        if ((i==name1.size()-1 ||  name1[i+1]==0x20) && name1[i]==0xb5) {Serial13->write("\xab"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xb5)  {Serial13->write("\xac"); Serial13->write("\x0c"); continue;}

        // ض -------------------------------------------------------------------
        if ((i==name1.size()-1 || name1[i+1]==0x20) && name1[i]==0xb6) {Serial13->write("\xad"); Serial13->write("\x0c"); continue;}
        if (name1[i+1]==0x20 && name1[i]==0xb6) {Serial13->write("\xad"); Serial13->write("\x0c"); continue;}
        if ((name1[i-1]==0xd8 ||name1[i-1]==0xd9) && name1[i]==0xb6)  {Serial13->write("\xae"); Serial13->write("\x0c"); continue;}

        // ط -------------------------------------------------------------------
        if (name1[i]==0xb7)  {Serial13->write("\xaf"); Serial13->write("\x0c"); continue;}
        // ظ -------------------------------------------------------------------
        if (name1[i]==0xb8)  {Serial13->write("\xe0"); Serial13->write("\x0c"); continue;}
        // ع -------------------------------------------------------------------
        if ((i==name1.size()-1 ||  name1[i+1]==0x20) && name1[i]==0xb9) {Serial13->write("\xe1"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xb9)  {Serial13->write("\xe4"); Serial13->write("\x0c"); continue;}
        // غ -------------------------------------------------------------------
        if ((i==name1.size()-1 ||  name1[i+1]==0x20) && name1[i]==0xba) {Serial13->write("\xe5"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xba)  {Serial13->write("\xe8"); Serial13->write("\x0c"); continue;}

        // ف -------------------------------------------------------------------
        if ((i==name1.size()-1 ||  name1[i+1]==0x20) && name1[i]==0x81) {Serial13->write("\xe9"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0x81)  {Serial13->write("\xea"); Serial13->write("\x0c"); continue;}
        //ق -------------------------------------------------------------------
        if ((i==name1.size()-1 ||  name1[i+1]==0x20) && name1[i]==0x82) {Serial13->write("\xeb"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0x82)  {Serial13->write("\xec"); Serial13->write("\x0c"); continue;}

        // ک -------------------------------------------------------------------
        if ((i==name1.size()-1 || name[i+1]==0x20) && name1[i]==0xa9) {Serial13->write("\xed"); Serial13->write("\x0c"); continue;}
        if (name1[i+1]==0x20 && name1[i]==0x83 ) {Serial13->write("\xed"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xa9)  {Serial13->write("\xee"); Serial13->write("\x0c"); continue;}
        if (name1[i-1]==0xd9 && name1[i]==0x83)  {Serial13->write("\xee"); Serial13->write("\x0c"); continue;}

        // گ -------------------------------------------------------------------
        if ((i==name1.size()-1 ||  name1[i-1]==0x20) && name1[i]==0xaf) {Serial13->write("\xef"); Serial13->write("\x0c"); continue;}
        if (name1[i-1]==0xda && name1[i]==0xaf)  {Serial13->write("\xf0"); Serial13->write("\x0c"); continue;}

        // ل -------------------------------------------------------------------
        if ((i==name1.size()-1 || name1[i+1]==0x20) && name1[i]==0x84 )  {Serial13->write("\xf1"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0x84)  {Serial13->write("\xf3"); Serial13->write("\x0c"); continue;}
        // م -------------------------------------------------------------------
        if ((i==name1.size()-1  || name1[i+1]==0x20) && name1[i]==0x85)  {Serial13->write("\xf4"); Serial13->write("\x0c"); continue;}
        if ( name1[i+1]==0x20 && name1[i]==0x85)  {Serial13->write("\xf4"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0x85)  {Serial13->write("\xf5"); Serial13->write("\x0c"); continue;}
        // ن -------------------------------------------------------------------
        if ((i==name1.size()-1 ||  name1[i+1]==0x20) && name1[i]==0x86 )  {Serial13->write("\xf6"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0x86)  {Serial13->write("\xf7"); Serial13->write("\x0c"); continue;}

        // و-------------------------------------------------------------------
        if (name1[i]==0x88)  {Serial13->write("\xf8"); Serial13->write("\x0c"); continue;}

        // ه-------------------------------------------------------------------
        if (name1[i]==0x87 && (name1[i+1]==0x20 ))  {Serial13->write("\xf9"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0x87 && (i==name1.size()-1 ))  {Serial13->write("\xf9"); Serial13->write("\x0c"); continue;}
        if(i>2){if (name1[i]==0x87 && (name1[i-2]==0x20 ))  {Serial13->write("\xfb"); Serial13->write("\x0c"); continue;} }
        if(i==1){if (name1[i]==0x87)  {Serial13->write("\xfb"); Serial13->write("\x0c"); continue;} }
        if (name1[i]==0x87 )  {Serial13->write("\xfa"); Serial13->write("\x0c"); continue;}

        // ي-------------------------------------------------------------------

        if ((i==name1.size()-1 || name1[i+1]==0x20 ) && name1[i]==0x8c )  {Serial13->write("\xfc"); Serial13->write("\x0c"); continue;}
        if (i==name1.size()-1  && name1[i]==0x8a)  {Serial13->write("\xfc"); Serial13->write("\x0c"); continue;}
        if ( name1[i+1]==0x20 && (name1[i]==0x8a || name1[i]==0x8c))  {Serial13->write("\xfc"); Serial13->write("\x0c"); continue;}
        if (name1[i-1]==0xd9 && name1[i]==0x8a)  {Serial13->write("\xfe"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0xbc )  {Serial13->write("\xfe"); Serial13->write("\x0c"); continue;}
        if (name1[i]==0x8c )  {Serial13->write("\xfe"); Serial13->write("\x0c"); continue;}
    }

}

void Verify::PrintNumber(QString number){

    QByteArray name1=number.toLocal8Bit();
    qDebug()<<"Length at "<<name1.toHex();
    qDebug()<<name1.toHex();
    for (int i=name1.size();i>0;i--)
    {
        //--------------------------------------------------------

        if (name1[i-1]==0xdb && name1[i]==0xb0 )  {Serial13->write("\x80"); Serial13->write("\x0c");}
        //----------------  ۱ ----------------
        if ( name1[i-1]==0xdb && name1[i]==0xb1 )  {Serial13->write("\x81"); Serial13->write("\x0c");}
        //----------------  ۲ ----------------
        if (name1[i-1]==0xdb && name1[i]==0xb2 )   {Serial13->write("\x82"); Serial13->write("\x0c");}
        //----------------  ۳ ----------------
        if ( name1[i-1]==0xdb && name1[i]==0xb3 )  {Serial13->write("\x83"); Serial13->write("\x0c");}
        //----------------  ۴ ----------------
        if (name1[i-1]==0xdb && name1[i]==0xb4 )  {Serial13->write("\x84"); Serial13->write("\x0c");}
        //---------------- ۵ ----------------
        if ( name1[i-1]==0xdb && name1[i]==0xb5 )  {Serial13->write("\x85"); Serial13->write("\x0c");}
        //----------------  ۶ ----------------
        if ( name1[i-1]==0xdb && name1[i]==0xb6 )  {Serial13->write("\x86"); Serial13->write("\x0c");}
        //----------------  ۷ ----------------
        if (name1[i-1]==0xdb && name1[i]==0xb7 )  {Serial13->write("\x87"); Serial13->write("\x0c");}
        //----------------  ۸ ----------------
        if ( name1[i-1]==0xdb && name1[i]==0xb8 )  {Serial13->write("\x88"); Serial13->write("\x0c");}
        //----------------  ۹ ----------------
        if ( name1[i-1]==0xdb && name1[i]==0xb9 )  {Serial13->write("\x89"); Serial13->write("\x0c");}
        //----------------  space ----------------
        if (name1[i-1]==0x20 && name1[i]==0xbc )  {Serial13->write("\x84"); Serial13->write("\x0c");}

    }
    //Serial13->write("\x95");
    //Serial13->write("\x0c");
    //Serial13->write("\x1b\x69");

}

void Verify::TestPrint()
{   plNoPerson->play();
    Serial13->write("---- TEST PRINTER---- ");   Serial13->write("\x0a");  Serial13->write("0123456789 "); Serial13->write("\x0a"); Serial13->write("\x0a"); }//-------------------------------------------------------------


void Verify::VolumController(int vol)
{  plNoReservedFood4->setVolume(vol);
    plOk->setVolume(vol); plNoPerson->setVolume(vol); plNoInternet10->setVolume(vol); plNoMealBegined8->setVolume(vol); plNoMealDefined7->setVolume(vol); plNoMachineinRest5->setVolume(vol); plNoRestaurantMember6->setVolume(vol); plNoConnectToDataBase9->setVolume(vol);   }//-------------------------------------------------------------
void Verify::inserter(){}


QString Verify::Insert_Into_ServerSetting(QString SA,QString DBN,QString U,QString Pa,QString TDS_Ver,QString Po)
{
    qDebug()<<"Insert Into DataBase";
    QSqlQuery query;   query.prepare("Delete From DataServerConfig ;");
    if(query.exec()) { qDebug()<<"All Deleted";  }
    query.prepare("INSERT INTO DataServerConfig (ServerName, DBName, UID, Password, Driver_Version, SqlPort) "
                  "VALUES (:ServerAddress, :DBName, :UID, :Password, :TDS_Version, :Port)");
    query.bindValue(":ServerAddress", SA);   query.bindValue(":DBName", DBN);  query.bindValue(":UID", U);
    query.bindValue(":Password", Pa);   query.bindValue(":TDS_Version", TDS_Ver);   query.bindValue(":Port", Po);

    if(query.exec())
    {    while (query.next()) { qDebug()<<"Saved to Database"; qDebug()<<"Initialize";   ERR_ServerAddress=SA;   ERR_DBName=DBN;   ERR_UID=U;   ERR_DBPassword=Pa;   ERR_TDS_Version=TDS_Ver;   ERR_Port=Po; } }


    Initialize_ServerSetting();
    return "با موفقیت ذخیره شد";
}
void Verify::Initialize_ServerSetting(){
    QSqlQuery query;   query.prepare("Select * From DataServerConfig ;");
    if(query.exec())
    { while (query.next()) {   qDebug()<<"Server Database Initialize";
            ERR_ServerAddress=query.value(0).toString();
            ERR_DBName=query.value(1).toString();
            ERR_UID=query.value(2).toString();
            ERR_DBPassword=query.value(3).toString();;
            ERR_TDS_Version=query.value(4).toString();;
            ERR_Port=query.value(5).toString();
        }}

    emit ServerAddressChanged(); emit DBNameChanged(); emit UIDChanged(); emit TDSVersionChanged(); emit PortChanged();}
void Verify::Insert_Into_Setting(int vol,int De,int DispOff){
    // --------------------- Reload All  -----------------------------
    qDebug()<<"Insert Into Setting DataBase";    QSqlQuery query;
    // INSERT FOR First Time
    //---------------------------- Insert  ---------------------------------------
    query.prepare("insert into Setting(Volume,Delay,DisplayOff) SELECT :vol,:De,:DispOff WHERE not exists (select * from Setting) ;");
    query.bindValue(":vol", vol);   query.bindValue(":De", De);   query.bindValue(":DispOff", DispOff); query.bindValue(":rowid", 1);
    qDebug()<<vol;
    qDebug()<<De;
    qDebug()<<DispOff;
    if(query.exec()) { qDebug()<<"SuccessFully INSERTED"; }
    //qDebug()<<query.lastError()
    //----------------------  Update All  -----------------------------
    query.prepare("UPDATE Setting Set Volume=:vol, Delay=:De, DisplayOff=:DispOff ");
    query.bindValue(":vol", vol);   query.bindValue(":De", De);   query.bindValue(":DispOff", DispOff); query.bindValue(":rowid", 1);  delay(50);
    if(query.exec())
    { Init_Setting(); }
}

void Verify::ClearImage(){  image4.load("/home/pi/unknown.jpeg");    }
void Verify::Init_Setting(){
    QSqlQuery query;   query.prepare("Select * From Setting ;");
    if(query.exec())
    { while (query.next()) {   qDebug()<<"Initialize Setting include (Volume,DisplayOff,Delay Time";
            ERR_SOUND=query.value(4).toInt();  ERR_DELAY=query.value(5).toInt();  ERR_DISPOFF= query.value(6).toInt(); PowerSaverCounter_Lim=ERR_DISPOFF;  VolumController(ERR_SOUND);
        }}
    else {VolumController(50); ERR_DISPOFF=20; PowerSaverCounter_Lim=ERR_DISPOFF; ERR_DELAY=5; }
    if(ERR_DISPOFF < 15)
    { ERR_DISPOFF=15; emit DisplayChanged();  }

    emit SoundChanged(); emit DelayChanged();    emit DisplayChanged();

}
void Verify::Get_Current_IP(){
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int nIter=0; nIter<list.count(); nIter++)
    {if(!list[nIter].isLoopback())
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                ip=list[nIter].toString();   }}
void Verify::OpenAllSerial(){
    if(!Serial11->isOpen()) {Serial11->clear();   Serial11->open(QIODevice::ReadWrite);}
    if(!Serial12->isOpen()) {Serial12->clear();   Serial12->open(QIODevice::ReadWrite);}
}
void Verify::CloseAllSerial(){
    if(Serial11->isOpen()) {Serial11->clear();   qDebug()<<"Closed Serial1";      Serial11->close();}
    if(Serial12->isOpen()) {Serial12->clear();   qDebug()<<"Closed Serial2";      Serial12->close();}
}
void Verify::Check_SerialPorts(){
    if(Serial11->isOpen()) { ERR_CHECKFINGER="پورت سریال ماژول اثر انگشت باز است"; emit CheckFingerChanged();  }
    if(!Serial11->isOpen()) { ERR_CHECKFINGER="پورت سریال ماژول اثر انگشت بسته است"; emit CheckFingerChanged();  }
    if(Serial12->isOpen()) { ERR_CHECKRFID="پورت سریال ماژول کارت خوان باز است"; emit CheckRFIDChanged();  }
    if(!Serial12->isOpen()) { ERR_CHECKRFID="پورت سریال ماژول کارت خوان بسته است"; emit CheckRFIDChanged();  }
    if(Serial13->isOpen()) { ERR_CHECKPRINTER="پورت سریال  چاپگر  باز است"; emit CheckPrinterChanged();  }
    if(!Serial13->isOpen()) { ERR_CHECKPRINTER="پورت سریال چاپگر  بسته است"; emit CheckPrinterChanged();  }}

void Verify::Detectore(){}

int Verify::E_Sound(){return ERR_SOUND;}
int Verify::E_DispOff(){return ERR_DISPOFF;}
int Verify::E_Delay(){return ERR_DELAY;}

int Verify::E_PROGRESS()
{ return ERR_PROGRESS; }

QString Verify::E_NAME()
{return ERR_NAME; }

int Verify::E_ID()
{return ERR_ID; }

int Verify::E_CARDNO()
{ return ERR_CARDNO; }

QString Verify::E_SECURITY()
{return ERR_SECURITY; }

QString Verify::E_SAVEDPIC1()
{return ERR_SAVEDPIC1; }

int Verify::VE_READFINGER()
{ return VERR_READFINGER; }

QString Verify::VE_READRFID()
{ return VERR_READRFID;}

int Verify::E_ACCURACY()
{    return ERR_ACCURACY; }
int Verify::E_STREAM1(){
    return ERR_STREAM1;}
int Verify::E_STREAM2(){
    return ERR_STREAM2;}
int Verify::E_VALUE()
{    return Value;   }
QString Verify::E_STATE()
{    return ERR_STATE;   }
void Verify::WriteController()
{    Controller=1;}
QString Verify::E_EFood()
{   return ERR_EFood;  }
QString Verify::E_FoodName1()
{   return ERR_FoodName1;  }
QString Verify::E_FoodName2()
{   return ERR_FoodName2;  }
QString Verify::E_FoodName3()
{   return ERR_FoodName3;  }
QString Verify::E_FoodCount1()
{   return ERR_FoodCount1; }
QString Verify::E_FoodCount2()
{   return ERR_FoodCount2; }
QString Verify::E_FoodCount3()
{   return ERR_FoodCount3; }

QString Verify::E_ServerAddress(){
    return ERR_ServerAddress;}
QString Verify::E_DBName(){
    return ERR_DBName;}
QString Verify::E_UID(){
    return ERR_UID;}
QString Verify::E_DBPassword(){
    return ERR_DBPassword;}
QString Verify::E_TDS_Version(){
    return ERR_TDS_Version;}
QString Verify::E_Port(){
    return ERR_Port;}

bool Verify::E_ReadUpBusy(){
    return  ERR_UP_BUSY; }
bool Verify::E_ReadUpDialog(){
    return  ERR_UP_DIALOG; }
bool Verify::E_ReadDownBusy(){
    return  ERR_DOWN_BUSY;}
int Verify::CheckSum(QByteArray input)
{int xo=0x000;
    for (int i=0;i<=23 ;i++)  {xo+=input[i];}
    return xo;}
int Verify::CheckSum2(QByteArray input)
{long int xo1=0x0000;
    int xo=0x00;
    for (int sv=0;sv<=507 ;sv++)  {xo1+=input[sv];}
    xo=xo1;
    return xo;}
