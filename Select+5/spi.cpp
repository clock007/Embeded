#include "spi.h"
//#include <wiringPi.h>
//#include <wiringPiSPI.h>
#include <QObject>
#include <QDebug>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <QObject>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include<QProcess>
#include <iostream>
#include <fstream>
#include<QDateTime>
#include <QFile>
//#include <raspicam/raspicam.h>
//#include <raspicam/raspicam_cv.h>
#include <unistd.h> // for usleep
#include <QSqlQuery>
#include <QProcess>
#include <QFile>
#include <QDomElement>
extern int PowerSaverCounter;
//ERROR DISPOFF is a Limitation for PowerSaverCounter
extern int PowerSaverCounter_Lim;
//int PowerSaverLim=40;
//int OffKey;
#define INTERUPT 5
#define ONSOUND 8
#define ONRFIDFINGER 17
#define ONPRINTER 12
#define BACKLIGH 18
#define DISPLAYVOLTAGE 23
#define SELECT 24
#define FAN 26


SPi::SPi(QObject *parent) : QObject(parent)
{   plClick=new QMediaPlayer;
    plClick->setMedia(QUrl::fromLocalFile("/home/pi/S1/beep.wav"));
    plClick->setVolume(80);
    plClick->play();
    qDebug()<<"Initialize  SPI......";
    //Initialize inital Parameter Setting
    Init_Setting_Password();
    Init_Setting_IP();

    //initialize Plug
    plug=0;
    emit PLugChanged();
    wiringPiSetupGpio();


    pinMode(BACKLIGH,OUTPUT);
    digitalWrite(BACKLIGH,LOW);
    pinMode(21,INPUT);
    digitalWrite(21,HIGH);
    pinMode(23,OUTPUT);
    digitalWrite(23,HIGH);

    //-----------------------  GPIO BACK LIGHT LCD  TURN OFF   (0 ON) -----------------------------------------
    digitalWrite(18,LOW);
    //----------------------------     GPIO LCD (1 ON ) ---------------------------------------------------------
    int chan=0;
    int speed=100000;
    int result;
    if (wiringPiSPISetup (0, 100000) < 0)
        fprintf (stderr, "Unable to open SPI device 0: %s\n", strerror (errno)) ;

    //**************************************  Start Service ***************************************************





}

void SPi::SpiCheck()
{
    qDebug()<<"Spi Checking";
    int i,battery1,battery2;
    int ce=0;
    char temp1,temp2,temp3;

    uint8_t writeCommand[7];
    uint8_t readCommand[70];
    writeCommand[0] = 0x7b;
    writeCommand[1] = 0x53;
    writeCommand[2] = 0x54;
    writeCommand[3] = 0x54;
    writeCommand[4] = 0x7d;
    writeCommand[5] = 0x0d;
    writeCommand[6] = 0x0a;

    wiringPiSPIDataRW (ce, writeCommand, 7);


    usleep(100000);

    for(i = 0; i < 70; i++) {      readCommand[i] = 0xff;}
    wiringPiSPIDataRW(0, readCommand, 70);

    for(i=0;i<=59;i++)
    {
        if (char(readCommand[i])=='T'&& char(readCommand[i+1])=='1')
        { temp1=char(readCommand[i+5]);  temp2=char(readCommand[i+7]);  temp3=char(readCommand[i+8]);
            battery1=(temp1-48)*100;     battery1=(temp2-48)*10+battery1;   battery1=(temp3-48)+battery1;   }

        if (char(readCommand[i])=='T'&& char(readCommand[i+1])=='2')
        { temp1=char(readCommand[i+5]);  temp2=char(readCommand[i+7]);  temp3=char(readCommand[i+8]);
            battery2=(temp1-48)*100;     battery2=(temp2-48)*10+battery2;   battery2=(temp3-48)+battery2;
            battery=battery1+battery2;}
        printf ("Buffer at %d: %c \n", i, readCommand[i]);
        if (char(readCommand[i])=='D'&& char(readCommand[i+1])=='P')
            plug=int(readCommand[i+5]);    }

    //usleep(20);
    for(i = 0; i < 70; i++) {
        printf ("Buffer at %d: %c \n", i, readCommand[i]) ;      }

    qDebug()<<"battery1="<<battery1<<"battery2="<<battery2<<"battery="<<battery;
    qDebug()<<plug;
    battery=battery1+battery2;
    if(plug==49) battery=battery-70;
    //some times it take negative or small (50% in time)
    if (battery<600) battery=-801;
    //if has acceptable value send it
    if (70 < battery)   emit BatteryChanged();
    emit PLugChanged();
    plug=1;

}

