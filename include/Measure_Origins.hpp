/*****************************************************************************                                                                           *
*  @file     contour.hpp                                                     *
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
*  2014/01/24 | 1.0.0.1   | Henry.Wen      | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef CONTOUR_H
#define CONTOUR_H

#include <iostream>
#include <opencv2/opencv.hpp> 
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
using namespace cv;

void Measure_Origins(Mat& src);
bool isNear(const Point2f point, const vector<Point2f> array);


#endif