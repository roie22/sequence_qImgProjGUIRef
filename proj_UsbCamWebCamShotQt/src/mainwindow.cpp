#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBoxCamId->addItem("0");
    ui->comboBoxCamId->addItem("1");
    ui->comboBoxCamId->addItem("2");
    ui->comboBoxCamId->addItem("3");
     ui->comboBoxCamId->addItem("4");
    ui->comboBoxCamId->currentText();

    int  camId = ui->comboBoxCamId->currentText().toUInt();
    if(!cap.isOpened()){
        qDebug()<< "打开摄像头失败。 camId= "<<camId ;
    }

    // 检查摄像头是否成功打开
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera. camId = " <<camId<< std::endl;
        qDebug()<< "!cap.isOpened(),camId= "<<camId ;
        // return -1;
    }

    // 设置摄像头分辨率（可选）
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    // 创建一个窗口显示实时画面
    // cv::namedWindow("Camera Preview", cv::WINDOW_AUTOSIZE);
    std::cout << "Press 's' to save a photo, 'q' to quit..." << std::endl;

    setter=new SettingDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    // 释放资源
    cap.release();
    cv::destroyAllWindows();
}

#include<iostream>
#include<QDebug>

#include <iostream>
#include <chrono>
#include <ctime>

#include <chrono>
//#include <format>  // C++20
#include <iostream>

#include <chrono>
#include <iomanip>
#include <sstream>

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
//    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d_%H_%M_%S");
    return ss.str();
}



void MainWindow::on_actionpaizhao_triggered()
{
    qDebug()<< "on_actionpaizhao_triggered. ";

    int  camId = ui->comboBoxCamId->currentText().toUInt();
    if(!cap.isOpened())
    {
        cap.open(camId);
    }

    if(!cap.isOpened()){
        qDebug()<< "打开摄像头失败。 camId= "<<camId ;
    }

    {
        cv::Mat frame;
        cap >> frame; // 捕获一帧

        if (frame.empty()) {
            qDebug()<< "frame.empty()";
            return;
        }

        {
            std::string fileName=get_current_time()+".jpg";
            std::cout<<"save img to fileName= "<<fileName<< std::endl;
            //        stringstream
            cv::imwrite(fileName , frame);
        }

        // 将 OpenCV 的 BGR 图像转换为 RGB（Qt 默认格式）
        if(1)cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

        // 将 cv::Mat 转换为 QImage
        QImage qimage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

        // 缩放图像以适应 QLabel
        QPixmap pixmap = QPixmap::fromImage(qimage).scaled(
            ui->imageLabel->width(), ui->imageLabel->height(), Qt::KeepAspectRatio);

        // 显示图像
        ui->imageLabel->setPixmap(pixmap);
    }
}

void MainWindow::on_pushButton_clicked()
{
    on_actionpaizhao_triggered();
}

#include "settingdialog.h"
void MainWindow::on_actionOpenSettingDiag_triggered()
{
    setter->exec();
}

