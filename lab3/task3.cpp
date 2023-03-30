#include <opencv2/highgui.hpp>
#include <iostream>

#define Y_NEIGHBORHOOD 9
#define X_NEIGHBORHOOD 9

using namespace cv;
using namespace std;

void on_click(int event, int x, int y, int flags, void* userdata) {
  if (event != EVENT_LBUTTONDOWN) {
    return;
  }
  Mat image = * (Mat*) userdata;

  int ray_x = (Y_NEIGHBORHOOD - 1) / 2;
  int ray_y = (Y_NEIGHBORHOOD - 1) / 2;
  
  if (x - ray_x < 0 || x + ray_x >= image.cols || y - ray_y < 0 || y + ray_y >= image.rows) {
    // Out of bound
    return;
  }

  Rect rect(x - ray_x, y - ray_y, X_NEIGHBORHOOD, Y_NEIGHBORHOOD);
  Scalar mean = cv::mean(image(rect));

  printf("The mean is: (%f,%f,%f)\n", mean[2], mean[1], mean[0]);
  return;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "The usage is ./executable <image_file>\n";
    return -1;
  }

  Mat img = imread(argv[1]);
  namedWindow("Robocop");
  imshow("Robocop", img);
  setMouseCallback("Robocop", on_click, (void*) &img);
  waitKey(0);
  destroyWindow("Robocop");

  return 0;
} 