#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set up serial port
    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";

    // view ports on your system
    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();\
                qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }

    // check which port the arduino is on
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
            if(serialPortInfo.vendorIdentifier() == arduino_mega_vendorID) {
                if(serialPortInfo.productIdentifier() == arduino_mega_productID) {
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                    qDebug() << "Port available!";
                }
            }
        }
    }

    // setup port if available
    if (arduino_is_available) {
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    } else {
        QMessageBox::warning(this, "Port error", "Couldn't find arduino");
    }

    // Initially, set the LED state to off
    ledState = false;
}

MainWindow::~MainWindow()
{
    if (arduino->isOpen()) {
        qDebug() << "Close port";
        arduino->close();
    }
    delete ui;
}

void MainWindow::on_red_pushButton_pressed()
{
    // Send command '1' to Arduino when the button is pressed
    if (arduino->isWritable()) {
        QString command = "1";
        qDebug() << "Sending command: " << command;
        arduino->write(command.toStdString().c_str());
    } else {
        qDebug() << "Could not write to serial";
    }
}

void MainWindow::on_red_pushButton_released()
{
    // Send command '0' to Arduino when the button is released
    if (arduino->isWritable()) {
        QString command = "0";
        qDebug() << "Sending command: " << command;
        arduino->write(command.toStdString().c_str());
    } else {
        qDebug() << "Could not write to serial";
    }
}

void MainWindow::on_green_pushButton_pressed()
{
    // Send command '1' to Arduino when the button is pressed
    if (arduino->isWritable()) {
        QString command = "3";
        qDebug() << "Sending command: " << command;
        arduino->write(command.toStdString().c_str());
    } else {
        qDebug() << "Could not write to serial";
    }
}


void MainWindow::on_green_pushButton_released()
{
    // Send command '0' to Arduino when the button is released
    if (arduino->isWritable()) {
        QString command = "2";
        qDebug() << "Sending command: " << command;
        arduino->write(command.toStdString().c_str());
    } else {
        qDebug() << "Could not write to serial";
    }
}

