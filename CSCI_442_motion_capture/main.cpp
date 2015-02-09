
#include "main.h"

int main() {
    cv::Mat frame;

    int c = 100;
    cv::VideoCapture capture(0);

    capture >> frame;
    //    cv::Mat weightedFrame = cv::Mat::zeros(frame.size(), CV_32FC3);
    cv::Mat bw = cv::Mat(frame.size(), CV_8UC3);
    cv::Mat run_ave = frame.clone();
    cv::Mat blur_frame = frame.clone();
    cv::Mat weightedFrame = cv::Mat(frame.size(), CV_32FC3);
    cv::Mat dif = frame.clone();
    cv::Mat thresh = cv::Mat(frame.size(), CV_8UC3);
    cv::Mat storage;


    while (1) {
        ;
        capture >> frame;


        /*per helpful hints*/

        /*blur frame and take average*/
        cv::GaussianBlur(frame, blur_frame, Size(21, 21), 0, 0);
        cv::accumulateWeighted(blur_frame, weightedFrame, 0.30);
        cv::convertScaleAbs(weightedFrame, run_ave, 1.0, 0.0);

        /*take difference between average and original*/
        cv::absdiff(run_ave, blur_frame, dif);
        cv::cvtColor(dif, bw, CV_BGR2GRAY);
        
        /*blur and threshold twice*/
        cv::GaussianBlur(bw, bw, Size(21, 21), 0, 0);
        cv::threshold(bw, thresh, 8.0, 255.0, 0);
        cv::GaussianBlur(thresh, thresh, Size(21, 21), 0, 0);
        cv::threshold(thresh, thresh, 8.0, 255.0, 0);

        storage = thresh.clone();

        cv::Mat contour = cv::Mat::zeros(frame.size(), CV_8UC3);
        vector<vector<Point> > vect_contours;
        cv::findContours(storage, vect_contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

        /*compute bounding boxes*/
        Scalar color(255, 255, 255);
        Scalar color_red(0, 0, 255);
        for (unsigned int i = 0; i < vect_contours.size(); i++) {
            drawContours(contour, vect_contours, i, color, 1, 8);

            Point max = findUpperRightCorner(vect_contours.at(i));
            Point min = findLowerLeftCorner(vect_contours.at(i));
            int area = (max.x - min.x) * (max.y - min.y);
            if (area > 1000) {
                rectangle(frame, max, min, color_red, 1, 8, 0);
            }
        }

        //        int npts[vect_contours.size()];
        //        cv::Mat poly = cv::Mat::zeros(frame.size(), CV_8UC3);
        //        Point ** points = double_vector_to_double_array(vect_contours);
        //        fillPoly(poly, points, npts, vect_contours.size(), color, 8, 0);

        cv::imshow("OpenCV", frame);
        cv::imshow("OpenCV2", dif);
        cv::imshow("GrayScale", thresh);
        cv::imshow("New Image", contour);


        c = cv::waitKey(10);
        if (c == 27)
            break;
    }

    return 0;
}

/**
 * 
 * @param ctr
 * @return Point of max x and max y
 */
Point findUpperRightCorner(vector<Point> ctr) {
    int maxX = 0;
    int maxY = 0;

    for (unsigned int i = 0; i < ctr.size(); i++) {
        Point point = ctr.at(i);
        int x = point.x;
        int y = point.y;

        if (x > maxX) {
            maxX = x;
        }
        if (y > maxY) {
            maxY = y;
        }
    }
    Point ret = Point(maxX, maxY);
    return ret;
}

/**
 * 
 * @param ctr
 * @return Point of max x and max y
 */
Point findLowerLeftCorner(vector<Point> ctr) {
    int minX = 1000000000;
    int minY = 1000000000;

    for (unsigned int i = 0; i < ctr.size(); i++) {
        Point point = ctr.at(i);
        int x = point.x;
        int y = point.y;

        if (x < minX) {
            minX = x;
        }
        if (y < minY) {
            minY = y;
        }
    }

    Point ret = Point(minX, minY);
    return ret;
}

Point** double_vector_to_double_array(vector<vector<Point> > vtr) {

    Point ** points = (Point**) malloc(vtr.size() * sizeof (Point*));

    for (unsigned int i = 0; i < vtr.size(); i++) {

        vector<Point> next_vtr = vtr.at(i);
        points[i] = (Point *) malloc(next_vtr.size() * sizeof (Point));
        for (unsigned int j = 0; j < next_vtr.size(); j++) {
            points[i][j] = next_vtr.at(j);
        }
    }

    return points;
}