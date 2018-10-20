/* 
 * @ Brief: this function finds corners of a RECTANGLE
 * @ Description:
 *   Get exterior contour -> Polygon fitting -> Find corners
*/
#include "Measure_Origins.hpp"
#include "getExteriorContour.hpp"

//#define DEBUG

void Measure_Origins(Mat& src){

    // get The exterior contour
    vector<Point> contour;
    Mat edged;
    getExteriorContour(src, contour);
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

    // draw corners
    Mat img_corners;
    cvtColor(src, img_corners, COLOR_GRAY2BGR);
    
    for (int i=0; i<rectCorners.size(); i++){
        circle(img_corners,rectCorners[i], 50, Scalar(0,0,255),8, 8, 0);
    }
    namedWindow("corners", WINDOW_NORMAL);
    resizeWindow( "corners",src.cols/10, src.rows/10);
    imshow("corners", img_corners);
    imwrite("./output/corners.jpg", img_corners);
    waitKey(0);

}