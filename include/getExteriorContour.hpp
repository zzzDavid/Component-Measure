#ifndef GET_EXTERIOR_CONTOUR_H
#define GET_EXTERIOR_CONTOUR_H

#include <iostream>
#include <opencv2/opencv.hpp> 
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
using namespace cv;


void getExteriorContour( Mat src, vector<Point>& contour);

#endif