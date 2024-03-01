#include "fingersign.h"
#include <QtDebug>
#include <QtSerialPort>
#include <QDebug>
#include <QQuickImageProvider>
#include <QDebug>
#include <QSqlQuery>
#include <QAbstractVideoFilter>
#include <QDebug>
#include <QTemporaryFile>
#include <QMutex>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QImage>
#include <QtGui>
#include <QtCore/QCoreApplication>
#include <verify.h>
#include <QTime>
#include <wiringPi.h>
#include <QImage>
#include <exception>
//#include <raspicam/raspicam.h>
#include <raspicam/raspicam_cv.h>
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
//VideoCapture cap(0);
int frameHeight;
int frameWidth;
QImage image;
QImage image1,image2,image3;
//-----------------------------------------------------------------------------

FingerSign::FingerSign(QObject *parent) : QObject(parent) , QQuickImageProvider(QQuickImageProvider::Image)
{
    qDebug()<<"initialize FingerSign";
    Serial31=new QSerialPort(this);
    Serial32=new QSerialPort(this);


    Serial32->setPortName("/dev/ttyUSB1"); //COM-port
    Serial32->setBaudRate(115200);
    Serial32->setStopBits(QSerialPort::OneStop);
    Serial32->setParity(QSerialPort::NoParity);
    Serial32->setDataBits(QSerialPort::Data8);
    //******************** Setup Serial Port RFID *********************************************************
    Serial31->setPortName("/dev/ttyUSB0"); //COM-port
    Serial31->setParity(QSerialPort::NoParity);
    Serial31->setDataBits(QSerialPort::Data8);
    Serial31->setBaudRate(9600);
    Serial31->setStopBits(QSerialPort::OneStop);

    connect(Serial31,SIGNAL(readyRead()), this, SLOT(readdata31()));
    //COM-port that arduino is connected to
    //Serial31->open(QIODevice::ReadWrite);

    //-------------  Load face Classifier -------------------
    if( faceCade_1.load( faceCascadeName_1 ) ) {
                qDebug()<<"loaded successfully"; }
    if(!Camera.isOpened()){qDebug()<<"Camera is Close, Now Opening"; Camera.open();    }
   // Camera.set( CV_CAP_PROP_FORMAT, CV_8UC2);
    //Camera.set( CV_CAP_PROP_FRAME_WIDTH, 640 );
   // Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 480 );


}
FingerSign::~FingerSign() { }
QImage FingerSign::requestImage(const QString& id, QSize* size, const QSize& requestedsize)
{ result=image;   qDebug()<<result.size();  if(size) { *size = result.size();   }
      return result;}


