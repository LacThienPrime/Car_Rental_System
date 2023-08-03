#include "databaseworker.h"

DatabaseWorker::DatabaseWorker(QObject *parent) : QObject(parent)
{
    sqlModel = new QSqlQueryModel();
}

void DatabaseWorker::connectData()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }

    database.setHostName("localhost");
    database.setUserName("Root");
    database.setPassword("");
    database.setDatabaseName("C:/Users/Rome/Documents/CarRentSystem/usersData.db");

    if (database.open())
    {
        emit dataFetched(sqlModel);
    }
    else
    {
        emit dataFetched(nullptr);
    }
}

void DatabaseWorker::fetchData()
{
    if (database.isOpen())
    {
        sqlModel->setQuery("SELECT ID, carModel, colour FROM vehicles WHERE availability = 0");
        emit dataFetched(sqlModel);
    }
}
