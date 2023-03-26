#pragma once
#include "helper_functions.h"
#include <opencv2/highgui.hpp>
#include <iostream>
 
cv::Mat minFilter(cv::Mat img, int kernel) {
  if (kernel % 2 == 0) {
    throw std::invalid_argument("Kernel of even size are not allowed");
  }

  cv::Mat new_img(img.rows, img.cols, CV_8U);

  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      unsigned char min = 255;

      for (int x = 0; x < kernel; x++) {
        for (int y = 0; y < kernel; y++) {
          int i_x = i + x;
          int j_y = j + y;
          if (i_x < 0  || i_x >= img.rows || j_y < 0 || j_y >= img.cols) {
            min = std::min(min, (unsigned char) 255);
          } else {
            min = std::min(min, img.at<unsigned char> (i_x, j_y));
          }
        }
      }

      new_img.at<unsigned char> (i,j) = min;
    }
  }
  return new_img;
}

cv::Mat maxFilter(cv::Mat img, int kernel) {
  if (kernel % 2 == 0) {
    throw std::invalid_argument("Kernel of even size are not allowed");
  }

  cv::Mat new_img(img.rows, img.cols, CV_8U);

  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      unsigned char max = 0;

      for (int x = 0; x < kernel; x++) {
        for (int y = 0; y < kernel; y++) {
          int i_x = i + x;
          int j_y = j + y;
          if (i_x < 0  || i_x >= img.rows || j_y < 0 || j_y >= img.cols) {
            max = std::max(max, (unsigned char) 0);
          } else {
            max = std::max(max, img.at<unsigned char> (i_x, j_y));
          }
        }
      }

      new_img.at<unsigned char> (i,j) = max;
    }
  }
  return new_img;
}