QString FingerSign::OpenSerial()
{   if( Serial31->open(QIODevice::ReadWrite)){ qDebug()<<"Finger Print Opened";}
    if( Serial32->open(QIODevice::ReadWrite)){  qDebug()<<"RFID Opened";}
    if( Serial31->isOpen())
        qDebug()<<"   isopen ----";
    if(Serial32->isOpen())
        qDebug()<<"   isopen ----";
    //******************** Test Connection to Serial Port *************************************************
    TestConnection[0]=0x55; TestConnection[1]=0xaa; TestConnection[2]=0x00; TestConnection[3]=0x00; TestConnection[4]=0x01; TestConnection[5]=0x00;  TestConnection[6]=0x00; TestConnection[7]=0x00;
    TestConnection[8]=0x00; TestConnection[9]=0x00; TestConnection[10]=0x00; TestConnection[11]=0x00;    TestConnection[12]=0x00; TestConnection[13]=0x00; TestConnection[14]=0x00; TestConnection[15]=0x00; TestConnection[16]=0x00; TestConnection[17]=0x00;
    TestConnection[18]=0x00; TestConnection[19]=0x00; TestConnection[20]=0x00; TestConnection[21]=0x00; TestConnection[22]=0x00; TestConnection[23]=0x00; TestConnection[24]=0x00; TestConnection[25]=0x01;

    qDebug()<<"Test Connection"<<Re_TestConnection;
    Serial32->write(TestConnection,26);  Serial32->waitForBytesWritten(500); Serial32->waitForReadyRead(1000); Re_TestConnection=Serial32->readAll();   qDebug()<<"Test Connection"<<Re_TestConnection;
   if(Re_TestConnection[0]!=0xaa && Re_TestConnection[1]!=0x55) {qDebug()<<"ERRRRROR"<<Re_TestConnection; Serial31->close(); Serial32->close(); delay(100);
    Serial31->setPortName("/dev/ttyUSB1");   Serial31->setBaudRate(9600); Serial31->open(QIODevice::ReadWrite);
    Serial32->setPortName("/dev/ttyUSB0");   Serial32->setBaudRate(115200);  Serial32->open(QIODevice::ReadWrite);       }

    //******************** Setup Serial Port Printer *********************************************************

    emit ChangedSerial32();
    return  ERR_Serial32;
}
void FingerSign::CloseSerial()
{    Serial31->clear();
     Serial32->clear();
      if (Serial32->isOpen())
          Serial32->close();
      if (Serial31->isOpen())
          Serial31->close();

      if(!Serial31->isOpen())
          qDebug() << "Serial1 is Close";
      if(!Serial32->isOpen())
          qDebug() << "Serial2 is Closed";
}
void FingerSign::Detector()
{       
    int i;

    try{
    Camera.grab();
    Camera.retrieve (camFrames_1);
    cout<<"Stop camera..."<<endl;
    camFrames_1=camFrames_1(Rect(330,120,600,600));
    cv::flip(camFrames_1,camFrames_1,-1);
    cv::flip(camFrames_1,camFrames_1,1);
    //camFrames2=camFrames2(Rect(0,0,640,480));
    //cv::flip(camFrames2,camFrames2,1);
    qDebug()<<camFrames_1.rows;
    frameHeight = camFrames_1.rows;     frameWidth = camFrames_1.cols;
    cvtColor(camFrames_1, grayFrames_1, CV_BGR2GRAY);
    faceCade_1.detectMultiScale(grayFrames_1, faces, 1.5, 5, 0, Size(150, 150));
    qDebug()<<"counter is:"<< counter;

    if(faces.size()==0) { ReleaseCapture=1; counter=0;}
    for(i=0;i<faces.size();i++)
    {counter=counter+1;
      if(faces[0].x+faces[0].width<=camFrames_1.cols && faces[0].y+faces[0].height<=camFrames_1.rows && 0<faces[0].x-50>0 && faces[0].y-50>0)
         {
          faceROI=grayFrames_1(Rect(faces[0].x, faces[0].y ,faces[0].width,faces[0].height));
          rectangle(camFrames_1, Rect(faces[0].x,faces[0].y, faces[0].width,faces[0].height),  Scalar(0, 255, 0), 5, 1, 0);
          Size size(200,200);   resize(faceROI,faceROI,size);
                          if (count_of_capture==0 && counter>6) {
                            qDebug()<<"image 1 Saved"; counter=0; ReleaseCapture=0;
                            image1= QImage(faceROI.data,  faceROI.cols,faceROI.rows, static_cast<int>(faceROI.step),QImage::Format_Indexed8);
                            image1.save("/home/pi/cap1","png"); //shutter->play();
                            ERR_SAVEDPIC="تصویر شماره ۱ ذخیره شد";       emit ChangedSavedPic();
                            counter=0;
                            count_of_capture=count_of_capture+1;}

                            if (count_of_capture==1 && counter>6) { qDebug()<<"image 2 Saved";     counter=0; ReleaseCapture=0;
                            image2= QImage(faceROI.data,  faceROI.cols,faceROI.rows, static_cast<int>(faceROI.step),QImage::Format_Indexed8);
                            image2.save("/home/pi/cap2","png"); //shutter->play();
                            ERR_SAVEDPIC="تصویر شماره 2 ذخیره شد";        emit ChangedSavedPic();
                            counter=0;
                            count_of_capture=count_of_capture+1;}

                            if (count_of_capture==2 && counter>6) {  qDebug()<<"image 3 Saved";  counter=0; ReleaseCapture=0;
                            image3= QImage(faceROI.data,  faceROI.cols,faceROI.rows, static_cast<int>(faceROI.step),QImage::Format_Grayscale8);
                            image3.save("/home/pi/cap3","png"); //shutter->play();
                            ERR_SAVEDPIC="تصویر شماره 3 ذخیره شد";        emit ChangedSavedPic();
                            counter=0;
                            count_of_capture=count_of_capture+1;}

                           }//if faces Size is Standard
                         }//if Confidence <0.7



      image= QImage((uchar*) camFrames_1.data,600 ,600, camFrames_1.step, QImage::Format_RGB888);
}
  catch(std::exception &e) {}
}
void FingerSign::readdata31()
{  ERR_RFID=""; emit ChangedRFID();   ERR_RFID=Serial31->readAll();
    qDebug()<<"RFID VALUE";
    qDebug()<<ERR_RFID;
    ERR_RFID.remove(QRegExp("[\n\t\r\a\d]"));  qDebug()<<ERR_RFID; emit ChangedRFID();  }
