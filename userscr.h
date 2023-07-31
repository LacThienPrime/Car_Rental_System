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
#include <QObject>
#include <QVector>

#include "observer.h"

namespace Ui {
class userscr;
}

class userscr : public QDialog, public Observer
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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::userscr *ui;

    Subject weatherStation;

    userscr *display1;
    userscr *display2;

    QSqlQueryModel *sqlModel;
    QSqlDatabase database;
};

#endif // USERSCR_H
