#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/User/Desktop/QTPROJ/SQL1/DB2..db3");
    mydb.open();

    qry = new QSqlQuery(mydb);
    qry->prepare("Select * from Employees");
    qry->exec();

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(*qry);
    ui->tableView->setModel(model);

    connect(ui->addButton, &QPushButton::clicked, [=](){
        QString name = ui->name->text();
        QString surname = ui->surname->text();
        int age = ui->age->text().toInt();
        QString job = ui->job->text();

        //Insert new Entry
        qry->prepare("insert into Employees (Name, Surname, Age, Job) values ('"+name+"','"+surname+"', '"+QString::number(age)+"', '"+job+"')");
        qry->exec();

        //Reshow the Table Again
        qry->prepare("Select * from Employees");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
    });


    connect(ui->updateButton, &QPushButton::clicked, [=](){
        QString name = ui->name->text();
        QString surname = ui->surname->text();
        int age = ui->age->text().toInt();
        QString job = ui->job->text();

        //Update Entry Matching Name
        qry->prepare("update Employees set Name='"+name+"', Surname='"+surname+"', Age='"+QString::number(age)+"', Job='"+job+"' where Name='"+name+"' ");
        qry->exec();

        //Reshow the Table Again
        qry->prepare("Select * from Employees");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);


    });

    connect(ui->deleteButton, &QPushButton::clicked, [=](){
        QString name = ui->name->text();
        QString surname = ui->surname->text();
        int age = ui->age->text().toInt();
        QString job = ui->job->text();

        //Delete Entry Matching Name and Surname
        qry->prepare("Delete from Employees WHERE (Name='"+name+"' AND Surname='"+surname+"')");
        qry->exec();

        //Reshow the Table Again
        qry->prepare("Select * from Employees");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
    });


    connect(ui->tableView, &QTableView::clicked, [=] (QModelIndex index) {

        QString Value = ui->tableView->model()->index(index.row(), index.column()).data().toString();

        qDebug() << Value;


        if(index.column() == 0)
        {
    QString Surname = ui->tableView->model()->index(index.row(), index.column()+1).data().toString();
     qry->prepare("Select * from Employees WHERE Name ='"+Value+"' AND Surname='"+Surname+"'");
            qry->exec();
            qry->next();
        }

        if(index.column() == 1)
        {
    QString Age = ui->tableView->model()->index(index.row(), index.column()+1).data().toString();
            qry->prepare("Select * from Employees WHERE Surname ='"+Value+"' AND Age = '"+Age+"'");
            qry->exec();
            qry->next();
        }

        if(index.column() == 2)
        {
    QString Job = ui->tableView->model()->index(index.row(), index.column()+1).data().toString();
            qry->prepare("Select * from Employees WHERE Age ='"+Value+"' AND Job = '"+Job+"'");
            qry->exec();
            qry->next();
        }

        if(index.column() == 3)
        {
    QString Age = ui->tableView->model()->index(index.row(), index.column()-1).data().toString();
            qry->prepare("Select * from Employees WHERE Job ='"+Value+"' AND Age = '"+Age+"'");
            qry->exec();
            qry->next();
        }

        ui->name->setText(qry->value(0).toString());
        ui->surname->setText(qry->value(1).toString());
        ui->age->setText(qry->value(2).toString());
        ui->job->setText(qry->value(3).toString());
    } );


    connect(ui->searchEdit, &QLineEdit::textChanged, [=](){
        QString searchtxt = ui->searchEdit->text();
        qDebug() << searchtxt;

        //Look for a Match in Jobs
        if (searchtxt.length()!= 0)
        qry->prepare("Select * from Employees WHERE Job = '"+searchtxt+"'");
            else qry->prepare("Select * from Employees");
        qry->exec();

        //Reshow the Table Again
        model->setQuery(*qry);
        ui->tableView->setModel(model);

    });
}

MainWindow::~MainWindow()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
    delete ui;
}

