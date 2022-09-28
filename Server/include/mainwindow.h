#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QSet>
#include <QDateTime>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit  MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void newConnection();
    void readyRead();


private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_2_clicked();

private:
    QTcpServer *file_server;
    QTcpSocket *file_socket;

    QTcpServer *m_server;
    QTcpSocket *m_socket;

    QDateTime time_current;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
