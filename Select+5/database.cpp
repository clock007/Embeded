#include "database.h"
#include <QImage>
#include <QPixmap>
#include <QtWidgets>
#include <QFile>
#include <cstdlib>
#include <fstream>

using namespace std;


DataBase::DataBase(QObject *parent) : QObject(parent)
{}

DataBase::~DataBase()
{}

void DataBase::connectToDataBase()
{    if(!QFile("/home/pi/IOdb.db").exists()){
        qDebug()<<"Not Exist";
    }
    else {qDebug()<<"Exist";   this->openDataBase();}}

bool DataBase::restoreDataBase()
{   if(this->openDataBase()){
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Failed to restore the database";
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{   db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/pi/IOdb.db");
    db.open();
    if(db.isOpen()){
        qDebug()<<"opened";
    } else {
        return false;
    }
}

void DataBase::closeDataBase(){ db.close();}
bool DataBase::createTable(){ }
void DataBase::MakeTrainingSet(){  }
bool DataBase::insertIntoTable(const QString id, const QString name, const QString cardno, const QString accesstype, int fL, int fH)
{

    QByteArray byte1,byte2,byte3;

    QFile file1("/home/pi/cap1");   QFile file2("/home/pi/cap2");    QFile file3("/home/pi/cap3");

    qDebug()<<"exist="<<file1.exists();
    if(!file1.open(QIODevice::ReadOnly))
     { qDebug()<<file1.errorString();    }
    if (file1.isOpen()) qDebug()<<"----------- open file-------";
    byte1=file1.readAll();
    file1.close();
    file2.open(QIODevice::ReadOnly);
    byte2=file2.readAll();
    file2.close();
    file3.open(QIODevice::ReadOnly);
    byte3=file3.readAll();
    file3.close();
 if(db.isOpen())
     qDebug()<<"ok";
   QSqlQuery query(db);

   query.prepare("INSERT INTO Person (id, FullName, CardNo, AccessType, FingerIdL, FingerIdH, Image1, Image2, Image3, States) "
                   "VALUES (:id, :FullName, :CardNo, :AccessType, :FingerIdL, :FingerIdH, :Image1, :Image2, :Image3, :States)");

    int ab=0;
    query.bindValue(":id", id);
    query.bindValue(":FullName", name);
    query.bindValue(":CardNo", cardno);
    query.bindValue(":AccessType", accesstype);
    query.bindValue(":FingerIdL", fL);
    query.bindValue(":FingerIdH", fH);
    query.bindValue(":Image1",byte1);
    query.bindValue(":Image2",byte2);
    query.bindValue(":Image3",byte3 );
    query.bindValue(":States",ab );

    if (query.exec())
    { qDebug()<<"ok Saved";}
    else
        qDebug()<<query.lastError();}

bool DataBase::insertIntoTable2(const QString id, const QString name, const QString cardno, const QString accesstype)
{}
bool DataBase::UpdateTable(const QString id, const QString name, const QString cardno, const QString accesstype, int fL, int fH)
{   if(db.isOpen())
        qDebug()<<"ok";
    QSqlQuery query(db);
    qDebug()<<"--------------------------------  Send To UPDATE----------------------------------------------------";
   // query.prepare("UPDATE Person Set id=:id, FullName=:FullName, CardNo=:CardNo, AccessType=:AccessType, FingerIdL=:FingerIdL, FingerIdH=:FingerIdH");
    int id2=id.toInt();

    query.prepare("DELETE From Person WHERE id="+id+" ");


    if (query.exec())
    { qDebug()<<"----------------------------------- DELETE OLD REcord -----------------------------------------";}

    else
        qDebug()<<"DELETE ERROR:"<<query.lastError();
    query.prepare("INSERT INTO Person (id, FullName, CardNo, AccessType, FingerIdL, FingerIdH) "
                  "VALUES (:id, :FullName, :CardNo, :AccessType, :FingerIdL, :FingerIdH)");
    qDebug()<<"Parameter List id: "<<id2;
     qDebug()<<"Parameter List Name: "<<name;
       qDebug()<<"Parameter List CardNo: "<<cardno;
        qDebug()<<"Parameter List AccessType: "<<accesstype;
        qDebug()<<"Parameter List: FL: "<<fL;
         qDebug()<<"Parameter List: FH: "<<fH;

    query.bindValue(":id", id2);
    query.bindValue(":FullName", name);
    query.bindValue(":CardNo", cardno);
    query.bindValue(":AccessType", accesstype);
    query.bindValue(":FingerIdL", fL);
    query.bindValue(":FingerIdH", fH);

    if (query.exec())
    { qDebug()<<"--------------------------------  UPDATE --------------------------------------------------------";}
    else
        qDebug()<<query.lastError();}


bool DataBase::insertIntoTableIPSetting(const QString IP, const QString DNS, const QString GateWay, const QString NetMask){
    if(db.isOpen())
        qDebug()<<"ok";
    QSqlQuery query(db);}
bool DataBase::insertIntoTablePassword(const QString pass){
    if(db.isOpen())
        qDebug()<<"ok";
    QSqlQuery query(db);
    query.bindValue(":pass", pass);
    query.prepare("INSERT INTO Password (pass) "
                  "VALUES (:pass)");

    if (query.exec())
    { qDebug()<<"ok Saved";}
    else
        qDebug()<<query.lastError();}

bool DataBase::insertIntoTableServerSetting(const QString Address, const QString DBname, const QString User, const QString Pass, const QString Driver, const QString Ver, const QString Port)
{   if(db.isOpen())
        qDebug()<<"ok";
    QSqlQuery query(db);}

bool DataBase::removeRecord(const int id){}

void DataBase::Finger_Searcher(int finger){}


QString DataBase::remove(QString id){
    QByteArray Re_Dele;
    QByteArray Dele;
    QSqlQuery query;
    int controller=0;
    QSerialPort *Serial51=new QSerialPort;
    query.prepare("DELETE From Person WHERE id="+id+" ");
    Serial51->setPortName("/dev/ttyUSB0");
    Serial51->open(QIODevice::ReadWrite);
    Serial51->setBaudRate(115200);

    if (!Serial51->isOpen())
        if(Serial51->open(QIODevice::ReadWrite))
            controller=1;
        else if (!Serial51->open(QIODevice::ReadWrite))
            return "Cannot Open Serial Port";
    int temp=id.toInt();
    Dele[0]=0x55; Dele[1]=0xaa; Dele[2]=0x00; Dele[3]=0x00; Dele[4]=0x44; Dele[5]=0x00; Dele[6]=0x04; Dele[7]=0x00;
    Dele[8]=0x01; Dele[9]=0x00; Dele[10]=0xFF; Dele[11]=0x00;
    Dele[8]=temp & 0xff;
    Dele[9]=temp >> 8;
    Dele[10]=temp & 0xff;
    Dele[11]=temp >> 8;
    int i;
    for(i=12;i<=23;i++)
        Dele[i]=0x00;

    int xo=0x000;
    for (int i=0;i<=23 ;i++)
        xo+=Dele[i] ;
    Dele[24]=xo & 0xff;
    Dele[25]=xo >> 8;
    Serial51->write(Dele,26);
    Serial51->waitForBytesWritten(-1);
    Serial51->waitForReadyRead(4000);
    Re_Dele=Serial51->readAll();
    Serial51->close();}


void DataBase::removeAll()
{   QByteArray Re_Dele;
    QByteArray Dele;
    QSqlQuery query;
    int controller=0;
    QSerialPort *Serial51=new QSerialPort;
    query.prepare("DELETE * From Person ");
    Serial51->setPortName("/dev/ttyUSB0");
    Serial51->open(QIODevice::ReadWrite);
    Serial51->setBaudRate(9600);
    int temp=1100;

    Dele[0]=0x55; Dele[1]=0xaa; Dele[2]=0x00; Dele[3]=0x00; Dele[4]=0x44; Dele[5]=0x00; Dele[6]=0x04; Dele[7]=0x00;
    Dele[8]=0x01; Dele[9]=0x00; Dele[10]=0xFF; Dele[11]=0x00;
    Dele[8]=temp & 0xff;
    Dele[9]=temp >> 8;
    Dele[10]=temp & 0xff;
    Dele[11]=temp >> 8;
    int i;
    for(i=12;i<=23;i++)
        Dele[i]=0x00;
    int xo=0x000;
    for (int i=0;i<=23 ;i++)
        xo+=Dele[i] ;
    Dele[24]=xo & 0xff;
    Dele[25]=xo >> 8;
    Serial51->write(Dele,26);
    Serial51->waitForBytesWritten(-1);
    Serial51->waitForReadyRead(4000);
    Re_Dele=Serial51->readAll();
    Serial51->close();


}

QString DataBase::Reload_IP_Setting(){}

QString DataBase::Reload_Server_Setting(){}

QString DataBase::Reload_Password_Setting(){}

QString DataBase::E_ID()
{return ERR_ID;}

QString DataBase::E_NAME()
{return ERR_NAME;}

QString DataBase::E_CARDNO()
{return ERR_CARDNO;}

QString DataBase::E_ACCESSTYPE()
{return ERR_ACCESSTYPE;}

QString DataBase::E_FINGERIDL()
{return ERR_FINGERIDL;}

