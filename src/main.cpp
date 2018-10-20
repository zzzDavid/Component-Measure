#include "measure.h"
#include "utils.h"

#define DEBUG

int main(int argc, char* argv[]) {

#ifdef DEBUG
  cv::String filename = "../../image/798-333-beige/18-07-17-15-19-34top.tif";

  std::vector<cv::Vec3f> coors;
  circles(filename, coors);
#endif

  return 0;
}
