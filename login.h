#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QTimer>
#include <QPainter>

#include "signup.h"
#include "mainscr.h"
#include "userscr.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void cleanLineEdit();
    void connectDatabase();
    void matchDatabase();

    SignUp* ptrSignUp;
    mainscr* ptrMain;
    userscr* ptrUserScr;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    QSqlDatabase db;
};

#endif // LOGIN_H
