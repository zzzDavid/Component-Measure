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
*  2014/01/24 | 1.0.0.1   | Zhang Niansong | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "contour.hpp"

bool cmp(vector<Point> a, vector<Point> b)
{
    double i = fabs(contourArea(Mat(a)));
    //cout << "area 1 = " << i << endl;
    double j = fabs(contourArea(Mat(b)));
    //cout << "area 2 = " << j << endl;
    return (i > j);
}

void contour(Mat& src, vector<Point>& contour){

    cout << "channel of input image = " << src.channels() << endl;
    // binarize image
    Mat image_bin;
    int _threshold = 200;
    int dil = 13;
    threshold(src, image_bin, _threshold, 255, THRESH_BINARY);
    // namedWindow( "image_bin", WINDOW_NORMAL );
    // resizeWindow("image_bin", 800, 1000);
    // imshow("image_bin", image_bin);
    // waitKey(0);

    // dilated binary image
	Mat image_dil;
	Mat element = getStructuringElement(MORPH_RECT, Size(dil, dil));
	dilate(image_bin, image_dil, element);
	//imshow("image_dil", image_dil);

    // edge detection
    Mat edged;
    Canny(image_dil, edged, 50, 200);
    // namedWindow( "edged", WINDOW_NORMAL );
    // resizeWindow("edged", 800, 1000);
    // imshow("edged", edged);
    // waitKey(0);
 

    // find all contours and draw them out
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(edged, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0,0)); 

	sort(contours.begin(), contours.end(), cmp);
    
    // for (int i = 0; i < contours.size(); i++)
	// {
	// 	Rect box = boundingRect(Mat(contours[i]));
	// 	int width = box.width;
	// 	int height = box.height;
	// 	cout << "box = " << i << " width = " << width << " height = " << height << endl;
	// }

    // Mat image_copy = src.clone();
    // cvtColor(image_copy, image_copy, COLOR_GRAY2BGR);
	// Scalar color(0,255,0);
    // drawContours(image_copy, contours, 0, color, LINE_8, 8);
    // namedWindow( "contours", WINDOW_NORMAL );
    // resizeWindow("contours", src.cols/10, src.rows/10);
	// imshow("contours", image_copy);
    // waitKey(0);

    contour = contours[0];
}

