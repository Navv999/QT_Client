#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mySocket=new QTcpSocket();
    connect(mySocket,SIGNAL(readyRead()),this,SLOT(readyread()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connect_clicked()
{
    ui->plainTextEdit->clear();
    mySocket->connectToHost("127.0.0.1",4444);
    if (mySocket->waitForConnected(3000)){
        ui->plainTextEdit->appendPlainText("Connected to Server");
    }
    else{
        ui->plainTextEdit->appendPlainText("Connection to host failed");

    }

}


void MainWindow::on_disconnect_clicked()
{
    if (mySocket->isOpen())
    {
        mySocket->close();
        ui->plainTextEdit->appendPlainText("Connection to host terminated");

    }

}


void MainWindow::on_lineEdit_returnPressed()
{
    char myChar[1024];
    if (mySocket->isWritable()){
        QString myStr=ui->lineEdit->text();
        memset(myChar,'\0',sizeof(myChar));
        memcpy(myChar,ui->lineEdit->text().toUtf8(),myStr.length());
        mySocket->write(myChar);
        mySocket->waitForBytesWritten(1000);//to be asked
        ui->plainTextEdit->appendPlainText("Client Sended"+ QString(myChar));
        ui->lineEdit->clear();
    }

}


void MainWindow::readyread()
{
    QByteArray myByte;
    myByte=mySocket->readAll();
    ui->plainTextEdit->appendPlainText(QString(myByte));
}

