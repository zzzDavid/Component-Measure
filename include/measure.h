#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef MEASURE_MEASURE_H
#define MEASURE_MEASURE_H

enum MEASURE_RESULT {
    MEASURE_SUCCESS,
    MEASURE_FAIL
};

void circles(const cv::String& filename, std::vector<cv::Vec3f> coors);

#endif //MEASURE_MEASURE_H
