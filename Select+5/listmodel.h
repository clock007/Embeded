#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QSqlQueryModel>

class ListModel : public QSqlQueryModel
{
    Q_OBJECT
public:

    Q_INVOKABLE void updateModel();
    Q_INVOKABLE void updateModel2();
    Q_INVOKABLE void updateSearchLog(QString);
    Q_INVOKABLE void updateModel3();
    Q_INVOKABLE void updateModel4();
    bool SortFullName=false;
    bool SortID=false;


    enum Roles {
        IdRole = Qt::UserRole,      // id1
        id,                      // id
        FullName,                      // Last name
        CardNo,                      // id
        AccessType,                      // Last name
        FingerIdL,                      // id
        FingerIdH,                      // Last name
        Image1,
        Image2,
        Image3,
        Personid,
        Cardno,
        DateTime,
        Type

        // Nik name
    };

    explicit ListModel(QObject *parent = 0);

    // Override the method that will return the data
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:

    QHash<int, QByteArray> roleNames() const;

signals:

public slots:

    int getId(int row);
};

#endif // LISTMODEL_H
