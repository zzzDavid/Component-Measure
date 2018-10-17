#include "circle.hpp"

// #define DEBUG

void mycircle(Mat & src){

    int dil = 13;
    // binarize image
    Mat image_bin;
    threshold(src, image_bin, 0, 255, CV_THRESH_OTSU);
    #ifdef DEBUG
    namedWindow( "image_bin", WINDOW_NORMAL );
    resizeWindow("image_bin", src.cols/10, src.rows/10);
    imshow("image_bin", image_bin);
    waitKey(0);
    #endif

    // dilated binary image
	// Mat image_dil;
	// Mat element = getStructuringElement(MORPH_RECT, Size(dil, dil));
	// dilate(image_bin, image_dil, element);
	// #ifdef DEBUG
    // namedWindow( "image_dil", WINDOW_NORMAL );
    // resizeWindow("image_dil", src.cols/10, src.rows/10);
    // imshow("image_dil", image_dil);
    // waitKey(0);
    // #endif

    // Gaussian Blur
    Mat image_blur;
    GaussianBlur(image_bin, image_blur, Size(9,9),2,2);


    vector<Vec3f> circles;
    double dp = 1.2;
    double minDist = image_bin.rows/5;
    double param1 = 50;
    double param2 = 30;
    double minRadius = 10;
    double maxRadius = image_bin.cols;
    HoughCircles(image_blur, circles, HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius);
    Mat temp;
    cvtColor(src,temp, COLOR_GRAY2BGR);
    for (int i=0; i<circles.size(); i++){
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle(temp, center, 3, Scalar(0,0,255), -1, 8, 0);
        circle(temp, center, radius, Scalar(0,255,0),3,8,0);
    }
    namedWindow( "all circles", WINDOW_NORMAL );
    resizeWindow("all circles", src.cols/10, src.rows/10);
    imshow("all circles", temp);
    waitKey(0);
}