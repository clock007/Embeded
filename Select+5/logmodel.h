#include "listmodel.h"
#include "database.h"

ListModel::ListModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    this->updateModel();
}

// The method for obtaining data from the model
QVariant ListModel::data(const QModelIndex & index, int role) const {

    // Define the column number, on the role of number
    int columnId = role - Qt::UserRole - 1;
    // Create the index using a column ID
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ListModel::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[IdRole] = "counter";
    roles[id] = "id";
    roles[FullName] = "FullName";
    roles[CardNo] = "CardNo";
    roles[AccessType] = "AccessType";
    roles[FingerIdL] = "FingerIdL";
    roles[FingerIdH] = "FingerIdH";
    roles[Image] = "Image";
    return roles;
}

// The method updates the tables in the data model representation
void ListModel::updateModel()
{
    // The update is performed SQL-queries to the database
    this->setQuery("SELECT id, FullName,CardNo, AccessType, FingerIdL, FingerIdH, Image From Person" );

}

// Getting the id of the row in the data view model
int ListModel::getId(int row)
{
    return this->data(this->index(row, 0), IdRole).toInt();
}
