#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include <QString>
#include <QSerialPort>
#include <QByteArray>

class BackEnd : public QObject
{
    Q_OBJECT
    //‫‪Q_PROPERTY(QString‬‬ ‫‪name‬‬)‬‬
    Q_PROPERTY(QString GetRFIF READ reader1 NOTIFY Changed11)
    Q_PROPERTY(QString SignRFID READ reader3 NOTIFY Changed31)

public:
    explicit BackEnd(QObject *parent = nullptr);
    QSerialPort *serial11;
    QSerialPort *serial31;
    Q_INVOKABLE void closeserial11();
    Q_INVOKABLE void closeserial31();
    Q_INVOKABLE void openserial11();
    Q_INVOKABLE void openserial31();

    void openserialport11();
    void openserialport31();
    void writedata11(QByteArray s);
    void writedata31(QByteArray s);
    //void closeserial();
    QString reader11();
    QString reader31();
    //void writedata();
    QString mydata;


signals:
    void Changed11();
    void Changed31();

public slots:
    QString readdata11();
    QString readdata31();
private:

};

#endif // BACKEND_H
