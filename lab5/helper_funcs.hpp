#pragma once
#include <opencv2/highgui.hpp>

void processImageAsphalt(const cv::Mat& img, cv::Mat& dst, double sigma, int mean_thresh, int pixel_thresh);

void processImageStreet(const cv::Mat& img, cv::Mat& dst);

void processImageRobot(const cv::Mat& img, cv::Mat& dst);