#include "utils.h"

/* find_roi : return limits with a margin from a Harris corner matrix
 * @param im_corner: Harris corner matrix from cv::cornerHarris
 * @return lim: int array of length 4, in order of xmin, xmax, ymin, ymax
 * @param margin: leave margin from the corners
 */
void find_roi(const cv::Mat& im_corner, int lim[], int margin) {
  int xmin = im_corner.rows;
  int ymin = im_corner.cols;
  int xmax = 0;
  int ymax = 0;

  for (int x = 0; x < im_corner.rows; x++)
  {
    for (int y = 0; y < im_corner.cols; y++)
    {
      if (im_corner.at<float>(x, y) > 1e-6)
      {
        if (x < xmin) xmin = x;
        if (y < ymin) ymin = y;
        if (x > xmax) xmax = x;
        if (y > ymax) ymax = y;
      }
    }
  }

  lim[0] = (xmin - margin) > 0 ? (xmin - margin) : 0;
  lim[1] = (xmax + margin) < im_corner.rows ? (xmax + margin) : im_corner.rows;
  lim[2] = (ymin - margin) > 0 ? (ymin - margin) : 0;
  lim[3] = (ymax + margin) < im_corner.cols ? (ymax + margin) : im_corner.cols;
}
