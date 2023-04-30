#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "helper_funcs.hpp"

using namespace cv;

struct EventStruct {
  double sigma;
  int pixel_thresh;
  int mean_thresh;
  Mat img;
};

int main(int argc, char** argv) {
  namedWindow("Segmentation");


  Mat img = imread("../robocup.jpg");

  processImageRobot(img, img);
  imshow("Segmentation", img);
  waitKey(0);

  return 0;
}