#include <iostream>
#include"Measure_Origins.hpp"
#include <opencv2/opencv.hpp>
#include <math.h>
#include "detectLines.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    // read input image
    Mat image_org = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

    vector<Point> c;
    //Measure_Origins(image_org);
    detectCurve(image_org);
   
}