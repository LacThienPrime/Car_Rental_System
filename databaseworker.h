#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlDatabase>

class DatabaseWorker : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseWorker(QObject *parent = nullptr);

public slots:
    void connectData();
    void fetchData();

signals:
    void dataFetched(QSqlQueryModel *model);

private:
    QSqlDatabase database;
    QSqlQueryModel *sqlModel;
};

#endif // DATABASEWORKER_H
