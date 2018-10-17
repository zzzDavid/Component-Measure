/*****************************************************************************                                                                           *
*  @file     contour.cpp                                                     *
*  @brief    对文件的简述                                                      *
*  Details.                                                                  *
*                                                                            *
*  @author   Zhang Niansong                                                  *                                              *
*  @version  1.0.0                                                           *
*  @date     2018-10-16                                                      *                               
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/01/24 | 1.0.0.1   | Zhang Niansong | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "contour.hpp"

#define DEBUG

bool cmp(vector<Point> a, vector<Point> b)
{
    double i = fabs(contourArea(Mat(a)));
    //cout << "area 1 = " << i << endl;
    double j = fabs(contourArea(Mat(b)));
    //cout << "area 2 = " << j << endl;
    return (i > j);
}

void contour(Mat& src, vector<Point>& contour){

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
	Mat image_dil;
	Mat element = getStructuringElement(MORPH_RECT, Size(dil, dil));
	dilate(image_bin, image_dil, element);
	#ifdef DEBUG
    namedWindow( "image_dil", WINDOW_NORMAL );
    resizeWindow("image_dil", src.cols/10, src.rows/10);
    imshow("image_dil", image_dil);
    waitKey(0);
    #endif

    // edge detection
    Mat edged;
    Canny(image_dil, edged, 100, 220);
    #ifdef DEBUG
    namedWindow( "edged", WINDOW_NORMAL );
    resizeWindow("edged", src.cols/10, src.rows/10);
    imshow("edged", edged);
    waitKey(0);
    #endif
 

    // find all contours and draw them out
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(edged, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0,0)); 

	sort(contours.begin(), contours.end(), cmp);
    
    for (int i = 0; i < contours.size(); i++)
	{
		Rect box = boundingRect(Mat(contours[i]));
		int width = box.width;
		int height = box.height;
        #ifdef DEBUG
        cout << "all boxes: " << endl;
		cout << "box = " << i << " width = " << width << " height = " << height << endl;
        #endif
	}

     Mat image_copy = src.clone();
     cvtColor(image_copy, image_copy, COLOR_GRAY2BGR);
	 Scalar color(0,255,0);
     drawContours(image_copy, contours, 0, color, LINE_8, 8);

     #ifdef DEBUG
     namedWindow( "contours", WINDOW_NORMAL );
     resizeWindow("contours", src.cols/10, src.rows/10);
	 imshow("contours", image_copy);
     waitKey(0);
     #endif

    // The exterior contour
    contour = contours[0];
    Rect box = boundingRect(Mat(contour));
    vector<Point2f> rectCorners(4);
    rectCorners[0] = Point2f(box.x, box.y);
    rectCorners[1] = Point2f(box.x+box.width, box.y);
    rectCorners[2] = Point2f(box.x, box.y+box.height);
    rectCorners[3] = Point2f(box.x+box.width, box.y+box.height);

    #ifdef DEBUG
    cout << "Box axis:" << endl;
    cout << "bottom left = " << "(" << box.x <<  " , " << box.y << ")" << endl;
    cout << "bottom right = " << "(" << box.x + box.width <<  " , " << box.y << ")" << endl;
    cout << "top left = " <<  "(" << box.x <<  " , " << box.y + box.height << ")" << endl;
    cout << "top right = " <<  "(" << box.x + box.width <<  " , " << box.y + box.height << ")" << endl;
    #endif


    // Good feature to track
    vector<Point2f> corners;
    int max_corners = 10;
    double quality_level = 0.01;
    double min_distance = 100.0;
    int block_size = 3;
    bool use_harris = false;
    double k = 0.04;
    goodFeaturesToTrack(edged, corners, max_corners, quality_level, min_distance,Mat(), block_size, use_harris, k);
    // select corners
    for( int i=corners.size()-1; i>=0; i-- ){
        if (!isNear(corners[i], rectCorners)){
            corners.erase(corners.begin() + i);
            cout << "point at" << corners[i].x << corners[i].y << "is removed" << endl;
        }else{
            cout << "point at" << corners[i].x << corners[i].y << "is preserved" << endl;
        }
    }
    //#ifdef DEBUG
    // draw corners
    Mat img_corners;
    cvtColor(src, img_corners, COLOR_GRAY2BGR);
    cout << "found corner axis:" << endl;
    for (int i=0; i<corners.size(); i++){
        circle(img_corners,corners[i], 50, Scalar(0,255,0),8, 8, 0);
        cout << "x = " << corners[i].x << "\t\t y = " << corners[i].y << endl;
    }
    for (int i=0; i<rectCorners.size(); i++){
        circle(img_corners,rectCorners[i], 50, Scalar(0,0,255),8, 8, 0);
    }
    namedWindow("corners", WINDOW_NORMAL);
    resizeWindow( "corners",src.cols/10, src.rows/10);
    imshow("corners", img_corners);
    waitKey(0);
    //#endif


}

bool isNear(const Point2f point, const vector<Point2f> array){
    // if the point is near any of the points in array
    bool flag = 0;
    for (int i=0; i<array.size(); i++){
        float x = array[i].x;
        float y = array[i].y;
        float dist = sqrt( (x-point.x)*(x-point.x) + (y-point.y)*(y-point.y) );
        if (dist < 100) flag = 1;
    }
    
    return flag;
}
