#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void SetUpServer();

public slots:
    void connectToServer();
    void SendMessageToServer();
    void AcceptMessageFromServer();


private slots:
    void on_lineEdit_3_returnPressed();

private:
    QDateTime time_current;
    QTcpSocket *m_clientSocket;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H