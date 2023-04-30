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

  double sigma = 1.5;
  int mean_thresh = 94;
  int pixel_thresh = 56;
  Mat img1 = imread("../Asphalt-1.png", IMREAD_GRAYSCALE);
  Mat img2 = imread("../Asphalt-2.png", IMREAD_GRAYSCALE);
  Mat img3 = imread("../Asphalt-3.png", IMREAD_GRAYSCALE);

  processImageAsphalt(img1, img1, sigma, mean_thresh, pixel_thresh);
  imshow("Segmentation", img1);
  waitKey(0);

  processImageAsphalt(img2, img2, sigma, mean_thresh, pixel_thresh);
  imshow("Segmentation", img2);
  waitKey(0);

  processImageAsphalt(img3, img3, sigma, mean_thresh, pixel_thresh);
  imshow("Segmentation", img3);
  waitKey(0);

  return 0;
}