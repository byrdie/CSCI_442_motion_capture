//#include <stdafx.h>
#include <stdlib.h>
#include <cstddef>
#include <opencv2/core/core.hpp> // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
using namespace cv;

int main() {
    cv::Mat frame;

    int c = 100;
    cv::VideoCapture capture(0);

    capture >> frame;
    //    cv::Mat weightedFrame = cv::Mat::zeros(frame.size(), CV_32FC3);

    while (1) {
        //frame = cv::cvQueryFrame(capture);
        capture >> frame;
        cv::Mat bw = cv::Mat(frame.size(), CV_8UC1);
        cv::Mat run_ave = frame.clone();
        cv::Mat weightedFrame = cv::Mat(frame.size(), CV_32FC3);

        cv::cvtColor(frame, bw, CV_BGR2GRAY);
        cv::Canny(bw, bw, 80, 100);

        /*per helpful hints*/

        cv::accumulateWeighted(frame, weightedFrame, 0.32);
        cv::convertScaleAbs(weightedFrame, run_ave, 1.0, 0.0);
        //        cv::GaussianBlur(weightedFrame, weightedFrame, Size(31, 31), 0, 0);

        cv::imshow("OpenCV", frame);
        cv::imshow("GrayScale", bw);
        cv::imshow("New Image", run_ave);

        c = cv::waitKey(10);
        if (c == 27)
            break;
    }

    return 0;
}