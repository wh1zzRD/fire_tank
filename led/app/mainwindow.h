#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QGridLayout>

// #include "joystick.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void redPushButton_pressed();
    void greenPushButton_released();

    void redPushButton_released();
    void greenPushButton_pressed();

private:
    Ui::MainWindow *ui;
    /*Joystick *joystick;*/ // Declare an instance of your joystick class
    // QPushButton *red_PushButton;
    // QPushButton *green_PushButton;

    QSerialPort *arduino;
    bool arduino_is_available;
    QString arduino_port_name;

    static const quint16 arduino_mega_vendorID = 9025;
    static const quint16 arduino_mega_productID = 66;

    bool ledState;

    // Define your Arduino vendor and product ID constants here if needed
    // static const quint16 arduino_mega_vendorID = 0x2341;
    // static const quint16 arduino_mega_productID = 0x0042;
};

#endif // MAINWINDOW_H
