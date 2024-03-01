#ifndef VERIFY_H
#define VERIFY_H
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
#include <QSqlQuery>

#include <raspicam/raspicam.h>
//#include <raspicam/raspicam_cv.h>
//#include <QAbstractVideoFilter>
#include <QTemporaryFile>
#include <QMutex>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <QImage>
#include <QtGui>
//#include <raspicam/raspicam.h>

#include <QtCore/QCoreApplication>
#include <QtMultimedia>
#include <QtMultimedia/QMediaPlayer>

using namespace std;


class Verify : public QObject, public QQuickImageProvider
{
   Q_OBJECT
   Q_PROPERTY(QString VERR_READRFID READ VE_READRFID NOTIFY VChangedRFID)
   Q_PROPERTY(int VERR_READFINGER READ VE_READFINGER NOTIFY VChangedFINGER)
   Q_PROPERTY(int ERR_STREAM1 READ E_STREAM1 NOTIFY Stream1Changed)
   Q_PROPERTY(int ERR_STREAM2 READ E_STREAM2 NOTIFY Stream2Changed)

   Q_PROPERTY(QString ERR_SAVEDPIC1 READ E_SAVEDPIC1 NOTIFY SavedPic1Changed)
   Q_PROPERTY(int ERR_ID READ E_ID NOTIFY IDChanged())
   Q_PROPERTY(QString ERR_NAME READ E_NAME NOTIFY NAMEChanged)
   Q_PROPERTY(int ERR_CARDNO READ E_CARDNO NOTIFY CARDNOChanged)
   Q_PROPERTY(QString ERR_SECURITY READ E_SECURITY NOTIFY SECURITYChanged)
   Q_PROPERTY(int ERR_PRGOGRESS READ E_PROGRESS NOTIFY ProgressChanged)
   Q_PROPERTY(int ERR_ACCURACY READ E_ACCURACY NOTIFY ACCURACYChanged)
   Q_PROPERTY(int VALUE READ E_VALUE NOTIFY VALUEChanged)
 //  Q_PROPERTY(QString ERR_SHAKED READ E_SHAKED NOTIFY ShakedChanged())
   Q_PROPERTY(QString ERR_STATE READ E_STATE NOTIFY StateChanged)



   Q_PROPERTY(QString ERR_EFood READ E_EFood NOTIFY EFoodChanged)
   Q_PROPERTY(QString ERR_FoodName1 READ E_FoodName1 NOTIFY FoodName1Changed)
   Q_PROPERTY(QString ERR_FoodCount1 READ E_FoodCount1 NOTIFY FoodCount1Changed)
   Q_PROPERTY(QString ERR_FoodName2 READ E_FoodName2 NOTIFY FoodName2Changed)
   Q_PROPERTY(QString ERR_FoodCount2 READ E_FoodCount2 NOTIFY FoodCount2Changed)
   Q_PROPERTY(QString ERR_FoodName3 READ E_FoodName3 NOTIFY FoodName3Changed)
   Q_PROPERTY(QString ERR_FoodCount3 READ E_FoodCount3 NOTIFY FoodCount3Changed)


   Q_PROPERTY(QString ERR_ServerAddress READ E_ServerAddress NOTIFY ServerAddressChanged)
   Q_PROPERTY(QString ERR_DBName READ E_DBName NOTIFY DBNameChanged)
   Q_PROPERTY(QString ERR_UID READ E_UID NOTIFY UIDChanged)
   Q_PROPERTY(QString ERR_DBPassword READ E_DBPassword NOTIFY DBPasswordChanged)
   Q_PROPERTY(QString ERR_TDS_Version READ E_TDS_Version NOTIFY TDSVersionChanged)
   Q_PROPERTY(QString ERR_Port READ E_Port NOTIFY PortChanged)

   Q_PROPERTY(bool ERR_UP_DIALOG READ E_ReadUpDialog NOTIFY ChangedUpDialog)
   Q_PROPERTY(bool ERR_UP_BUSY READ E_ReadUpBusy NOTIFY ChangedUpBusy)
   Q_PROPERTY(bool ERR_DOWN_BUSY READ E_ReadDownBusy NOTIFY ChangedDownBusy)

