#include "detectLines.hpp"
#include "Measure_Origins.hpp"
#include "getExteriorContour.hpp"
// #define DEBUG_CIRCLE


void detectCurve(Mat & src){

    Mat img_plg(src.size(), CV_8UC1, Scalar(255));

    /*Fit contour into polygon*/
    PolyFit(src, img_plg);

    /*Detect Circles*/
    vector<Vec3f> circles;
    mycircle(src, circles);
    /* Description:
     * circles contains all circles detected
     * Vec3f = vector of 3 floats: x, y, r
    */

    /*Detect Rect Corners*/
    vector<Point> rectCorners;
    findRectCorners(img_plg, circles, rectCorners);

    /*Detect Lines*/
    vector<Vec4i> linesP;
    Mat temp;
    cvtColor(img_plg, temp, CV_GRAY2BGR);
    calcLinesP(temp, linesP);
        /*Only preserve vertical and horizontal lines*/
    for (int i=linesP.size()-1; i>=0; i--){
        if(!isVorH(linesP[i])){
            linesP.erase(linesP.begin()+i);
        }
    }
    drawLinesP(temp, linesP);
    cout << "found "<< linesP.size() << " vertical and horizontal lines in total" << endl;
    imwrite("./output/LineDetection.jpg", temp);
    /* Description:
     * linesP contains all lines detected
     * Vec4i = vector of 4 integers: x1, y1, x2, y2
     * The start and end point of the line
    */

    /*Find Curve Ends*/
    // ATTENTION: this can only deal with 1-curve situation
    //            doesn't work with multiple curves
    vector<Point> curveEnds;
    findCurveEnds(linesP, circles, curveEnds);
    cout << "Found "<< curveEnds.size() << " curve ends" << endl;

    /*Extract curve from contour*/
    vector<Point> contour;
    vector<Point> curve;
    getExteriorContour(src, contour);
    extractCurve(contour, curveEnds, curve);

    /*Draw corners, str8t lines and curves on original picture*/
    vector<Vec4i> straight_lines;
    vector<vector<Point>> curves;
    Mat img_all;
    cvtColor(src, img_all, CV_GRAY2BGR);
    curves.push_back(curve);
    createStraightLines(rectCorners, curveEnds, straight_lines);
    drawStraightLines(img_all, straight_lines);
    drawPoints(img_all, rectCorners, curveEnds);
    polylines(img_all, curves, 0, Scalar(0,0,255), 50);
    // draw circle on image
    for (int i=0; i<circles.size(); i++){
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle(img_all, center, 3, Scalar(0,0,255), 30);
        circle(img_all, center, radius, Scalar(0,0,255),20);
    }
    imwrite("./output/image_all.jpg", img_all);

}

/*-------------------------------------------------------------------------------------*/
/*                              helper functions                                       */
/*-------------------------------------------------------------------------------------*/

void createStraightLines(vector<Point> rectCorners, vector<Point> curveEnds, vector<Vec4i>& straight_lines){
    vector<Point> points;
    points.insert(points.end(), rectCorners.begin(), rectCorners.end());
    points.insert(points.end(), curveEnds.begin(), curveEnds.end());
    for (int i=0; i< points.size(); i++){
        for (int j=0; j < i; j++){
            straight_lines.push_back( Vec4i(points[i].x, points[i].y, points[j].x, points[j].y) );
        }
    }
    for (int i=straight_lines.size()-1; i>=0; i--){
        if(!isVorH(straight_lines[i])){
            straight_lines.erase( straight_lines.begin()+i );
        }
    }
}

void drawStraightLines(Mat& img_all, vector<Vec4i> straight_lines){
    for (int i=0; i< straight_lines.size(); i++){
        line(img_all, Point(straight_lines[i][0], straight_lines[i][1]),
             Point(straight_lines[i][2], straight_lines[i][3]), Scalar(255,0,0), 50);
    }
}

void drawPoints(Mat& img_all, vector<Point> rectCorners, vector<Point> curveEnds){
    for (int i=0; i< rectCorners.size(); i++){
        circle(img_all, rectCorners[i], 50, Scalar(0,255,0), 50);
    }
    for (int i=0; i< curveEnds.size(); i++){
        circle(img_all, curveEnds[i], 50, Scalar(0,0,255), 50);
    }
}

void mycircle(Mat src, vector<Vec3f>& circles){

    // binarize
    Mat image_bin;
    threshold(src, image_bin, 0, 255, CV_THRESH_OTSU);

    // Gaussian Blur
    Mat image_blur;
    GaussianBlur(image_bin, image_blur, Size(9,9),2,2);

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
    #ifdef DEBUG_CIRCLE
    namedWindow( "all circles", WINDOW_NORMAL );
    resizeWindow("all circles", src.cols/10, src.rows/10);
    imshow("all circles", temp);
    waitKey(0);
    #endif
    imwrite("./output/detected_circles.jpg", temp);
}

