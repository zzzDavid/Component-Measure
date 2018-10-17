#include <iostream>
#include"contour.hpp"
#include <opencv2/opencv.hpp>
#include <math.h>
#include "circle.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    // read input image
    Mat image_org = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    namedWindow( "original image", WINDOW_NORMAL );
    resizeWindow("original image", 800, 1000);
    imshow("original image", image_org);
    waitKey(0);

    //vector<Point> c;
    //contour(image_org, c);
    mycircle(image_org);
    waitKey(0);
}