   Q_PROPERTY( int ERR_SOUND READ E_Sound NOTIFY SoundChanged)
   Q_PROPERTY( int ERR_DISPOFF READ E_DispOff NOTIFY DisplayChanged)
   Q_PROPERTY( int ERR_DELAY READ E_Delay NOTIFY DelayChanged)

   Q_PROPERTY( QString ERR_CHECKFINGER READ E_CheckFinger NOTIFY CheckFingerChanged)
   Q_PROPERTY( QString ERR_CHECKRFID  READ E_CheckRFID NOTIFY CheckRFIDChanged)
   Q_PROPERTY( QString ERR_CHECKPRINTER READ E_CheckPrinter NOTIFY CheckPrinterChanged)

   Q_PROPERTY( QString ERR_FAILED_USB READ E_Failed_USB NOTIFY ChangedUSB)




public:
     explicit Verify(QObject *parent=nullptr);
    ~Verify();
    //void fetcher();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedsize);

    //QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);
    QMediaPlayer *plNoPerson;
    QMediaPlayer *plOk;
    QMediaPlayer *plFishTakenBefor3;
    QMediaPlayer *plNoReservedFood4;
    QMediaPlayer *plNoMachineinRest5;
    QMediaPlayer *plNoRestaurantMember6;
    QMediaPlayer *plNoMealDefined7;
    QMediaPlayer *plNoMealBegined8;
    QMediaPlayer *plNoConnectToDataBase9;
    QMediaPlayer *plNoInternet10;

    QImage result;


    int counter=0;
    int counter2=0;




    QImage E_image();
    long imageIndex = 0;
    int preX=0,preY=0;

    Q_INVOKABLE void Detectore();
    Q_INVOKABLE void Check_SerialPorts();
    Q_INVOKABLE void UpFinger();
    Q_INVOKABLE void DownFinger();
    Q_INVOKABLE void WriteController();
    Q_INVOKABLE void OpenAllSerial();
    Q_INVOKABLE void CloseAllSerial();
    Q_INVOKABLE void ClearImage();
   // Q_INVOKABLE void Close_InputSerials();

    Q_INVOKABLE void inserter();

    Q_INVOKABLE void ClearALL();
    Q_INVOKABLE void PrintLetter(QString name);
    Q_INVOKABLE void PrintNumber(QString number);
    Q_INVOKABLE void DeleteAll();
    Q_INVOKABLE QString Deleteone(QString);

   // Q_INVOKABLE QString SaveSetting(int,int,int);
    //Q_INVOKABLE void UpdateModel2(QString);

    Q_INVOKABLE QString Insert_Into_ServerSetting(QString,QString,QString,QString,QString,QString);
    Q_INVOKABLE void Initialize_ServerSetting();

    Q_INVOKABLE void Insert_Into_Setting(int,int,int);
    Q_INVOKABLE void Init_Setting();


    Q_INVOKABLE void VolumController(int);
    Q_INVOKABLE void TestPrint();

    Q_INVOKABLE void Get_Current_IP();




    QString ERR_ServerAddress;
    QString ERR_DBName;
    QString ERR_UID;
    QString ERR_DBPassword;
    QString ERR_TDS_Version;
    QString ERR_Port;

    //Q_INVOKABLE void Deleteone();
    void FaceVerify();
    void PrintUnit(QStringList,int,int,int);
    QSerialPort *Serial11;
    QSerialPort *Serial12;
    QSerialPort *Serial13;


    QString VERR_READRFID;
    int VERR_READFINGER;
    int SelectDevice;
    QByteArray VERR_PRINTER;

     int ERR_STREAM1=0;
     int ERR_STREAM2=0;
     int ERR_PROGRESS;
     int ERR_ACCURACY;

     int Type;
     QString ERR_NAME;
     int ERR_ID;
     int ERR_CARDNO;
     QString ERR_SECURITY;

     QString ERR_SAVEDPIC1;
     QString ERR_SHAKED;
     QString ERR_STATE;
     int states;


     QString ERR_EFood_BUSY;

     QString ERR_EFood;
     QString ERR_FoodName1;
     QString ERR_FoodName2;
     QString ERR_FoodName3;
     QString ERR_FoodCount1;
     QString ERR_FoodCount2;
     QString ERR_FoodCount3;

    QString ERR_CHECKFINGER;
    QString ERR_CHECKRFID;
    QString ERR_CHECKPRINTER;

