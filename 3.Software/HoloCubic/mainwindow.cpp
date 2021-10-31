#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/holocubic.png"));
    connect(&timer,&QTimer::timeout,this,&MainWindow::ShowValidPort); //定时检测串口
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(OnSerialButtonClicked())); //连接串口按钮
    connect(ui->textButton, SIGNAL(clicked()), this, SLOT(OnTextButtonClicked())); //文字页面发送按钮
    connect(ui->wifiButton, SIGNAL(clicked()), this, SLOT(OnWifiButtonClicked())); //网络设置发送按钮
    connect(ui->locationButton, SIGNAL(clicked()), this, SLOT(OnLocationButtonClicked())); //位置设置发送按钮
    // 设置串口信息
    serialPort.setBaudRate(115200);                        //设置波特率
    serialPort.setDataBits(QSerialPort::Data8);          //设置数据位
    serialPort.setStopBits(QSerialPort::OneStop);        //设置停止位
    serialPort.setParity(QSerialPort::NoParity);          //设置奇偶校验
    serialPort.setFlowControl(QSerialPort::NoFlowControl);//设置流控制模式

    // 开始计时
    timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ShowValidPort()
{
    QStringList newSerialPortList;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            newSerialPortList += info.portName();
    if(newSerialPortList.size() != serialPortList.size())
    {
        serialPortList = newSerialPortList;
        ui->comboBox->clear();
        ui->comboBox->addItems(serialPortList);
    }
    if(currentCOM != ui->comboBox->currentText()) //串口突然断开连接了
    {
        currentCOM = ui->comboBox->currentText();
        if("关闭" == ui->pushButton->text())
        {
            OnSerialButtonClicked();
        }
    }
}

void MainWindow::OnSerialButtonClicked()
{
    if("打开" == ui->pushButton->text())
    {
        currentCOM = ui->comboBox->currentText();
        serialPort.setPortName(currentCOM); //获取串口号
        if(serialPort.open(QIODevice::ReadWrite)) //如果打开串口成功
        {
            ui->pushButton->setText("关闭");
            ui->comboBox->setEnabled((false));
        }
    }
    else if("关闭" == ui->pushButton->text())
    {
        ui->pushButton->setText("打开");
        serialPort.close();
        ui->comboBox->setEnabled((true));
    }
}

void MainWindow::OnTextButtonClicked()
{

    if(serialPort.isOpen()==false)  //判断串口是否正常打开
    {
        QMessageBox::warning(this,"提示","请打开串口！");
        return;
    }

    QByteArray text("text");

    if(ui->textEdit->toPlainText().length()>0){
        int sizeText = text.size();
        text = text.insert(sizeText,ui->textEdit->toPlainText().toUtf8());
        serialPort.write(text);
    }

}

void MainWindow::OnWifiButtonClicked(){

    QEventLoop eventloop;
    if(serialPort.isOpen()==false)  //判断串口是否正常打开
    {
        QMessageBox::warning(this,"提示","请打开串口！");
        return;
    }
    QByteArray wifiSSID("ssid");
    QByteArray wifiPassword("pswd");
    if(ui->ssidEdit->text().length()>0){
        int sizeWifiSSID = wifiSSID.size();
        wifiSSID = wifiSSID.insert(sizeWifiSSID,ui->ssidEdit->text().toUtf8());
        serialPort.write(wifiSSID);
    }

    QTimer::singleShot(200, &eventloop, SLOT(quit()));
    eventloop.exec();
    if(ui->ssidEdit->text().length()>0){
        int sizeWifiPassword = wifiPassword.size();
        wifiPassword = wifiPassword.insert(sizeWifiPassword,ui->passwordEdit->text().toUtf8());
        serialPort.write(wifiPassword);
    }

}

void MainWindow::OnLocationButtonClicked(){

    if(serialPort.isOpen()==false)  //判断串口是否正常打开
    {
        QMessageBox::warning(this,"提示","请打开串口！");
        return;
    }
    QByteArray weatherLocation("weat");

    if(ui->locationEdit->text().length()>0){
        int sizeWeatherLocation = weatherLocation.size();
        weatherLocation = weatherLocation.insert(sizeWeatherLocation,ui->locationEdit->text().toUtf8());
        serialPort.write(weatherLocation);
    }

}

