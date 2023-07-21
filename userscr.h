#ifndef USERSCR_H
#define USERSCR_H

#include <QDialog>
#include <QMainWindow>
#include <QPainter>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractItemModel>
#include <QString>
#include <qsqlquery.h>
#include <QLabel>

#include "mainscr.h"

namespace Ui {
class userscr;
}

class userscr : public QDialog
{
    Q_OBJECT

public:
    explicit userscr(QWidget *parent = nullptr);
    ~userscr();

    void connectData();
    void appendData();

    mainscr* ptrMainScr;

    QStringList getCurrentData();
    QString inputName;

private slots:
    void on_pushButton_clicked();

private:
    Ui::userscr *ui;
    userscr* ptrUserScr;

    QSqlQueryModel *sqlModel;
    QSqlDatabase database;
};

class ICustomer
{
public:
    virtual ~ICustomer();

    virtual void update() = 0;
};

class ICar
{
public:
    virtual ~ICar();

    virtual void notify() = 0;
    virtual void attach(ICustomer* customer) = 0;
    virtual void detach(ICustomer* customer) = 0;
};



#endif // USERSCR_H