void SPi::DisplayBackLightCheck()
{   qDebug()<<PowerSaverCounter;
     qDebug()<<PowerSaverCounter_Lim;

    PowerSaverCounter=PowerSaverCounter+1;
    if(PowerSaverCounter > 11000){PowerSaverCounter=500; qDebug()<<"Power SAver Value:"<<PowerSaverCounter;  }

    //---------------------------------------  Display and Voltage Controller ------------------------------
    //---------------- Turn Off BackLight ------------------------------------------------------------------
    if (PowerSaverCounter> PowerSaverCounter_Lim ) {
        qDebug()<<"Display Voltage off";
        digitalWrite(BACKLIGH,HIGH);
        if ( 10000 < PowerSaverCounter && TurnedOff_Before==0 ) {
            digitalWrite(DISPLAYVOLTAGE,LOW);  TurnedOff_Before=1; }
        //---------- Turn Off Voltage --

    }
    //--------------------------- Turn on BackLight --------------------------------------------------------
   // if (PowerSaverCounter < PowerSaverCounter_Lim ) {
      //  digitalWrite(BACKLIGH,LOW);
      //  if (TurnedOff_Before==1) {
        //    pinMode(BACKLIGH,OUTPUT);  digitalWrite(DISPLAYVOLTAGE,HIGH);  TurnedOff_Before=0; }
       //  }


}
void SPi::SetClock(QString year, QString month, QString day, QString hour, QString minute, QString secound){
    QProcess *p1=new QProcess(this);
    p1->start("sudo date --set \""+year+"-"+month+"-"+day+" "+hour+":"+minute+":"+secound+"\"");
    p1->waitForFinished();
    QString dateTime=p1->readAllStandardOutput();
    qDebug()<<dateTime;
    p1->start("sudo hwclock -w");
    p1->waitForFinished();
    p1->start("sudo hwclock -r");
    p1->waitForFinished();}

void SPi::sysToHwclock(){      }

void SPi::hwclockToSys()
{   QProcess *p1=new QProcess(this);
    p1->start("sudo hwclock -r");
    p1->waitForFinished();
    QString dateTime=p1->readAllStandardOutput();
    QString dateTimeString ("sudo date -s \""+dateTime+"\"");
    p1->start(dateTimeString);
    p1->waitForFinished(200);
    QString result=p1->readAllStandardOutput();
    qDebug()<<"Resule1:  "<<result;}

void SPi::Reboot()
{   QProcess reb;
    QString  program= "sudo reboot";
    reb.start(program);    reb.waitForFinished(1000);}

void SPi::TurnOnDisplay()
{  PowerSaverCounter=0;
    pinMode(BACKLIGH,OUTPUT);
    digitalWrite(BACKLIGH,LOW);
     digitalWrite(DISPLAYVOLTAGE,HIGH);
    qDebug()<<"--- Display Turned On ---";


}


void SPi::XMLFile(){
    QDomDocument document;
    // Making the root element
    QDomElement root = document.createElement("Dorms");
    // Adding the root element to the docuemnt
    document.appendChild(root);
    // Writing to a file

    //--------------------  if Existdelete File --------------------
    QFile file2("/home/pi/ManiFest.xml");
    if(file2.exists()){
        file2.remove();}

    qDebug()<<"----------- Creating XML File -----------------------";
    QFile file("/home/pi/ManiFest.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Open the file for writing failed";   }
    else  {qDebug() << "Writing is done"; }

    QDomElement dorm = document.createElement("Edition_Properties");
    dorm.setAttribute("Name", "Attendance " );
    dorm.setAttribute("Ver", "1.4.30");
    root.appendChild(dorm);
    QDomElement dorm2 = document.createElement("Producter");
    dorm2.setAttribute("Preseneted_Date", "1399/3/30" );
    dorm2.setAttribute("Producter", "Azarakhsh_Corporation" );
    root.appendChild(dorm2);
    //QDomElement dorm3 = document.createElement("Date");
    //dorm.setAttribute("Date","");
    //root.appendChild(dorm3);
    QTextStream stream(&file);
    stream << document.toString();

    file.close();
   }

//----------------------------------------------------------------------


