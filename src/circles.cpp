#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

cv::Mat read_and_prep(const char *filename)
{
  cv::Mat im_0, im_1, im_2, im;

  im_0 = cv::imread(filename);
  cv::resize(im_0, im_1, cv::Size(), 0.1, 0.1, cv::INTER_CUBIC);
  im_2 = im_1(cv::Range(0, 800), cv::Range(0, 800));
  cv::cvtColor(im_2, im, cv::COLOR_BGR2GRAY);

  return im;
}

int main()
{
  cv::Mat im = read_and_prep("../../image/800-beige/18-04-08-14-32-05.tif");

  // CANNY
  cv::Mat im_canny;
  cv::Canny(im, im_canny, 250, 500, 3);

  cv::imshow("Canny", im_canny);

  // HOUGH LINES
  std::vector<cv::Vec2f> lines;
  cv::HoughLines(im_canny, lines, 1, 0.1, 36, 0, 0);

  cv::Mat im_2;
  cv::cvtColor(im_canny, im_2, cv::COLOR_GRAY2BGR);

  for (auto &line : lines) // draw lines
  {
    float rho = line[0], theta = line[1];
    cv::Point pt1, pt2;
    double a = cos(theta), b = sin(theta);
    double x0 = a * rho, y0 = b * rho;
    pt1.x = cvRound(x0 + 1000 * (-b));
    pt1.y = cvRound(y0 + 1000 * (a));
    pt2.x = cvRound(x0 - 1000 * (-b));
    pt2.y = cvRound(y0 - 1000 * (a));
    cv::line(im_2, pt1, pt2, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
  }

  cv::imshow("Hough Lines", im_2);

  // HOUGH CIRCLES
  std::vector<cv::Vec3f> circles;
  cv::HoughCircles(im, circles, cv::HOUGH_GRADIENT, 1, im.rows / 10, 400, 20, 10, 100);

  cv::Mat im_3;
  cv::cvtColor(im_canny, im_3, cv::COLOR_GRAY2BGR);
  for (auto &circle : circles) // draw circles
  {
    cv::Point center = cv::Point(circle[0], circle[1]);

    cv::circle(im_3, center, 1, cv::Scalar(0, 0, 255), 3, cv::LINE_AA); // circle center point
    cv::circle(im_3, center, circle[2], cv::Scalar(0, 0, 255), 1, cv::LINE_AA); // circle outline
  }

  cv::imshow("Hough Circles", im_3);

  cv::waitKey(0);
  cv::destroyAllWindows();

  return 0;
}
