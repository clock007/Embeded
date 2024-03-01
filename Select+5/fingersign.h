#ifndef FINGERSIGN_H
#define FINGERSIGN_H
#include <QObject>
#include <QString>
#include <QSerialPort>
#include <QByteArray>
#include <QTimer>
#include <QQuickImageProvider>
#include <QObject>
#include <QtSerialPort>
#include <QDebug>
#include <QQuickImageProvider>
#include <QDebug>
#include <QAbstractVideoFilter>
#include <QTemporaryFile>
#include <QMutex>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <QImage>
#include <QtGui>
#include <QtCore/QCoreApplication>
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
class FingerSign : public QObject , public QQuickImageProvider
{

    Q_OBJECT
    Q_PROPERTY(QString ERR_Serial32 READ E_OpenSerial32 NOTIFY ChangedSerial32)
    Q_PROPERTY(QString ERR_ID READ E_Read_Id NOTIFY ChangedID)
    Q_PROPERTY(QString ERR_ChekDuplicateId READ E_CheckUser NOTIFY ChangedCheckUser)
    Q_PROPERTY(QString ERR_ChekDuplicateCardNo READ E_CheckCardno NOTIFY ChangedCardNoDup)
    Q_PROPERTY(QString ERR_GetEmptyId READ E_Read_Empty_Id NOTIFY ChangedGetEmptyId)
    Q_PROPERTY(QString ERR_STATUS READ E_Read_Status NOTIFY ChangedStatus)
    Q_PROPERTY(QString ERR_Connection_Test READ E_Read_ConnectionTest NOTIFY ChangedConnectionTest)
    Q_PROPERTY(QString ERR_Image1 READ E_Read_Image1 NOTIFY ChangedImage1)
    Q_PROPERTY(QString ERR_Image2 READ E_Read_Image2 NOTIFY ChangedImage2)
    Q_PROPERTY(QString ERR_Image3 READ E_Read_Image3 NOTIFY ChangedImage3)
    Q_PROPERTY(QString ERR_Generate1 READ E_Read_Generate1 NOTIFY ChangedGenerate1)
    Q_PROPERTY(QString ERR_Generate2 READ E_Read_Generate2 NOTIFY ChangedGenerate2)
    Q_PROPERTY(QString ERR_Generate3 READ E_Read_Generate3 NOTIFY ChangedGenerate3)
    Q_PROPERTY(QString ERR_MERGE READ E_Read_Merge NOTIFY ChangedMerge)
    Q_PROPERTY(QString ERR_STORE READ E_Read_Store NOTIFY ChangedStore)

    Q_PROPERTY(QString ERR_SAVEDPIC READ E_Read_SavedPic NOTIFY ChangedSavedPic)

    Q_PROPERTY(QString ERR_RFID READ E_RFID NOTIFY ChangedRFID)
    Q_PROPERTY(char ERR_FingerIdL READ E_FingerIdL NOTIFY ChangedFingerIdL)
    Q_PROPERTY(char ERR_FingerIdH READ E_FingerIdH NOTIFY ChangedFingerIdH)

    Q_PROPERTY(QString ERR_DupRFID READ E_DupRFID NOTIFY ChangedDupRFID)
public:
   FingerSign(QObject *parent=nullptr);
     QImage   requestImage(const QString& id, QSize* size, const QSize& requestedsize);
    ~FingerSign();

    //----------------------------------------------
    raspicam::RaspiCam_Cv Camera;
    QImage image;
    QImage result;
    CascadeClassifier faceCade_1;
    String faceCascadeName_1 = "/home/pi/faceclassifier.xml";
    Mat camFrames_1, grayFrames_1;

    Mat faceROI;
    int counter=0;
    int count_of_image;
    int count_of_capture=0;
    int ReleaseCapture=0;
    vector<Rect> faces;
    //-----------------------------------------------
    long imageIndex = 0;
    int preX=0,preY=0;

    void f_Write_ID();
    void f_Write_Status();

