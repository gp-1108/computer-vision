/*
  The actual circle detection does not work properly, no idea why though
*/
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

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

  Mat gray_scale;
  cvtColor(img, gray_scale, COLOR_BGR2GRAY);
  GaussianBlur(gray_scale, gray_scale, Size(5,5), 1.5);

  // Detecting circles
  std::vector<Vec3f> circles;
  HoughCircles(gray_scale, circles, HOUGH_GRADIENT, 2,
    gray_scale.rows/6,
    300, 30, 0, 12
  );
  for( size_t i = 0; i < circles.size(); i++ ) {
    Vec3i c = circles[i];
    Point center = Point(c[0], c[1]);
    int radius = c[2];
    circle(img, center, radius, Scalar(255,0,0), -1, 8, 0);
  }

  namedWindow("Threshold");

  imshow("Threshold", img);
  waitKey(0);

  return 0;
}