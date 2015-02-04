//#include <stdafx.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp> // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
using namespace cv;

int main()
{
      cv::Mat frame;
      int c = 100;
      cv::VideoCapture capture(0);
      //cv::cvCapture *capture = cv::cvCaptureFromCAM(0);
     while(1)
     {
              //frame = cv::cvQueryFrame(capture);
              capture >> frame;
              cv::Mat bw = cv::Mat(frame.size(), CV_8UC1);
              cv::cvtColor(frame, bw, CV_BGR2GRAY);
               cv::Canny(bw, bw, 80, 100);
              cv::imshow("OpenCV",frame);
              cv::imshow("GrayScale", bw);

              c = cv::waitKey(10);
              if(c==27)
                    break;
     }

     return 0;
}