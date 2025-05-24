#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;

/**
 * @brief 拼接两张图像（自动处理尺寸不一致）
 * @param img1 第一张图像
 * @param img2 第二张图像
 * @param direction 0=水平拼接，1=垂直拼接
 * @param bgColor 背景填充颜色（默认黑色）
 */
cv::Mat combineImages(const cv::Mat& img1, const cv::Mat& img2,
                      int direction = 0, cv::Scalar bgColor = cv::Scalar(0, 0, 0)) {
    // 统一尺寸
    cv::Mat img2_resized;
    if (direction == 0) { // 水平拼接
        cv::resize(img2, img2_resized, cv::Size(img2.cols, img1.rows));
    } else { // 垂直拼接
        cv::resize(img2, img2_resized, cv::Size(img1.cols, img2.rows));
    }

    // 创建画布
    cv::Mat combined;
    if (direction == 0) {
        combined = cv::Mat(
            std::max(img1.rows, img2_resized.rows),
            img1.cols + img2_resized.cols,
            img1.type(),
            bgColor
            );
        img1.copyTo(combined(cv::Rect(0, 0, img1.cols, img1.rows)));
        img2_resized.copyTo(combined(cv::Rect(img1.cols, 0, img2_resized.cols, img2_resized.rows)));
    } else {
        combined = cv::Mat(
            img1.rows + img2_resized.rows,
            std::max(img1.cols, img2_resized.cols),
            img1.type(),
            bgColor
            );
        img1.copyTo(combined(cv::Rect(0, 0, img1.cols, img1.rows)));
        img2_resized.copyTo(combined(cv::Rect(0, img1.rows, img2_resized.cols, img2_resized.rows)));
    }

    return combined;
}

void checkPts(std::vector<cv::Point2f> pts_img_left,
              std::vector<cv::Point2f> pts_imgIdeal_left,
              std::vector<cv::Point2f> pts_proj_left,
              cv::Mat src,cv::Mat &markedImg){
    markedImg=src.clone();
    int thickness = 5;
    int radius = 6;
   for(int i=0;i<pts_img_left.size();i++){
       cv::Scalar blue(255,0,0);
       cv::circle(markedImg,pts_img_left[i],radius+i*2,blue,thickness);
       cv::Scalar yellow(255,255,0);
       cv::circle(markedImg,pts_imgIdeal_left[i],radius+7+i*2,yellow,thickness);

       cv::Scalar white(255,255,255);
       cv::circle(markedImg,pts_proj_left[i]/1.0,radius+9+i*2,white,thickness);
   }
}

int main()
{
    cout << "Hello World!" << endl;
    cv::Mat src_left=cv::imread("../images/2025-05-21_16_24_48.jpg",1);

    cv::Mat imgCheckLeft ;
    /**
 * 左上            右上
 *  |              |
 *  |             /|\
 * \|/             |
 *  |         \    |
 *  左下  -------- 右下
 *            /
 */
    std::vector<cv::Point2f> pts_img_left={
        cv::Point2f(969,605), cv::Point2f(872,777),cv::Point2f(1233,777),cv::Point2f(1340,606)
    };
    std::vector<cv::Point2f> pts_img_right={
        cv::Point2f(1101,607), cv::Point2f(1233,777),cv::Point2f(1590,777),cv::Point2f(1474,606)
    };

    std::vector<cv::Point2f> pts_imgIdeal_left={
        cv::Point2f(969,605), cv::Point2f(872,777),cv::Point2f(1233,777),cv::Point2f(1230,606)
    };
    std::vector<cv::Point2f> pts_imgIdeal_right={
        cv::Point2f(1230,607), cv::Point2f(1233,777),cv::Point2f(1590,777),cv::Point2f(1474,606)
    };

    std::vector<cv::Point2f> pts_proj_left={
        cv::Point2f(0,0), cv::Point2f(0,576),cv::Point2f(1152,576),cv::Point2f(1152,0)
    };
    std::vector<cv::Point2f> pts_proj_right={
        cv::Point2f(0,0), cv::Point2f(0,576),cv::Point2f(1152,576),cv::Point2f(1152,0)
    };

    cv::Mat markedImg_left;
    checkPts( pts_img_left, pts_imgIdeal_left, pts_proj_left, src_left, markedImg_left);
    cv::imwrite("markedImg_left.jpg", markedImg_left);
//    combineImages();

    cv::Mat t_p2i_left = cv::getPerspectiveTransform(pts_proj_left, pts_img_left);
    cv::Mat t_i2ii_left = cv::getPerspectiveTransform(pts_img_left, pts_imgIdeal_left);
    std::cout<<"t_p2i_left= "<<t_p2i_left<< std::endl;
    std::cout<<"t_i2ii_leftt_i2ii_left= "<<t_i2ii_left<< std::endl;
    cv::Mat t_p2pi_left=t_p2i_left.inv()* t_i2ii_left* t_p2i_left;
std::cout<<"t_p2pi_left= "<<t_p2pi_left<< std::endl;

    cv::Mat t_p2i_right = cv::getPerspectiveTransform(pts_proj_right, pts_img_right);
    cv::Mat t_i2ii_right = cv::getPerspectiveTransform(pts_img_right, pts_imgIdeal_right);
    std::cout<<"t_p2i_right= "<<t_p2i_right<< std::endl;
    std::cout<<"t_i2ii_right_i2ii_left= "<<t_i2ii_right<< std::endl;
    cv::Mat t_p2pi_right=t_p2i_right.inv()* t_i2ii_right* t_p2i_right;
    std::cout<<"t_p2pi_right= "<<t_p2pi_right<< std::endl;

    cv::Mat markedImg_right;
    checkPts( pts_img_right, pts_imgIdeal_right, pts_proj_right, src_left, markedImg_right);
    cv::imwrite("markedImg_right.jpg", markedImg_right);

    cv::FileStorage fs("t_p2pi.xml", cv::FileStorage::WRITE);
    if (fs.isOpened()) {
        fs << "t_p2i_left" << t_p2i_left;
        fs << "t_i2ii_left" <<t_i2ii_left;
        fs<<"t_p2pi_left"<<t_p2pi_left;

        fs << "t_p2i_right" << t_p2i_right;
        fs << "t_i2ii_right" <<t_i2ii_right;
        fs<<"t_p2pi_right"<<t_p2pi_right;
    }
    fs.release(); // 关闭文件

    return 0;
}
