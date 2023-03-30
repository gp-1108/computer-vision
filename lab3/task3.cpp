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
  
  if ( y + Y_NEIGHBORHOOD > image.rows || x + X_NEIGHBORHOOD > image.cols) {
    // Out of bound
    return;
  }

  Rect rect(x, y, X_NEIGHBORHOOD, Y_NEIGHBORHOOD);
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