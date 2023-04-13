#pragma once
#include <opencv2/highgui.hpp>

struct EventStruct{
  int threshold;
  int sigma;
  int hough;
  int rads;
  cv::Mat image;
  cv::Mat gray_scale;
};