    QString ERR_FAILED_USB;


     int ERR_VOL;
  //   int ERR_SCREENSAVER;

     bool ERR_UP_DIALOG;
     bool ERR_UP_BUSY;
     bool ERR_DOWN_BUSY;


     int ERR_SOUND;
     int ERR_DISPOFF=25;
     int ERR_DELAY;

    //QString ERR_READRF---------------------------------------------------------;
    int E_STREAM1();
    int E_STREAM2();
    int E_PROGRESS();
    int E_ACCURACY();

    QString E_NAME();
    int E_ID();
    int E_CARDNO();
    QString E_SECURITY();

    int E_VALUE();
    QString VE_READRFID();
    int VE_READFINGER();

    QString E_SAVEDPIC1();
   // QString E_SHAKED();
    QString E_STATE();


    //int E_PowerSaver();
    //int E_OffKey();
    QString E_EFood();
    QString E_FoodName1();
    QString E_FoodName2();
    QString E_FoodName3();
    QString E_FoodCount1();
    QString E_FoodCount2();
    QString E_FoodCount3();

    QString E_ServerAddress();
    QString E_DBName();
    QString E_UID();
    QString E_DBPassword();
    QString E_TDS_Version();
    QString E_Port();

    int E_Sound();
    int E_DispOff();
    int E_Delay();

    bool E_ReadUpBusy();
    bool E_ReadUpDialog();
    bool E_ReadDownBusy();

    QString E_CheckFinger(){ return ERR_CHECKFINGER;}
    QString E_CheckRFID(){return ERR_CHECKRFID;}
    QString E_CheckPrinter(){return ERR_CHECKPRINTER; }
    QString E_Failed_USB(){return  ERR_FAILED_USB; }
//----------------------------------------------------------------

    int Controller;
    int s;
    int finger;
    int Value;


    int count_of_image;
    int count_of_imageture=0;
    int Releaseimageture=0;

    QFileSystemWatcher watcher;
    QByteArray RFID;
    QByteArray Dele;
    QByteArray Re_Dele;
    QByteArray Get;
    QByteArray Re_Get;
    QByteArray Generation;
    QByteArray Re_Generation;
    QByteArray Search;
    QByteArray Re_Search;
    QByteArray cpyFinger1;
    QByteArray Re_cpyFinger1;
    QByteArray cpyFinger2;
    QByteArray Re_cpyFinger2;
    QByteArray DFinger;
    QByteArray Re_DFinger;
    QByteArray FingerPack;

    QByteArray TestConnection;
    QByteArray Re_TestConnection;

    void FingerStep1();
    void FingerStep2();
    void FingerStep3();
    void FingerStep4(char,char);
    void print(QString);
    int CheckSum(QByteArray);
    int CheckSum2(QByteArray);





public slots:
    void readdata12();
    void readdata11();
    void OpenSerialports();
    void CloseSerialports();


signals:

    void VChangedRFID();
    void VChangedFINGER();
    void IDChanged();
    void NAMEChanged();
    void CARDNOChanged();
    void SECURITYChanged();
    void Stream1Changed();
    void Stream2Changed();
    void SavedPic1Changed();
    void VALUEChanged();
    void ProgressChanged();
    void ACCURACYChanged();
   // void ShakedChanged();
    void StateChanged();
    void EFoodChanged();
    void FoodName1Changed();
    void FoodCount1Changed();
    void FoodName2Changed();
    void FoodCount2Changed();
    void FoodName3Changed();
    void FoodCount3Changed();
   // void VolChanged();
    //void ScreenChanged();
    void DisplayChanged();
    void SoundChanged();
    void DelayChanged();
    void ChangedUpDialog();
    void ChangedUpBusy();
    void ChangedDownBusy();

    void ServerAddressChanged();
    void DBNameChanged();
    void UIDChanged();
    void DBPasswordChanged();
    void TDSVersionChanged();
    void PortChanged();
   // void DPassChanged();
   // void PowerSaverChanged();
    //void OffKeyChanged();
    //void CARDNOChanged();
    void CheckFingerChanged();
    void CheckRFIDChanged();
    void CheckPrinterChanged();
    void ChangedUSB();

};

#endif // VERIFY_H
