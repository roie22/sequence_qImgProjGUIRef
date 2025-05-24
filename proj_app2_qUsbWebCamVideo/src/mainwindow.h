#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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
    cv::VideoCapture cap;  //!< 视频播放
    QTimer *timer;  //!< 视频播放计时器
    cv::Mat curFrame ;

    SettingDialog *setter;

    void shotOneImage();

    //! new added :
    //!
    // 定义视频编码器和输出文件
    // 使用XVID编码器，文件扩展名为.avi
    cv::VideoWriter videoWriter;
    int frameWidth ;//= static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight;// = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps ;//= cap.get(cv::CAP_PROP_FPS);
    QTimer * timer_recording; //!< 录制视频计时器
    void recordingVieoProc();
     std::string outputFilename;
private slots:
    void on_actionpaizhao_triggered();

    void on_actionOpenSettingDiag_triggered();

    void on_but_shot_image_clicked();

    void on_btn_play_video_clicked();
    void updateframe();
    void on_pushButton_recording_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
