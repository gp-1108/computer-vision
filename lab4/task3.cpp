#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "trackBarsFuncs.hpp"
#include "EventStruct.hpp"


using namespace cv;

int main (int argc, char** argv) {
  if (argc < 2) {
    std::cout << "The usage is ./exec <image_path>\n";
    return -1;
  }

  Mat img = imread(argv[1]);

  if (img.data == NULL) {
    std::cout << "Pleace choose an existing image path\n";
    return -1; 
  }

  EventStruct* my_pane = new EventStruct;
  my_pane->threshold = 0;
  my_pane->sigma = 1.5;
  my_pane->hough = 120;
  my_pane->image = img;
  my_pane->rads = 180;
  cvtColor(img, my_pane->gray_scale, COLOR_BGR2GRAY);

  namedWindow("Threshold");

  createTrackbar("Min Threshold: ", "Threshold", nullptr, 100, trackBarChangeThreshold, (void*) my_pane);
  setTrackbarPos("Min Threshold: ", "Threshold", my_pane->threshold);

  createTrackbar("Sigma: ", "Threshold", nullptr, 100, trackBarChangeSigma, (void*) my_pane);
  setTrackbarPos("Sigma: ", "Threshold", my_pane->sigma);

  createTrackbar("Hough Threshold: ", "Threshold", nullptr, 300, trackBarChangeHough, (void*) my_pane);
  setTrackbarPos("Hough Threshold: ", "Threshold", my_pane->hough);

  createTrackbar("Rads hough: ", "Threshold", nullptr, 180, trackBarChangeRads, (void*) my_pane);
  setTrackbarPos("Rads hough: ", "Threshold", my_pane->rads);

  imshow("Threshold", my_pane->image);
  waitKey(0);

  delete(my_pane);
  return 0;
}