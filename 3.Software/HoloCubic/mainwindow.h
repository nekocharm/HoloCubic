#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>        // 提供访问串口的功能
#include <QSerialPortInfo>    // 提供系统中存在的串口的信息
#include <QTimer>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 用户函数


private slots:
    void ShowValidPort();
    void OnSerialButtonClicked();
    void OnTextButtonClicked();
    void OnWifiButtonClicked();
    void OnLocationButtonClicked();

private:
    Ui::MainWindow *ui;  

    // 用户变量
    QSerialPort serialPort; // 定义串口类
    QStringList serialPortList; // 串口列表

    QString currentCOM = "";
    QTimer timer;
};
#endif // MAINWINDOW_H