int FingerSign::Checksum(QByteArray input)
{
    int xo=0x000;
    for (int i=0;i<=23 ;i++)
        xo+=input[i] ;
    return xo;}
void FingerSign::ConnectionTest(){   }
void FingerSign::GETStatus(QString id2){
    int id;
    id=id2.toInt();
    ERR_STATUS="شماره شناسه مورد تایید نیست";
    //id=18;
    Permitt[0]=0x55;    Permitt[1]=0xaa;    Permitt[2]=0x00;    Permitt[3]=0x00;    Permitt[4]=0x46;
    Permitt[5]=0x00;    Permitt[6]=0x04;    Permitt[7]=0x00;    Permitt[8]=id& 0xff;   Permitt[9]=id >> 8;
    Permitt[10]=id& 0xff;   Permitt[11]=id >> 8;
    int i=0;
    for (i=12;i<=23;i++)
        Permitt[i]=0x00;

    Permitt[24]=Checksum(Permitt)& 0xff;
    Permitt[25]=Checksum(Permitt) >> 8;
    Serial32->write(Permitt,26);
    Serial32->waitForReadyRead(1000);
    ERR_FingerIdL=id& 0xff;
    Re_Permitt=Serial32->readAll();
    qDebug()<< Re_Permitt.toHex();
    if(Re_Permitt[6]==0x04)  {ERR_STATUS="شماره شناسه مورد تایید است"; emit ChangedStatus(); state=0; step=1; }
}
void FingerSign::CheckUserName()
{}
void FingerSign::GetEmptyId(){

    Serial32->clear();
    ERR_GetEmptyId="";
    GEmptyId.clear();
    Re_GEmptyId.clear();
    //id=18;
    GEmptyId[0]=0x55;    GEmptyId[1]=0xaa;    GEmptyId[2]=0x00;    GEmptyId[3]=0x00;    GEmptyId[4]=0x45;
    GEmptyId[5]=0x00;    GEmptyId[6]=0x04;    GEmptyId[7]=0x00;    GEmptyId[8]=01;   GEmptyId[9]=00;
    GEmptyId[10]=0xB8;   GEmptyId[11]=0x0B;
    int i=0;
    for (i=12;i<=23;i++)
        GEmptyId[i]=0x00;


    GEmptyId[24]=Checksum(GEmptyId)& 0xff;
    GEmptyId[25]=Checksum(GEmptyId) >> 8;
    Serial32->write(GEmptyId,26);
    Serial32->waitForReadyRead(1000);

    Re_GEmptyId=Serial32->readAll();
    qDebug()<< Re_GEmptyId.toHex();
    if(Re_GEmptyId[6]==0x04)  {ERR_GetEmptyId="شناسه تخصیص داده شد"; emit ChangedGetEmptyId(); state=0; step=1;
       // Re_GEmptyId[10]=0xfe; Re_GEmptyId[11]=0x01;
        F_ID_L=Re_GEmptyId[10];  F_ID_H=Re_GEmptyId[11];
    }
    if(Re_GEmptyId[6]==0x02)  {ERR_GetEmptyId="حافظه تکمیل است"; emit ChangedGetEmptyId(); }
}
void FingerSign::f_RW_Image(){
    state++;
    f_Write_Image();
    Serial32->waitForBytesWritten(1000);
    Serial32->waitForReadyRead(1000);
    Re_GetImage=Serial32->readAll();
    qDebug()<< Re_GetImage.toHex();
    qDebug()<<step;
    if (Re_GetImage[24]==0x22 && step==1 )  {
        ERR_Image1="با تشکر";  emit ChangedImage1();  step=2; state=0; f_Generate1();}
    else if (Re_GetImage[24]==0x22 && step==2 )  {
        ERR_Image2="با تشکر";  emit ChangedImage2();  step=3; state=0; f_Generate2();}
    else if (Re_GetImage[24]==0x22 && step==3 )  {
        ERR_Image3="با تشکر";  emit ChangedImage3(); state=0; f_Generate3();}
}
void FingerSign::f_Generate1()
{   Generate1[0]=0x55;    Generate1[1]=0xaa;    Generate1[2]=0x00;    Generate1[3]=0x00;    Generate1[4]=0x60;
    Generate1[5]=0x00;    Generate1[6]=0x02;    Generate1[7]=0x00;    Generate1[8]=0x00;
    int i=0;
    for (i=9;i<=23;i++)
        Generate1[i]=0x00;

    Generate1[24]=Checksum(Generate1)& 0xff;
    Generate1[25]=Checksum(Generate1) >> 8;
    Serial32->write(Generate1,26);
    Serial32->waitForBytesWritten(1000);
    Serial32->waitForReadyRead(1000);
    Re_Generate1=Serial32->readAll();
    qDebug()<<"inGeneration";
    qDebug()<< Re_Generate1.toHex();
    if(Re_Generate1[24]==0x62){  ERR_Generate1="با موفقیت انجام شد"; emit ChangedGenerate1(); step=2;
        state++;}

    qDebug()<<Re_Generate1.toHex();
    if(state==30){ ERR_Generate1="انگشت روی سنسور قرار ندارد";  emit ChangedGenerate1();  }
}
void FingerSign::f_Generate2()
{   Generate2[0]=0x55;    Generate2[1]=0xaa;    Generate2[2]=0x00;    Generate2[3]=0x00;    Generate2[4]=0x60;
    Generate2[5]=0x00;    Generate2[6]=0x02;    Generate2[7]=0x00;    Generate2[8]=0x01;
    int i=0;
    for (i=9;i<=23;i++)
        Generate2[i]=0x00;
    Generate2[24]=Checksum(Generate2)& 0xff;
    Generate2[25]=Checksum(Generate2) >> 8;
    Serial32->write(Generate2,26); state=0;
    Serial32->waitForBytesWritten(1000);
    Serial32->waitForReadyRead(1000);
    Re_Generate2=Serial32->readAll();
    qDebug()<< Re_Generate2.toHex();

    if(Re_Generate2[24]==0x62){ ERR_Generate2="با موفقیت انجام شد"; emit ChangedGenerate2();}
    if(state==30){ERR_Generate2="Fail";  emit ChangedGenerate2(); }
}
void FingerSign::f_Generate3()
{
    Generate3[0]=0x55;    Generate3[1]=0xaa;    Generate3[2]=0x00;    Generate3[3]=0x00;    Generate3[4]=0x60;
    Generate3[5]=0x00;    Generate3[6]=0x02;    Generate3[7]=0x00;    Generate3[8]=0x02;
    int i=0;
    for (i=9;i<=23;i++)
        Generate3[i]=0x00;
    Generate3[24]=0x63;    Generate3[25]=0x01;

    Serial32->write(Generate3,26); state=0;

    Serial32->waitForBytesWritten(1000);
    Serial32->waitForReadyRead(1000);
    Re_Generate3=Serial32->readAll();
    qDebug()<< Re_Generate3.toHex();
    if(Re_Generate3[24]==0x62){ ERR_Generate3="با موفقیت انجام شد";  emit ChangedGenerate3(); step=3;}

}

