#include "measure.h"
#include "utils.h"

void circles(const cv::String &filename, std::vector<cv::Vec3f> coors)
{
  cv::Mat im_0, im_1, im_med, im_otsu, im_corner;

  // Pre-processing
  im_0 = cv::imread(filename, cv::IMREAD_GRAYSCALE);
  cv::resize(im_0, im_1, cv::Size(), 0.14, 0.14, cv::INTER_CUBIC);

  // Median blur
  cv::medianBlur(im_1, im_med, 5);
//  show("median blur", im_med);

  // Otsu threshold
  cv::threshold(im_med, im_otsu, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
//  show("otsu", im_otsu);

  cv::cornerHarris(im_otsu, im_corner, 2, 3, 0.04, cv::BORDER_DEFAULT);
//  show("harris", im_corner);

  int lim[4] = {0, 0, 0, 0};
  find_roi(im_corner, lim);
  cv::Mat im_1_roi = im_1(cv::Range(lim[0], lim[1]), cv::Range(lim[2], lim[3]));
  cv::Mat im_otsu_roi = im_otsu(cv::Range(lim[0], lim[1]), cv::Range(lim[2], lim[3]));

  // HOUGH CIRCLES
  int min_rad = std::min(im_otsu_roi.rows, im_otsu_roi.cols) / 20;
  cv::HoughCircles(im_otsu_roi, coors, cv::HOUGH_GRADIENT, 1, 50, 200, 10, min_rad, min_rad + 5);

  cv::Mat im_disp;
  cv::cvtColor(im_otsu_roi, im_disp, cv::COLOR_GRAY2BGR);
  for (auto &coor : coors) // draw circles
  {
    cv::Point center = cv::Point(coor[0], coor[1]);
    cv::circle(im_disp, center, 1, cv::Scalar(0, 0, 255), 3, cv::LINE_AA); // circle center point
    cv::circle(im_disp, center, coor[2], cv::Scalar(0, 0, 255), 1, cv::LINE_AA); // circle outline
  }
  cv::imshow("hough circles", im_disp);

  cv::waitKey(0);
  cv::destroyAllWindows();
}
