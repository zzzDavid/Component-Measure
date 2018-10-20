#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <opencv2/opencv.hpp> 
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
using namespace cv;

void detectCurve(Mat& src);
void mycircle(Mat src, vector<Vec3f>& circles);
void findRectCorners(Mat img_plg, vector<Vec3f> circles, vector<Point>& corners);
void PolyFit(Mat src, Mat& img_plg);
void drawLinesP(Mat &input, const vector<Vec4i> &lines);
void calcLinesP(const Mat &input, vector<Vec4i> &lines);
void eraseCorner(vector<Point>& corners, vector<Vec3f> circles);
void findCurveEnds(vector<Vec4i> linesP, vector<Vec3f> circles, vector<Point>& curveEnds);
void extractCurve(vector<Point> contour, vector<Point> curveEnds, vector<Point>& curve);
bool isNearCircle(Point corner, vector<Vec3f> circles);
bool isVorH(Vec4i line);
void createStraightLines(vector<Point> rectCorners, vector<Point> curveEnds, vector<Vec4i>& straight_lines);
void drawStraightLines(Mat& img_all, vector<Vec4i> straight_lines);
void drawPoints(Mat& img_all, vector<Point> rectCorners, vector<Point> curveEnds);

#endif