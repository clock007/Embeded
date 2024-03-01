#include "backend.h"
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
//#include <QMessageBox>
#include <QObject>
#include <QDebug>

QString mydata;
BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    serial11=new QSerialPort(this);
    serial31=new QSerialPort(this);
    connect(serial11,SIGNAL(readyRead()), this, SLOT(readdata11()));
    connect(serial11,SIGNAL(readyRead()), this, SLOT(readdata31()));
   // openserialport11();
}

void BackEnd::openserialport11()
{
    serial11->setPortName("ttyUSB0");
    serial11->setBaudRate(QSerialPort::Baud9600);
    serial11->setDataBits(QSerialPort::Data8);
    serial11->setParity(QSerialPort::NoParity);
    serial11->setStopBits(QSerialPort::OneStop);
    serial11->setFlowControl(QSerialPort::NoFlowControl);
    if (serial11->open(QIODevice::ReadWrite))
        qDebug()<< "ok";
}

void BackEnd::openserialport31()
{
    serial31->setPortName("ttyUSB0");
    serial31->setBaudRate(QSerialPort::Baud9600);
    serial31->setDataBits(QSerialPort::Data8);
    serial31->setParity(QSerialPort::NoParity);
    serial31->setStopBits(QSerialPort::OneStop);
    serial31->setFlowControl(QSerialPort::NoFlowControl);
    if (serial31->open(QIODevice::ReadWrite))
        qDebug()<< "ok";
}


QString BackEnd::readdata11()
{
    QByteArray data= serial11->readAll();


    mydata=data.toHex();
    emit Changed11();

    return mydata;


}



QString BackEnd::readdata31()
{
    QByteArray data= serial31->readAll();
    mydata=data.toHex();
    emit Changed31();
    return mydata;

}

void BackEnd::writedata11(QByteArray s)
{

//d[0]=0x01;
//serial->write(d);
emit Changed11();

}

void BackEnd::writedata31(QByteArray s)
{

//d[0]=0x01;
//serial->write(d);
emit Changed31();

}



QString BackEnd::reader11()
{

return mydata;
emit Changed11();
}

QString BackEnd::reader31()
{

return mydata;
emit Changed31();
}

void BackEnd::closeserial11()
{serial11->close();}

void BackEnd::closeserial31()
{serial31->close();}