void SPi::Insert_Into_Setting_Ip(QString ip, QString DNS, QString GateWay, QString NetMask)
{   qDebug()<<"Insert Into IPAddress";
    QSqlQuery query;
    query.prepare("Delete From Network ;"); query.exec();
    // Re Insert Into Network
    query.prepare("INSERT INTO Network (IPAddress, DNS, GateWay, NetMask) "
                  "VALUES (:IPAddress, :DNS, :GateWay, :NetMask)");
    query.bindValue(":IPAddress",ip );   query.bindValue(":DNS", DNS );  query.bindValue(":GateWay", GateWay);  query.bindValue(":NetMask", NetMask);
    query.bindValue(":Temp1", "1");  query.bindValue(":Temp2", "2");
    if(query.exec())
    {while (query.next()) {
            qDebug()<<"Inserted Successfully";}  }
    else { qDebug()<<"not done";  }
    Init_Setting_IP();}
void SPi::Init_Setting_IP() {
    qDebug()<<"Initialize Ip Setting According To DataBase";
    QSqlQuery query;
    query.prepare("Select * From Network ;");
    if(query.exec()) { while(query.next()){qDebug()<<"Retrieve IP Address";
            ERR_IPADDRESS=query.value(0).toString();
            ERR_DNS=query.value(1).toString();
            ERR_GATEWAY=query.value(2).toString();
            ERR_NETADDRESS=query.value(3).toString(); }}
    QProcess p1;   QString answer; QString cmd;
    cmd="sudo printf \"+++++++----+\" >> /etc/dhcpcd.conf";
    QString dataText="\nhostname\nclientid\npersistent\noption rapid_commit\noption domain_name_servers, domain_name, domain_search, host_name\noption classless_static_routes\noption ntp_servers\noption interface_mtu\nrequire dhcp_server_identifier\nslaac private\ninterface eth0\ninform "+ERR_IPADDRESS+"\nstatic routers="+ERR_GATEWAY+"\nstatic domain_name_servers="+ERR_DNS;
    QFile newData("/etc/dhcpcd.conf");
    if(newData.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&newData);
        out << dataText; }
    newData.close();
    p1.start(cmd);
    p1.waitForFinished(3000);
    answer=p1.readAllStandardOutput();qDebug()<<cmd;    p1.start(cmd); p1.waitForFinished(3000);     answer=p1.readAllStandardOutput();
    qDebug()<<"Change GateWay Address: " <<answer;
    cmd="sudo ifconfig eth0 down ";
    p1.start(cmd);
    p1.waitForFinished(3000);
    delay(200);
    cmd="sudo ifconfig eth0 up ";
    p1.start(cmd);
    p1.waitForFinished(3000);
    delay(200);
    //--------------------------------------------------------------------------------
    emit IpChanged();
    emit NetChanged();
    emit GateWayChanged();
    emit DnsChanged();}
//----------------------------------------------------------------------
void SPi::Insert_Into_Setting_Password(QString OldPass, QString NewPass){
    qDebug()<<"Insert Into Password DataBase";
    QString TempPass;  QSqlQuery query;
    // Reload All
    query.prepare("Select * From Setting ");
    if(query.exec()) { while (query.next()) {    TempPass=query.value(3).toString();
            qDebug()<<"Retrieve Existed Pass: ";   qDebug()<<TempPass;    }}
//-------------------------------------------- If Condtion is TRUE   ---------------------------------------------
    if (OldPass==TempPass){
        QSqlQuery query;
        query.prepare("insert into Setting(DefaultPassword) SELECT :pss WHERE not exists (select * from Setting) ;");
        query.bindValue(":pass",NewPass );
        if(query.exec()) { qDebug()<<"SuccessFully Inserted"; }
        query.prepare("UPDATE Setting Set DefaultPassword=:pass ");
        query.bindValue(":pass",NewPass );
        if(query.exec()) { qDebug()<<"SuccessFully Updated"; }
        Init_Setting_Password();
    } // End of If
}

void SPi::Init_Setting_Password()
{   QSqlQuery query;   query.prepare("Select * From Setting");
    query.bindValue(":rowid", 1);
    //query.first();
    if(query.exec()) {
        while (query.next()) {
            qDebug()<<"Initialize Pass According to Data Set";
            ERR_PASSWORD=query.value(3).toString();        }
    }
    emit PassWordChanged();
    qDebug()<<" End of All";}

void SPi::Beeper(){
    plClick->play();}

int SPi::E_Battery()
{ if (750 <= battery <=800)
    { qDebug()<<battery;        return battery;}}

int SPi::E_Plug()
{ return plug;  }

//------------------------------------
QString SPi::E_Password(){ return ERR_PASSWORD;}

//------------------------------------
QString SPi::E_IpAddress(){
    return ERR_IPADDRESS;}
QString SPi::E_NetAddress(){
    return ERR_NETADDRESS;}
QString SPi::E_GateWay(){
    return ERR_GATEWAY;}
QString SPi::E_Dns(){
    return ERR_DNS;}
//-------------------------------------

