#include "mainscr.h"
#include "ui_mainscr.h"

mainscr::mainscr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainscr)
{
    ui->setupUi(this);

    ui->listWidget->addItem("Rent");
    //connect(ui->label, &);
    connectData();
    appendData();
}

void mainscr::appendData()
{
    ui->tableView->setModel(SqlModel);
}

QStringList mainscr::getCurrentData()
{
    QStringList rowData;

    //get current row data
    int row = ui->tableView->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();
    //QModelIndex index0 = model->index(row, 0);  //two ways to get index

    if(row != -1)
    {
        //get the value of the whole row that user chosed
        rowData << model->index(row, 0).data().toString();
        rowData << model->index(row, 1).data().toString();
        rowData << model->index(row, 2).data().toString();
        rowData << model->index(row, 3).data().toString();
        rowData << model->index(row, 4).data().toString();
        rowData << model->index(row, 5).data().toString();
        //rowData << model->data(index0).toString(); as another way
    }
    return rowData;
}

void mainscr::connectData()
{
    if(QSqlDatabase::contains("qt_sql_default_connection")) {

        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }

    database.setHostName("localhost");
    database.setUserName("Root");
    database.setPassword("");
    database.setDatabaseName("C:/Users/Rome/Documents/CarRentSystem/usersData.db");

    if(database.open()) {
        SqlModel = new QSqlQueryModel();
        SqlModel->setQuery("select userName, password, email, phoneNumber from users");
    }
    else {
        QMessageBox::information(this, "fail", "open failed");
    }
}

mainscr::~mainscr()
{
    delete ui;
}
