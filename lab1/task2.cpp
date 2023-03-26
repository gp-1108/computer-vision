#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "The correct usage is ./exec <img filename>!\n";
    return -1;
  }

  Mat img = imread(argv[1]);

  if (img.data == NULL) {
    std::cout << "Please choose an existing file image!\n";
    return -1;
  }

  std::cout << "The image selected has " << img.channels() << " channels \n";

  namedWindow("Example 1");
  imshow("Example 1", img);

  const char c = waitKey(0);
  std::cout << "The button pressed was " << c << "\n";
  return 0;
}