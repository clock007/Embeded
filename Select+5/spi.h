#ifndef SPI_H
#define SPI_H
#include <QObject>
#include <QString>
#include <QtMultimedia>
#include <QtMultimedia/QMediaPlayer>

class SPi : public QObject
{

    Q_OBJECT
    Q_PROPERTY( int battery READ E_Battery NOTIFY BatteryChanged)
    Q_PROPERTY( int plug READ E_Plug NOTIFY PLugChanged)
    Q_PROPERTY( QString ERR_PASSWORD READ E_Password NOTIFY PassWordChanged)
    Q_PROPERTY( QString ERR_IPADDRESS READ E_IpAddress NOTIFY IpChanged)
    Q_PROPERTY( QString ERR_DNS READ E_Dns NOTIFY DnsChanged)
    Q_PROPERTY( QString ERR_GATEWAY READ E_GateWay NOTIFY GateWayChanged)
    Q_PROPERTY( QString ERR_NETADDRESS READ E_NetAddress NOTIFY NetChanged)
public:
    QMediaPlayer *plClick;
    Q_INVOKABLE void SpiCheck();
    Q_INVOKABLE void DisplayBackLightCheck();
    Q_INVOKABLE void sysToHwclock();
    Q_INVOKABLE void hwclockToSys();
    Q_INVOKABLE void Reboot();
    Q_INVOKABLE void SetClock(QString,QString,QString,QString,QString,QString);
    //------------------- Must Delete -------------------
    Q_INVOKABLE void TurnOnDisplay();
    Q_INVOKABLE void Insert_Into_Setting_Ip(QString,QString,QString,QString);
    Q_INVOKABLE void Init_Setting_IP();
    //---------------------------------------------------
    Q_INVOKABLE void Insert_Into_Setting_Password(QString,QString);
    Q_INVOKABLE void Init_Setting_Password();
    //---------------------------------------------------
    Q_INVOKABLE void Beeper();

    int battery=0;
    int plug;
    int TurnedOff_Before=0;
    unsigned char *sp;
    explicit SPi(QObject *parent = nullptr);


    QString ERR_PASSWORD;
    QString ERR_IPADDRESS;
    QString ERR_NETADDRESS;
    QString ERR_GATEWAY;
    QString ERR_DNS;

    int E_Battery();
    int E_Plug();
    void XMLFile();
    QString E_Password();
    QString E_IpAddress();
    QString E_NetAddress();
    QString E_GateWay();
    QString E_Dns();

signals:
    void PassWordChanged();
    void IpChanged();
    void NetChanged();
    void GateWayChanged();
    void DnsChanged();
    void GPassChanged();
    void BatteryChanged();
    void PLugChanged();
};

#endif // SPI_H