//--------------------------------Write Part ---------------------------

void FingerSign::f_Write_Status() {}

void FingerSign::f_Write_ID(){    }

void FingerSign::f_Write_Image()
{

    GetImage[0]=0x55;    GetImage[1]=0xaa;    GetImage[2]=0x00;
    GetImage[3]=0x00;    GetImage[4]=0x20;
    int i=0;
    for (i=5;i<=23;i++)
        GetImage[i]=0x00;

    GetImage[24]=Checksum(GetImage)& 0xff;
    GetImage[25]=Checksum(GetImage) >> 8;
    Serial32->write(GetImage,26); state=0;


}


void FingerSign::f_Merge()
{
    merge[0]=0x55;    merge[1]=0xaa;    merge[2]=0x00;    merge[3]=0x00;    merge[4]=0x61;    merge[5]=0x00;
    merge[6]=0x03;    merge[7]=0x00;    merge[8]=0x00;    merge[9]=0x00;    merge[10]=0x03;
    int i=0;
    for (i=11;i<=23;i++)
        merge[i]=0x00;
    merge[24]=0x66;    merge[25]=0x01;
    Serial32->write(merge,26);
    Serial32->waitForBytesWritten(3000);
    Serial32->waitForReadyRead(5000);
    Re_merge=Serial32->readAll();
    qDebug()<<Re_merge.toHex();
    if(Re_merge[24]==0x63){ ERR_MERGE="تلفیق نمونه انجام شد";  emit ChangedMerge(); }
    if(Re_merge[24]!=0x63){ ERR_MERGE="خطا در تلفیق";  emit ChangedMerge(); Serial32->clear();    }

}

