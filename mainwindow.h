#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#include <opencv2/opencv.hpp>
#include <iostream>
#include "settingdialog.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // 打开默认USB摄像头（设备号通常为0或1）
    cv::VideoCapture cap;//(0);

    SettingDialog *setter;

private slots:
    void on_actionpaizhao_triggered();

    void on_pushButton_clicked();

    void on_actionOpenSettingDiag_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
