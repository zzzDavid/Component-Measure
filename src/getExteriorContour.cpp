/* 
 * @ Brief: this function takes in a Mat image and returns the exterior contour of object
 * @ Description:
 *   Binarize -> dilate -> edge -> findContour -> select contour that has largest area
*/

#include "getExteriorContour.hpp"

// #define DEBUG_EXTERIOR

bool cmpArea(vector<Point> a, vector<Point> b)
{
    double i = fabs(contourArea(Mat(a)));
    double j = fabs(contourArea(Mat(b)));
    return (i > j);
}

void getExteriorContour( Mat src, vector<Point>& contour){

    /* parameters */
    int dil = 13;

    // binarize image
    Mat image_bin;
    threshold(src, image_bin, 0, 255, CV_THRESH_OTSU);
    #ifdef DEBUG_EXTERIOR
    namedWindow( "image_bin", WINDOW_NORMAL );
    resizeWindow("image_bin", src.cols/10, src.rows/10);
    imshow("image_bin", image_bin);
    waitKey(0);
    #endif

    // dilated binary image
	Mat image_dil;
	Mat element = getStructuringElement(MORPH_RECT, Size(dil, dil));
	dilate(image_bin, image_dil, element);
	#ifdef DEBUG_EXTERIOR
    namedWindow( "image_dil", WINDOW_NORMAL );
    resizeWindow("image_dil", src.cols/10, src.rows/10);
    imshow("image_dil", image_dil);
    waitKey(0);
    #endif

    // edge detection
    Mat edged;
    Canny(image_dil, edged, 100, 220);
    #ifdef DEBUG_EXTERIOR
    namedWindow( "edged", WINDOW_NORMAL );
    resizeWindow("edged", src.cols/10, src.rows/10);
    imshow("edged", edged);
    waitKey(0);
    #endif

    // find all contours
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(edged, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0,0)); 

    // Sort by area
	sort(contours.begin(), contours.end(), cmpArea);

    // The exterior contour
    contour = contours[0];
}