void FingerSign::f_Store()
{
    Store[0]=0x55;    Store[1]=0xaa;    Store[2]=0x00;    Store[3]=0x00;
    Store[4]=0x40;    Store[5]=0x00;    Store[6]=0x04;    Store[7]=0x00;
    qDebug()<<"------------"<<Re_GEmptyId[10]<<"------"<<Re_GEmptyId[11];
    Store[8]=Re_GEmptyId[10];
    Store[9]=Re_GEmptyId[11];
    Store[10]=0x00;

    int i=0;
    for (i=11;i<=23;i++)
        Store[i]=0x00;


    Store[24]= Checksum(Store)& 0xff;
    Store[25]=Checksum(Store) >> 8;

    Serial32->write(Store,26);
    Serial32->waitForBytesWritten(4000);
    Serial32->waitForReadyRead(4000);
    Re_Store=Serial32->readAll();
    qDebug()<<Store.toHex();
    qDebug()<<Re_Store.toHex();
    if(Re_Store[24]==0x42 && ERR_MERGE!="خطا در تلفیق"){
        ERR_STORE="با موفقیت ذخیره شد";
        ERR_FingerIdL=  Re_GEmptyId[10];  ERR_FingerIdH=Re_GEmptyId[11];
        qDebug()<<"EMPTY IFDL  is:"<<ERR_FingerIdL;
         emit ChangedFingerIdL(); emit ChangedFingerIdH(); Serial32->clear(); }
    if(Re_Store[8]==0x18){qDebug()<<Re_Store;
        ERR_STORE="این انگشت قبلا ذخیره شده است"; Serial32->clear();}
    emit ChangedStore();
}


void FingerSign::Deleter()
{
    Dele[0]=0x55; Dele[1]=0xaa; Dele[2]=0x00; Dele[3]=0x00; Dele[4]=0x44; Dele[5]=0x00; Dele[6]=0x04; Dele[7]=0x00;
    Dele[8]=0x01; Dele[9]=0x00;
    Dele[10]=0xFF; Dele[11]=0x00;

    int i;
    for(i=12;i<=23;i++)
        Dele[i]=0x00;

    int xo=0x000;
    for (int i=0;i<=23 ;i++)
        xo+=Dele[i] ;


    Dele[24]=xo & 0xff;
    Dele[25]=xo >> 8;


    Serial32->write(Dele,26);
    Serial32->waitForBytesWritten(5000);
    Serial32->waitForReadyRead(5000);
    Re_Dele=Serial32->readAll();
}
void FingerSign::init_Detector(){
    ERR_SAVEDPIC=""; emit ChangedSavedPic();
    ERR_SAVEDPIC="در حال برداشت تصویر"; emit ChangedSavedPic();}
void::FingerSign::Clear()

{   ConnTest.clear(); Re_ConnTest.clear(); GetId.clear(); Re_GetId.clear(); Permitt.clear(); Re_Permitt.clear();    GetImage.clear();
    Re_GetImage.clear();    Generate1.clear();    Re_Generate1.clear();    Generate2.clear(); Re_Generate2.clear();    Generate3.clear();
    Re_Generate3.clear(); GEmptyId.clear(); Re_GEmptyId.clear();    merge.clear();   Re_merge.clear(); Store.clear(); Re_Store.clear();
    del.clear(); Dele.clear(); Re_Dele.clear();    GEmptyId.clear(); Re_GEmptyId.clear();
    ERR_ChekDuplicateId=""; ERR_GetEmptyId="";    ERR_ID=""; ERR_STORE=""; ERR_MERGE=""; ERR_Image2="";  ERR_STATUS="";   ERR_Generate1=""; ERR_STATUS="";
    ERR_Image1=""; ERR_Image3=""; ERR_Generate2="";  ERR_Generate3=""; ERR_RFID="";
    ERR_SAVEDPIC="در حال برداشت تصویر";

    emit ChangedRFID();    emit ChangedStore();   // emit ChangedID();
    emit ChangedMerge();    emit ChangedImage1();   emit ChangedImage2();    emit ChangedImage3();
    emit ChangedGenerate1();   emit ChangedGenerate2();  emit ChangedGenerate3(); emit ChangedID();
    emit ChangedGetEmptyId(); emit ChangedCheckUser(); emit ChangedStatus(); emit ChangedGetEmptyId();
    qDebug()<<"------------------------ All Variable Cleared  ---------------------------------------------";
    emit ChangedSavedPic();
    QFile file1("/home/pi/cap1");   QFile file2("/home/pi/cap2");    QFile file3("/home/pi/cap3");
    file1.remove(); file2.remove(); file3.remove();


}
void::FingerSign::Clear2()

