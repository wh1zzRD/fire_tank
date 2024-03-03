#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
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

private slots:
    void on_red_pushButton_pressed();
    void on_green_pushButton_released();

    void on_red_pushButton_released();

    void on_green_pushButton_pressed();

private:
    Ui::MainWindow *ui;
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