void findRectCorners(Mat img_plg, vector<Vec3f> circles, vector<Point>& corners){   
    // find corners
    int max_corners = 30;
    double quality_level = 0.01;
    double min_distance = 100.0;
    int block_size = 20;
    bool use_harris = true;
    double k = 0.04;
    goodFeaturesToTrack(img_plg, corners, max_corners, quality_level, min_distance,Mat(), block_size, use_harris, k);

    // Erase the corners that is not rectangular
    eraseCorner(corners, circles);

    // draw corners
    Mat img_corners;
    cvtColor(img_plg, img_corners, COLOR_GRAY2BGR);
    cout << "found corner axis:" << endl;
    for (int i=0; i<corners.size(); i++){
        circle(img_corners,corners[i], 50, Scalar(0,255,0),8, 8, 0);
        cout << "x = " << corners[i].x << "\t\t y = " << corners[i].y << endl;
    }
    #ifdef DEBUG_CIRCLE
    namedWindow("corners", WINDOW_NORMAL);
    resizeWindow( "corners",src.cols/10, src.rows/10);
    imshow("corners", img_corners);
    waitKey(0);
    #endif
    imwrite("./output/Rectangular_corners.jpg", img_corners);
}

void PolyFit(Mat src, Mat& img_plg){
    // get exterior contour
    vector<Point> contour;
    getExteriorContour(src, contour);   

    // polygon approximation
    vector<vector<Point>> polygons;
    vector<Point> polygon;
    vector<Point> plg_for_vertice;
    approxPolyDP(contour, polygon, 50, true);
    approxPolyDP(contour, plg_for_vertice, 200, true);

    // draw polygon for line detection
    polygons.push_back(polygon);
    drawContours(img_plg, polygons, -1, Scalar(0), 1);
    #ifdef DEBUG_CIRCLE
    namedWindow( "fitted polygon", WINDOW_NORMAL );
    resizeWindow("fitted polygon", src.cols/10, src.rows/10);
	imshow("fitted polygon", img_plg);
    waitKey(0);
    #endif
    imwrite("./output/polyDP.jpg", img_plg);
}

void drawLinesP(Mat &input, const vector<Vec4i> &lines){
    for (int i=0; i<lines.size(); i++){
        line(input, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(255,0,0), 50);
    }
}

void calcLinesP(const Mat &input, vector<Vec4i> &lines){
    Mat contours;
    Canny(input, contours, 50, 150);
    lines.clear();
    HoughLinesP(contours, lines, 1, CV_PI/180, 10, 100, 1000);
}

void eraseCorner(vector<Point>& corners, vector<Vec3f> circles){
    for (int i=corners.size()-1; i>=0; i--){
        if(isNearCircle(corners[i], circles)){
            corners.erase( corners.begin()+i );
        }
    }
}

bool isNearCircle(Point corner, vector<Vec3f> circles){
    bool flag = false;
    for (int i=0; i<circles.size(); i++){
        double dist = sqrt( (corner.x-circles[i][0])*(corner.x-circles[i][0]) +
                            (corner.y-circles[i][1])*(corner.y-circles[i][1]) );
        if (dist <= circles[i][2]*1.1){
            flag = true;
        }
    }
    return flag;
}

void findCurveEnds(vector<Vec4i> linesP, vector<Vec3f> circles, vector<Point>& curveEnds){
    vector<Point> temp;
    for( int i=0; i<linesP.size(); i++ ){
        Point lineEnd1 = Point(linesP[i][0], linesP[i][1]);
        Point lineEnd2 = Point(linesP[i][2], linesP[i][3]);
        if(isNearCircle(lineEnd1, circles)){
            temp.push_back(lineEnd1);
        }
        if(isNearCircle(lineEnd2, circles)){
            temp.push_back(lineEnd2);
        }
    }
    
    curveEnds.push_back(temp[0]);
    for( int i=1; i<temp.size(); i++){
        double dst = sqrt( (curveEnds[0].x-temp[i].x)*(curveEnds[0].x-temp[i].x) +
                           (curveEnds[0].y-temp[i].y)*(curveEnds[0].y-temp[i].y) ); // dst between 1st pt and other pts
        if(dst >= circles[0][2]*1.4){
            curveEnds.push_back(temp[i]);
            break;
        }
    }
}

void extractCurve(vector<Point> contour, vector<Point> curveEnds, vector<Point>& curve){
//  ATTENTION: this function only work with 1 curve, which has 2 end points!
    for (int i=0; i<contour.size(); i++){
        if(contour[i].x >= min(curveEnds[0].x, curveEnds[1].x) &&
           contour[i].x <= max(curveEnds[0].x, curveEnds[1].x) &&
           contour[i].y >= min(curveEnds[0].y, curveEnds[1].y) &&
           contour[i].y <= max(curveEnds[0].y, curveEnds[1].y)){
               curve.push_back(contour[i]);
        }
    }
}

bool isVorH(Vec4i line){
    Point point1 = Point(line[0], line[1]);
    Point point2 = Point(line[2], line[3]);
    if(point1.y > point2.y){
        Point temp;
        temp = point2;
        point2 = point1;
        point1 = temp;
    } // keep point1 as the lower point and point2 as the higher point 
    /* calculate cosine, cause we keep pt1 at low, the angle is between [0, pi] */
    double cos = (point2.x - point1.x)/sqrt( (point1.x-point2.x)*(point1.x-point2.x) + (point1.y-point2.y)*(point1.y-point2.y) );
    if ( abs(cos)>0.98 || abs(cos) < 0.02 ) return true;
    else return false;
}