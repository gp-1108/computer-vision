#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

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


  Mat gray_scale_img(img.rows, img.cols, CV_8U);
  // Showing gray scale image
  cvtColor(img, gray_scale_img, COLOR_BGR2GRAY, 0);
  imshow("gray scale", gray_scale_img);
  waitKey(0);
  return 0;
}