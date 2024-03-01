#include "listmodel.h"
#include "database.h"

ListModel::ListModel(QObject *parent) :
    QSqlQueryModel(parent)
{   this->updateModel();}

// The method for obtaining data from the model
QVariant ListModel::data(const QModelIndex & index, int role) const {
// Define the column number, on the role of number
    int columnId = role - Qt::UserRole - 1;
// Create the index using a column ID
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);}

QHash<int, QByteArray> ListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "counter";
    roles[id] = "id";
    roles[FullName] = "FullName";
    roles[CardNo] = "CardNo";
    roles[AccessType] = "AccessType";
    roles[FingerIdL] = "FingerIdL";
    roles[FingerIdH] = "FingerIdH";
    roles[Image1] = "Image1";

    roles[Personid]="Personid";
    roles[Cardno]="Cardno";
    roles[DateTime]="DateTime";
    roles[Type]="Type";
    return roles;}

// The method updates the tables in the data model representation
void ListModel::updateModel()
{
    // The update is performed SQL-queries to the database
    this->setQuery("SELECT id, FullName,CardNo, AccessType From Person order by id ASC" );

}
void ListModel::updateModel2()
{   // The update is performed SQL-queries to the database
    this->setQuery("SELECT id, Personid, Cardno, DateTime, Type From RecordLog order by DateTime desc" );}

void ListModel::updateModel3()
{   // The update is performed SQL-queries to the database
    if (SortID==false){
        SortID=true;  this->setQuery("SELECT id, FullName,CardNo, AccessType From Person order by id ASC" );    return;}
    if (SortID==true){
        SortID=false;  this->setQuery("SELECT id, FullName,CardNo, AccessType From Person order by id desc" );  return;    }}

void ListModel::updateModel4()
{   // The update is performed SQL-queries to the database
    if(SortFullName==false){
       SortFullName=true;  this->setQuery("SELECT id, FullName,CardNo, AccessType From Person order by FullName ASC" );   return;}
    if(SortFullName==true){
       SortFullName=false;  this->setQuery("SELECT id, FullName,CardNo, AccessType From Person order by FullName desc" ); return;  }}

void ListModel::updateSearchLog(QString id2)
{  // The update is performed SQL-queries to the database
    QSqlQuery Query;
    this->setQuery("SELECT * From RecordLog WHERE id="+id2+" ");}

// Getting the id of the row in the data view model
int ListModel::getId(int row)
{    return this->data(this->index(row, 0), IdRole).toInt();}

