#include "measure.h"

#ifndef MEASURE_UTILS_H
#define MEASURE_UTILS_H

void inline show(const cv::String& win, const cv::Mat& im) {
  cv::imshow(win, im);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

void find_roi(const cv::Mat& im_corner, int lim[], int margin=10);

#endif //MEASURE_UTILS_H
