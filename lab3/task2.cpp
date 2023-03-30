#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void on_click(int event, int x, int y, int flags, void* userdata) {
  if (event != EVENT_LBUTTONDOWN) {
    return;
  }
  Mat image = * (Mat*) userdata;
  // Remember to switch to (y,x)
  Vec3b pixel = image.at<Vec3b> (y, x);

  // OpenCV uses BGR encoding, not RGB
  printf("The RGB value is (%u,%u,%u)\n", pixel[2], pixel[1], pixel[0]);
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