/*
  The best options to remove the cables were:
    -max filter -> kernel = 5
    -min filter -> kernel = NA, the cables never really disappear
*/
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include "helper_functions.cpp"
#include <opencv2/core/types.hpp>

using namespace cv;

int main (int argc, char **argv) {
  Mat img = imread(argv[1]);

  if (img.data == NULL) {
    std::cout << "Please choose an existing file image!\n";
    return -1;
  }

  namedWindow("gray scale");
  // Showing color image
  imshow("gray scale", img);
  waitKey(0);
  // destroyWindow("gray scale");


  Mat gray_scale_img(img.rows, img.cols, CV_8U);
  // Showing gray scale image
  cvtColor(img, gray_scale_img, COLOR_BGR2GRAY, 0);
  // imshow("gray scale", gray_scale_img);
  // waitKey(0);

  for(int kernel_size = 3; kernel_size < 35; kernel_size += 2) {
    std::cout << "Starting with kernel " << kernel_size << std::endl;

    Mat min_filtered = minFilter(gray_scale_img, kernel_size);
    char min_filename[50];
    sprintf(min_filename, "./filtered/min_filtered_kernel_%d.png", kernel_size);
    imwrite(min_filename, min_filtered);

    Mat max_filtered = maxFilter(gray_scale_img, kernel_size);
    char max_filename[50];
    sprintf(max_filename, "./filtered/max_filtered_kernel_%d.png", kernel_size);
    imwrite(max_filename, max_filtered);

    Mat median_filtered(gray_scale_img.rows, gray_scale_img.cols, CV_8U);
    medianBlur(gray_scale_img, median_filtered, kernel_size);
    char median_filename[50];
    sprintf(median_filename, "./filtered/median_filtered_kernel_%d.jpg", kernel_size);
    imwrite(median_filename, median_filtered);
    
    Mat gaussian_filtered(gray_scale_img.rows, gray_scale_img.cols, CV_8U);
    GaussianBlur(gray_scale_img, gaussian_filtered, Size(kernel_size, kernel_size), 0, 0, BORDER_DEFAULT);
    char gaussian_filename[50];
    sprintf(gaussian_filename, "./filtered/gaussian_filtered_kernel_%d.jpg", kernel_size);
    imwrite(gaussian_filename, gaussian_filtered);
  }

  return 0;
}