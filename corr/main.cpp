#include <stdio.h>
#include <iostream>
//#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/opencv_lib.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

float correlation(cv::Mat &image1, cv::Mat &image2)
{
    cv::Mat corr;
    cv::matchTemplate(image1, image2, corr, cv::TM_CCORR_NORMED);
    return corr.at<float>(0,0);  // corr only has one pixel
}

int main()
{
    cv::String filename = "/home/kobayashi/color_bar.jpg";
    Mat target;
    target = cv::imread(filename);
    if(target.empty()) exit(-1);

    cv::VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH,1280);
    cap.set(CAP_PROP_FRAME_HEIGHT,720);

    while(1)
    {
        Mat frame;
        cap >> frame;


        float co = correlation(frame,target);
        printf("correlation : %f \n",double(co));
        imshow("camera",frame);
        imshow("target",target);


        if(waitKey(30) >= 0) break;
    }

    return 0;
}