{ ConnTest.clear(); Re_ConnTest.clear(); GetId.clear(); Re_GetId.clear(); Permitt.clear(); Re_Permitt.clear();
    GetImage.clear();     Re_GetImage.clear();    Generate1.clear();    Re_Generate1.clear();
    Generate2.clear(); Re_Generate2.clear();    Generate3.clear(); Re_Generate3.clear(); GEmptyId.clear(); Re_GEmptyId.clear();
    merge.clear();   Re_merge.clear(); Store.clear(); Re_Store.clear(); del.clear(); Dele.clear(); Re_Dele.clear();


    ERR_GetEmptyId=""; emit ChangedGetEmptyId();
    ERR_STATUS=""; emit ChangedStatus();
    ERR_Generate1="";  emit ChangedGenerate1();
    ERR_Image1=""; emit ChangedImage1();
    ERR_Image2=""; emit ChangedImage2();
    ERR_Image3=""; emit ChangedImage3();
    ERR_Generate1=""; emit ChangedGenerate1();
    ERR_Generate2="";  emit ChangedGenerate2();
    ERR_Generate3="";  emit ChangedGenerate3();
    ERR_ChekDuplicateId=""; emit ChangedGetEmptyId();
    ERR_STATUS.clear(); ERR_STORE.clear(); ERR_ChekDuplicateId.clear(); ERR_Generate1.clear(); ERR_Generate2.clear(); ERR_Generate3.clear();
    ERR_Image1.clear(); ERR_Image2.clear(); ERR_Image3.clear(); ERR_GetEmptyId.clear();
    ERR_ChekDuplicateCardNo="";
    ERR_STORE=""; emit ChangedStore();
    ERR_MERGE="";  emit ChangedMerge();
       // emit ChangedID();

     emit ChangedGenerate2();  emit ChangedGenerate3(); emit ChangedID(); emit ChangedGetEmptyId();  emit ChangedCheckUser();
    emit ChangedStatus(); emit ChangedGetEmptyId(); emit ChangedCardNoDup();
    qDebug()<<"CLEARED----------------------------";
}


void FingerSign::CheckDuplicateId(QString Id)
{
    qDebug()<<"---------------------------------Step  Check Duplicate ID--------------------------";
    int Id2=Id.toInt();
    QSqlQuery query;
    query.prepare("SELECT * From Person WHERE id= :id ;");
    //  QByteArray outByteArray;     QPixmap TempImg;     qDebug()<< finger;
    ERR_ChekDuplicateId="شناسه معتبر است";
    int temp=0;
    query.bindValue(":id", Id2);
    if(query.exec())
    {    while (query.next()) {
            qDebug()<<"  on Processs";
            // emit VChangedRFID();   emit NAMEChanged();       emit IDChanged();     emit CARDNOChanged();   emit SECURITYChanged();  emit Stream2Changed();
        }}
    if(temp==1) {ERR_ChekDuplicateId="این شناسه قبلا مورد استفاده قرار گرفته است"; temp=0; }

    emit ChangedCheckUser();
}


QString FingerSign::SaveData(QString id,QString fullname,QString cardno,QString Accesstype)
{

    QSqlQuery query;
    query.prepare("INSERT INTO Person (id, FullName, CardNo, AccessType, FingerIdL, FingerIdH) "
                  "VALUES (:id, :FullName, :CardNo, :AccessType, :FingerIdL, :FingerIdH)");


    char fdH=Re_GEmptyId[10];
    char fdL=Re_GEmptyId[11];
    //char img=0;

    query.bindValue(":id", id);
    query.bindValue(":FullName",fullname);
    query.bindValue(":CardNo", cardno);
    query.bindValue(":AccessType", Accesstype);
    query.bindValue(":FingerIdL", fdL);
    query.bindValue(":FingerIdH", fdH);
    //qDebug()<<image5.size();
    if (query.exec())
    { qDebug()<<"ok Saved";}
    //  else
    //  qDebug()<<query.lastError()



}


