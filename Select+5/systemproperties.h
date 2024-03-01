 #ifndef SYSTEMPROPERTIES_H
#define SYSTEMPROPERTIES_H

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
using namespace std;

class Systemproperties : public QObject , public QQuickImageProvider
{

    Q_OBJECT
    Q_PROPERTY(QString ERR_Serial42 READ E_OpenSerial42 NOTIFY ChangedSerial42)
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

    Q_PROPERTY(QString ERR_RFID READ E_RFID NOTIFY ChangedRFID)
    Q_PROPERTY(char ERR_FingerIdL READ E_FingerIdL NOTIFY ChangedFingerIdL)
    Q_PROPERTY(char ERR_FingerIdH READ E_FingerIdH NOTIFY ChangedFingerIdH)

    //Q_PROPERTY(QString ERR_DupRFID READ E_DupRFID NOTIFY ChangedDupRFID)
    Q_PROPERTY(QString ERR_EDIT_ID READ E_EDIT_ID NOTIFY ChangedEdit_ID)
    Q_PROPERTY(QString ERR_EDIT_NAME READ E_EDIT_NAME NOTIFY ChangedEdit_Name)
    Q_PROPERTY(QString ERR_EDIT_CARDNO READ E_EDIT_CARDNO NOTIFY ChangedEdit_CardNo)
    Q_PROPERTY(QString ERR_EDIT_ACCESSTYPE READ E_EDIT_CARDNO NOTIFY ChangedEdit_ACCESSTYPE)
    Q_PROPERTY(char ERR_EDIT_FINGER_IDH READ E_EDIT_FINGERIDH NOTIFY ChangedEdit_Finger_IdH)
    Q_PROPERTY(char ERR_EDIT_FINGER_IDL READ E_EDIT_FINGERIDL NOTIFY ChangedEdit_Finger_IdL)


     Q_PROPERTY(QString ERR_SAVEDPIC READ E_Read_SavedPic NOTIFY ChangedSavedPic)
   // Q_PROPERTY(int ERR_EDIT_FIDH READ E_EDIT_FIDH NOTIFY ChangedEdit_FIDH)
   // Q_PROPERTY(int ERR_EDIT_FIDL READ E_EDIT_FIDL NOTIFY ChangedEdit_FIDL)






public:
   Systemproperties(QObject *parent=nullptr);
     QImage   requestImage(const QString& id, QSize* size, const QSize& requestedsize);
    ~Systemproperties();
   // raspicam::RaspiCam_Cv Camera;
    QImage image;
    QImage result;

    CascadeClassifier faceCade_2;
    String faceCascadeName_2 = "/home/pi/faceclassifier.xml";
    Mat camFrames_2, grayFrames_2;
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
   // Q_INVOKABLE void Editor(QString,QString,QString,QString);
    Q_INVOKABLE void Detector2();
    Q_INVOKABLE void CloseSerial();
    Q_INVOKABLE QString OpenSerial();
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
    Q_INVOKABLE void Edit_Loader(QString,int);
    Q_INVOKABLE void Delete_Current_Finger();
    Q_INVOKABLE void Updater(QString,QString,QString,QString);
    Q_INVOKABLE void Delete_Captured();



    QString mydata;
    int step;
    int state;
    QSerialPort *Serial41;
    QSerialPort *Serial42;

    QByteArray TestConnection;
    QByteArray Re_TestConnection;
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
    QString ERR_Serial42;
    QString ERR_ChekDuplicateId;
    QString ERR_ChekDuplicateCardNo;
    QString ERR_SAVEDPIC;
   // QString ERR_DupRFID;

    QString ERR_RFID;
    char ERR_FingerIdL;
    char ERR_FingerIdH;

    int F_ID_L,F_ID_H;

    QString ERR_EDIT_ID;
    QString ERR_EDIT_NAME;
    QString ERR_EDIT_CARDNO;
    QString ERR_EDIT_ACCESSTYPE;
    int ERR_EDIT_ID2;
    char ERR_EDIT_FIDH;
    char ERR_EDIT_FIDL;

//------------------Edition Page Part--------------------------

//--------------------------------------------
    QString E_Read_Id();
    QString E_CheckUser(){return ERR_ChekDuplicateId;  }
    QString E_Read_Empty_Id(){return ERR_GetEmptyId;  }
    QString E_Read_Status() {return ERR_STATUS;  }
    QString E_OpenSerial42() {return ERR_Serial42; }
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
    char E_FingerIdL();
    char E_FingerIdH();
    QString E_EDIT_ID(){return ERR_EDIT_ID;  }
    QString E_EDIT_NAME(){return ERR_EDIT_NAME;  }
    QString E_EDIT_CARDNO(){return ERR_EDIT_CARDNO;   }
    QString E_EDIT_ACCESSTYPE(){ return ERR_EDIT_ACCESSTYPE;}
    char E_EDIT_FINGERIDH(){return ERR_EDIT_FIDH;}
    char E_EDIT_FINGERIDL(){return ERR_EDIT_FIDH;}
    QString E_Read_SavedPic(){return ERR_SAVEDPIC;}
    //int E_EDIT_FIDH(){return ERR_EDIT_FIDH;}
   // int E_EDIT_FIDL(){return ERR_EDIT_FIDL;}
    //QString E_DupRFID();

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
    void ChangedSerial42();
    void ChangedRFID();
    void ChangedFingerIdL();
    void ChangedFingerIdH();
    void ChangedConnectionTest();
   // void ChangedDupRFID();
    void ChangedCardNoDup();

    void ChangedEdit_ID();
    void ChangedEdit_Name();
    void ChangedEdit_ACCESSTYPE();
    void ChangedEdit_CardNo();
    void ChangedEdit_Finger_IdH();
    void ChangedEdit_Finger_IdL();

    void ChangedSavedPic();


    //void ChangedEdit_FIDH();
  //  void ChangedEdit_FIDL();



public slots:
    void readdata31();

private:

};

#endif // BACKEND_H
