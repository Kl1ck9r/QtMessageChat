#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowTitle("Server");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{

    m_socket=m_server->nextPendingConnection();

    if(m_socket==nullptr){
        QMessageBox::critical(this,"Error in server","Failed accept signal from client !");
        exit(EXIT_FAILURE);

    }

    connect(m_socket,SIGNAL(disconnected()),m_socket,SLOT(deleteLater()));
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    m_socket->write("Welcome To Server !");
    m_socket->flush();
}

void MainWindow::readyRead()
{
    QString message=m_socket->readAll();
    message="Anton: "+message;
    ui->textEdit->append(message);
}

void MainWindow::on_pushButton_clicked()
{
    m_socket->write(ui->lineEdit->text().toLatin1());
    QString str=ui->lineEdit->text();

    time_current=QDateTime::currentDateTime();
    QString _time=time_current.toString("hh:mm");
    str="I: " +_time + ": " +str;

    ui->textEdit->append(str);
    ui->lineEdit->clear();
}

void MainWindow::on_lineEdit_returnPressed()
{
    m_socket->write(ui->lineEdit->text().toLatin1());
    QString str=ui->lineEdit->text();

    time_current = QDateTime::currentDateTime();
    QString _time=time_current.toString("hh:mm");
    str="I: "+_time + ": " +str;

    ui->textEdit->append(str);
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    m_socket=new QTcpSocket(this);
    m_server=new QTcpServer(this);

    if(!m_server->listen(QHostAddress::Any,ui->lineEdit_2->text().toInt()))
    {
        QMessageBox::critical(this,"Error in Server","Failed connect to host !");
        m_server->errorString();
    }else{
           connect(m_server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    }
}


