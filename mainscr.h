#ifndef MAINSCR_H
#define MAINSCR_H

#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QLabel>
#include <QVector>
#include <QString>

namespace Ui {
class mainscr;
}

class mainscr : public QDialog
{
    Q_OBJECT

public:
    explicit mainscr(QWidget *parent = nullptr);
    ~mainscr();

    void appendData();
    void connectData();

    QStringList getCurrentData();
    QString inputName;

private:
    Ui::mainscr *ui;

    QSqlQueryModel *SqlModel;
    QSqlDatabase database;
};

#endif // MAINSCR_H
