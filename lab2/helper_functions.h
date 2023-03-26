#pragma once
#include <opencv2/highgui.hpp>

cv::Mat minFilter(cv::Mat img, int kernel);

cv::Mat maxFilter(cv::Mat img, int kernel);