    Q_INVOKABLE void CloseSerial();
    Q_INVOKABLE QString OpenSerial();
    Q_INVOKABLE void init_Detector();
    Q_INVOKABLE void Detector();
    Q_INVOKABLE QString SaveData(QString,QString,QString,QString);
    Q_INVOKABLE void CheckUserName();
    Q_INVOKABLE void GetEmptyId();
    Q_INVOKABLE void ConnectionTest();
    Q_INVOKABLE void GETStatus(QString);
    Q_INVOKABLE QString Remover(QString);
    Q_INVOKABLE void CheckDuplicateId(QString);
    Q_INVOKABLE void CheckDuplicateCardNo(QString,QString);
    //Q_INVOKABLE void TestPrint();
    Q_INVOKABLE void Delete_Unwanted_Finger();
    Q_INVOKABLE void Deleter();
    Q_INVOKABLE void f_RW_Image();
    Q_INVOKABLE void f_Write_Image();
    Q_INVOKABLE void f_Generate1();
    Q_INVOKABLE void f_Generate2();
    Q_INVOKABLE void f_Generate3();
    Q_INVOKABLE void f_Merge();
    Q_INVOKABLE void f_Store();
    Q_INVOKABLE void Clear();
    Q_INVOKABLE void Clear2();
    Q_INVOKABLE void Reset_CardnoChecker();

    QString mydata;
    int step;
    int state;
    QSerialPort *Serial31;
    QSerialPort *Serial32;


    QByteArray ConnTest;
    QByteArray Re_ConnTest;
    QByteArray GEmptyId;
    QByteArray Re_GEmptyId;
    QByteArray GetId;
    QByteArray Re_GetId;
    QByteArray Permitt;
    QByteArray Re_Permitt;
    QByteArray GetImage;
    QByteArray Re_GetImage;
    QByteArray Generate1;
    QByteArray Re_Generate1;
    QByteArray Generate2;
    QByteArray Re_Generate2;
    QByteArray Generate3;
    QByteArray Re_Generate3;
    QByteArray merge;
    QByteArray Re_merge;
    QByteArray Store;
    QByteArray Re_Store;
    QByteArray del;
    QByteArray Dele;
    QByteArray Re_Dele;

    QByteArray TestConnection;
    QByteArray Re_TestConnection;


    QString ERR_ID;
    QString ERR_GetEmptyId;
    QString ERR_STATUS;
    QString ERR_Connection_Test;
    QString ERR_Image1;
    QString ERR_Image2;
    QString ERR_Image3;
    QString ERR_Generate1;
    QString ERR_Generate2;
    QString ERR_Generate3;
    QString ERR_MERGE;
    QString ERR_STORE;
    QString ERR_Serial32;
    QString ERR_ChekDuplicateId;
    QString ERR_ChekDuplicateCardNo;
    QString ERR_DupRFID;

    QString ERR_SAVEDPIC;

    QString ERR_RFID;
    char ERR_FingerIdL;
    char ERR_FingerIdH;

    int F_ID_L,F_ID_H;
    QString E_Read_Id();
    QString E_CheckUser(){return ERR_ChekDuplicateId;  }
    QString E_Read_Empty_Id(){return ERR_GetEmptyId;  }
    QString E_Read_Status() {return ERR_STATUS;  }
    QString E_OpenSerial32() {return ERR_Serial32; }
    QString E_Read_ConnectionTest(){ return ERR_Connection_Test;}
    QString E_CheckCardno(){return ERR_ChekDuplicateCardNo;  }
    QString E_Read_Image1();
    QString E_Read_Image2();
    QString E_Read_Image3();
    QString E_Read_Generate1();
    QString E_Read_Generate2();
    QString E_Read_Generate3();
    QString E_Read_Merge();
    QString E_Read_Store();
    QString E_RFID();

    QString E_Read_SavedPic(){return ERR_SAVEDPIC;}

    char E_FingerIdL();
    char E_FingerIdH();
    QString E_DupRFID();

    void writedata32(QByteArray s);

    QString reader31();
    QString AssignID();
    int Checksum(QByteArray input);

    //void writedata();



signals:
    void ChangedCheckUser();
    void ChangedID();
    void ChangedGetEmptyId();
    void ChangedStatus();
    void ChangedGenerate1();
    void ChangedGenerate2();
    void ChangedGenerate3();
    void ChangedMerge();
    void ChangedStore();
    void ChangedImage1();
    void ChangedImage2();
    void ChangedImage3();
    void ChangedSerial32();
    void ChangedRFID();
    void ChangedFingerIdL();
    void ChangedFingerIdH();
    void ChangedConnectionTest();
    void ChangedDupRFID();
    void ChangedCardNoDup();

    void ChangedSavedPic();


public slots:
    void readdata31();

private:

};

#endif // BACKEND_H
