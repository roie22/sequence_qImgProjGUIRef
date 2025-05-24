#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"

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

    int camId = ui->comboBoxCamId->currentText().toUInt();
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
    //    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    //    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    // 创建一个窗口显示实时画面
    // cv::namedWindow("Camera Preview", cv::WINDOW_AUTOSIZE);
    std::cout << "Press 's' to save a photo, 'q' to quit..." << std::endl;

    setter=new SettingDialog(this);

    timer = new QTimer;
    connect(timer,&QTimer::timeout,this, &MainWindow::updateframe);

    timer_recording = new QTimer;
    connect(timer_recording,&QTimer::timeout,this, &MainWindow::recordingVieoProc);

}

MainWindow::~MainWindow()
{
    delete ui;

    // 释放资源
    cap.release();
    cv::destroyAllWindows();
}


std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    //    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d_%H_%M_%S");
    return ss.str();
}

void MainWindow::shotOneImage(){
    qDebug()<< "on_actionpaizhao_triggered. ";
#if  0
    int camId = ui->comboBoxCamId->currentText().toUInt();
    if(!cap.isOpened())
    {
        cap.open(camId);
    }

    if(!cap.isOpened()){
        qDebug()<< "打开摄像头失败。 camId= "<<camId ;
        return ;
    }

    {
        cv::Mat frame;
        cap >> frame; // 捕获一帧

        if (frame.empty()) {
            qDebug()<< "frame.empty()";
            return;
        }
#endif

        {
            std::string fileName=get_current_time()+".jpg";
            std::cout<<"save img to fileName= "<<fileName<< std::endl;
            //        stringstream
            cv::imwrite(fileName , curFrame);
        }

#if  0
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
#endif
}

//! 拍一张照
void MainWindow::on_actionpaizhao_triggered()
{
    shotOneImage();
}



#include "settingdialog.h"
//! 设置对话框
void MainWindow::on_actionOpenSettingDiag_triggered()
{
    setter->exec();
}


void MainWindow::on_but_shot_image_clicked()
{
    shotOneImage();
}


#include <QPixmap>
#include <QImage>
#include <opencv2/opencv.hpp>

QPixmap matToQPixmap(const cv::Mat& mat) {
    // 处理空矩阵
    if (mat.empty()) {
        return QPixmap();
    }

    // 转换图像格式
    cv::Mat rgbMat;
    switch (mat.channels()) {
    case 1:  // 灰度图
        cv::cvtColor(mat, rgbMat, cv::COLOR_GRAY2RGB);
        break;
    case 3:  // BGR彩色图
        cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
        break;
    case 4:  // BGRA图（带Alpha通道）
        cv::cvtColor(mat, rgbMat, cv::COLOR_BGRA2RGBA);
        break;
    default:
        return QPixmap();
    }

    // 创建QImage并设置数据
    QImage qImage(rgbMat.data, rgbMat.cols, rgbMat.rows,
                  rgbMat.step,
                  (mat.channels() == 4) ? QImage::Format_RGBA8888 : QImage::Format_RGB888);

    // 复制图像数据以避免内存管理问题
    return QPixmap::fromImage(qImage.copy());
}

void MainWindow:: updateframe(){
    cap>> curFrame;
    QPixmap  pix =matToQPixmap(curFrame);
    // 缩放图像以适应 QLabel
    QPixmap pixmap = pix.scaled(
                ui->imageLabel->width(), ui->imageLabel->height(), Qt::KeepAspectRatio);
    this->ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->show();
}

void MainWindow::on_btn_play_video_clicked()
{
    int camId = ui->comboBoxCamId->currentText().toUInt();
    if(!cap.isOpened())
    {
        cap.open(camId);
    }

    if(!cap.isOpened()){
        qDebug()<< "打开摄像头失败。 camId= "<<camId ;
    }
    else
    {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

        // 手动设置分辨率和帧率
        //        cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        //        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
        //        double fps = 30.0;

        std::string name = cap.getBackendName();
        int wid = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        int hei = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

        int bright = cap.get(cv::CAP_PROP_BRIGHTNESS);
        int gain = cap.get(cv::CAP_PROP_GAIN);
        int expose = cap.get(cv::CAP_PROP_EXPOSURE);
        int format = cap.get(cv::CAP_PROP_FORMAT);
        int contrast = cap.get(cv::CAP_PROP_CONTRAST);

        // 获取视频的宽度、高度和帧率
        frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        fps = cap.get(cv::CAP_PROP_FPS);


        ui->textBrowser_videoInfo->append( ("name:"+name).c_str());
        ui->textBrowser_videoInfo->append( ("video wid:"+std::to_string(wid)).c_str());
        ui->textBrowser_videoInfo->append( ("video hei:"+std::to_string(hei)).c_str());
        ui->textBrowser_videoInfo->append( ("video fps:"+std::to_string(fps)).c_str());
        ui->textBrowser_videoInfo->append( ("video bright:"+std::to_string(bright)).c_str());

        ui->textBrowser_videoInfo->append( ("video gain:"+std::to_string(gain)).c_str());
        ui->textBrowser_videoInfo->append( ("video expose:"+std::to_string(expose)).c_str());
        ui->textBrowser_videoInfo->append( ("video format:"+std::to_string(format)).c_str());
        ui->textBrowser_videoInfo->append( ("video contrast:"+std::to_string(contrast)).c_str());
    }

    static int counter =1;
    if(counter& 1==1)
        timer->start(33);
    else{
        timer->stop();
        cap.release();
    }
    counter++;
}


void  MainWindow::recordingVieoProc(){


    // 写入当前帧到视频文件
    videoWriter.write(curFrame);
}

void MainWindow::on_pushButton_recording_clicked()
{
    static int counter =1;
    if(counter& 1==1){
        std::string name=get_current_time();
        outputFilename = name+std::to_string(frameWidth)+"_"+std::to_string(frameHeight)+"_"+std::to_string(fps)+"_"+"_output.avi";
        //  QString::arg("",frameWidth,frameWidth,frameWidth);
   qDebug()<< "outputFilename: "<< outputFilename.c_str();
        int fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');
        // 使用MJPG编码器(兼容性更好)
        //    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
        // 打开视频写入器
        if (!videoWriter.open(outputFilename, fourcc, fps, cv::Size(frameWidth, frameHeight))) {
            std::cerr << "无法创建视频文件! outputFilename=" <<outputFilename<< std::endl;
            // return -1;
        }
        //std::string name=get_current_time();

        timer_recording->start(33);
    }
    else{
        timer_recording->stop();
        videoWriter.release();
    }
    counter++;


}

