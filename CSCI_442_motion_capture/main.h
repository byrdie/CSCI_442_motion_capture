/* 
 * File:   main.h
 * Author: byrdie
 *
 * Created on February 7, 2015, 7:04 PM
 */

#ifndef MAIN_H
#define	MAIN_H


#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstddef>
#include <opencv2/core/core.hpp> // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
    using namespace std;
    using namespace cv;


    Point findUpperRightCorner(vector<Point> ctr);
    Point findLowerLeftCorner(vector<Point> ctr);
    Point** double_vector_to_double_array(vector<vector<Point> > vtr);



#endif	/* MAIN_H */

