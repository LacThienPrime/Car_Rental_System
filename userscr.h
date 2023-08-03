#ifndef USERSCR_H
#define USERSCR_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <qsqlquery.h>
#include <QObject>
#include <QThread>

#include "databaseworker.h"
#include "observer.h"

namespace Ui {
class userscr;
}

class userscr : public QDialog, public Customer
{
    Q_OBJECT

public:
    explicit userscr(QWidget *parent = nullptr);
    ~userscr();

    void connectData();
    void appendData();

    QStringList getCurrentData();
    QString inputName;

    void update(QString message) override;

signals:
    void fetchDataFromDatabase();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void handleFetchedData(QSqlQueryModel *model);

private:
    Ui::userscr *ui;

    Car car;

    userscr *display1;

    QSqlQueryModel *sqlModel;
    QSqlDatabase database;

    QThread workerThread;
    DatabaseWorker *dbWorker;
};

#endif // USERSCR_H
