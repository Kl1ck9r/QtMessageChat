
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Client");
    SetUpServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetUpServer()
{
    m_clientSocket=new QTcpSocket(this);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(connectToServer()));
    connect(m_clientSocket,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(SendMessageToServer()));
}

void MainWindow::connectToServer()
{
    m_clientSocket->abort();
    m_clientSocket->connectToHost(ui->lineEdit_2->text(),ui->lineEdit->text().toInt());
    connect(m_clientSocket,SIGNAL(readyRead()),this,SLOT(AcceptMessageFromServer()));
}
 // send message buttons
void MainWindow::SendMessageToServer()
{
    QString message=ui->lineEdit_3->text();
    m_clientSocket->write(ui->lineEdit_3->text().toLatin1());

    time_current=QDateTime::currentDateTime();
    QString _time=time_current.toString("hh:mm");
    message="I: "+ _time+ ": "+message;

    ui->textEdit->append(message);
    ui->lineEdit_3->clear();
}

void MainWindow::on_lineEdit_3_returnPressed()
{
    QString message=ui->lineEdit_3->text();
    m_clientSocket->write(ui->lineEdit_3->text().toLatin1());

    time_current=QDateTime::currentDateTime();
    QString _time=time_current.toString("hh:mm");
    message="I: "+ _time+ ": "+message;

    ui->textEdit->append(message);
    ui->lineEdit_3->clear();
}

void MainWindow::AcceptMessageFromServer()
{
    QString message=m_clientSocket->readAll();
    message="Ruslan: " + message;
    ui->textEdit->append(message);
}



