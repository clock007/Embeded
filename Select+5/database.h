#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QSerialPort>
#include <QString>

//#define DATABASE_HOSTNAME   "NameDataBase"
#define DATABASE_NAME       "IOdb.db"

//#define TABLE                   "Person"
//#define TABLE_FNAME             "FisrtName"
//#define TABLE_SNAME             "SurName"
//#define TABLE_NIK               "Nik"

class DataBase : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString ERR_RFID READ E_RFID NOTIFY RFIDChanged())
    //Q_PROPERTY(int ERR_FINGER READ E_FINGER NOTIFY FingerChanged())
    Q_PROPERTY(QString ERR_ID READ E_ID NOTIFY IDChanged())
    Q_PROPERTY(QString ERR_NAME READ E_NAME NOTIFY NAMEChanged())
    Q_PROPERTY(QString ERR_CARDNO READ E_CARDNO NOTIFY CARDNOChanged())
    Q_PROPERTY(QString ERR_ACCESSTYPE READ E_ACCESSTYPE NOTIFY ACCESSTYPEChanged())
    Q_PROPERTY(QString ERR_FINGERIDL READ E_FINGERIDL NOTIFY FINGERIDLChanged())


public:
    Q_INVOKABLE void Finger_Searcher(int);
    Q_INVOKABLE  bool insertIntoTable(const QString id, const QString name, const QString cardno, const QString accesstype,int, int);
    Q_INVOKABLE  bool UpdateTable(const QString id, const QString name, const QString cardno, const QString accesstype,int, int);
    Q_INVOKABLE  bool insertIntoTable2(const QString id, const QString name, const QString cardno, const QString accesstype);
    Q_INVOKABLE  bool insertIntoTablePassword(const QString pass);
    Q_INVOKABLE  bool insertIntoTableServerSetting(const QString Address, const QString DBname, const QString User, const QString Pass, const QString Driver, const QString Ver, const QString Port );
    Q_INVOKABLE  bool insertIntoTableIPSetting(const QString IP, const QString DNS, const QString GateWay, const QString NetMask);
    Q_INVOKABLE  QString remove(const QString id);
    Q_INVOKABLE  void removeAll();
    Q_INVOKABLE void MakeTrainingSet();

    Q_INVOKABLE QString Reload_Server_Setting();
    Q_INVOKABLE QString Reload_Password_Setting();
    Q_INVOKABLE QString Reload_IP_Setting();

    QString ERR_ID;
    QString ERR_NAME;
    QString ERR_CARDNO;
    QString ERR_ACCESSTYPE;
    QString ERR_FINGERIDL;


   // int E_FINGER();
    QString E_ID();
    QString E_NAME();
    QString E_CARDNO();
    QString E_ACCESSTYPE();
    QString E_FINGERIDL();





    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    void connectToDataBase();

private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();

public slots:
   // bool inserIntoTable(const QVariantList &data);      // Adding entries to the table

    bool removeRecord(const int id); // Removing records from the table on its id
signals:

void IDChanged();
void NAMEChanged();
void CARDNOChanged();
void ACCESSTYPEChanged();
void FINGERIDLChanged();



};

#endif // DATABASE_H