void FingerSign::CheckDuplicateCardNo(QString Cardno,QString id ){
    Cardno.remove(QRegExp("[\n\t\r\a\d]"));
    QSqlQuery query2; QString TempCard=""; QString TempId="";
    query2.prepare("SELECT * From Person WHERE CardNo= :CardNo ;");
    query2.bindValue(":CardNo", Cardno);
    qDebug()<<Cardno;
    if (query2.exec()){   while(query2.next()){ TempCard=query2.value(2).toString();}}
    query2.prepare("SELECT * From Person WHERE id= :id ;");
    query2.bindValue(":id", id);
    if (query2.exec()){   while(query2.next()){ TempId=query2.value(1).toString();}}


    if(TempCard!=""){ ERR_ChekDuplicateCardNo=" ";    emit ChangedCardNoDup(); ERR_ChekDuplicateCardNo="card";    emit ChangedCardNoDup();   qDebug()<<"Result of Check Duplicae CardNo is:"<<ERR_ChekDuplicateCardNo;   }
    if(TempCard==""){ERR_ChekDuplicateCardNo=" ";    emit ChangedCardNoDup(); ERR_ChekDuplicateCardNo="no";    emit ChangedCardNoDup();   qDebug()<<"Result of Check Duplicae CardNo is:"<< ERR_ChekDuplicateCardNo;  }
    if(TempId!=""){ERR_ChekDuplicateCardNo="";    emit ChangedCardNoDup(); ERR_ChekDuplicateCardNo="id";    emit ChangedCardNoDup();   qDebug()<<"Result of Check Duplicae Id is:"<<ERR_ChekDuplicateCardNo;   }


}

void FingerSign::Delete_Unwanted_Finger(){
    qDebug()<<"Delete Signed Finger (Incomplete Sign)";
    Dele[0]=0x55; Dele[1]=0xaa; Dele[2]=0x00; Dele[3]=0x00; Dele[4]=0x44; Dele[5]=0x00; Dele[6]=0x04; Dele[7]=0x00;
    Dele[8]=Re_GEmptyId[10];    Dele[9]=Re_GEmptyId[11];
    Dele[10]=Re_GEmptyId[10];    Dele[11]=Re_GEmptyId[11];
    int i;
    for(i=12;i<=23;i++)
        Dele[i]=0x00;
    int xo=0x000;
    for (int i=0;i<=23 ;i++)
        xo+=Dele[i] ;
    Dele[24]=xo & 0xff;
    Dele[25]=xo >> 8;
    Serial32->write(Dele,26);
    Serial32->waitForBytesWritten(10000);
    Serial32->waitForReadyRead(10000);
    Re_Dele=Serial32->readAll();
    qDebug()<<Re_Dele.toHex();


}

void FingerSign::Reset_CardnoChecker(){
    ERR_ChekDuplicateCardNo="";
    emit ChangedCardNoDup();
}
QString FingerSign::Remover(QString no)
{    }
char FingerSign::E_FingerIdL(){
    return ERR_FingerIdL;}
char FingerSign::E_FingerIdH(){
    return ERR_FingerIdH;}
QString FingerSign::E_DupRFID()
{return ERR_DupRFID; }

QString FingerSign::E_Read_Id()
{ return ERR_ID; }


QString FingerSign::E_Read_Generate1()
{ return ERR_Generate1; }

QString FingerSign::E_Read_Generate2()
{ return ERR_Generate2; }

QString FingerSign::E_Read_Generate3()
{ return ERR_Generate3; }


QString FingerSign::E_Read_Image1()
{ return ERR_Image1; }
QString FingerSign::E_Read_Image2()
{ return ERR_Image2; }
QString FingerSign::E_Read_Image3()
{ return ERR_Image3; }

QString FingerSign::E_Read_Merge()
{ return ERR_MERGE; }

QString FingerSign::E_Read_Store()
{ return ERR_STORE; }


QString FingerSign::E_RFID()
{ return ERR_RFID; }


