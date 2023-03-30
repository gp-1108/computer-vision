#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "The usage is ./executable <image_file>\n";
    return -1;
  }

  Mat img = imread(argv[1]);
  namedWindow("Robocop");
  imshow("Robocop", img);
  waitKey(0);
  destroyWindow("Robocop");

  return 0;
}