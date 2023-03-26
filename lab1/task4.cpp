#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

void const check_channels(Mat source_img) {
  if (source_img.channels() != 3) { return; }
  Mat img0(source_img.rows, source_img.cols, CV_8UC3);
  Mat img1(source_img.rows, source_img.cols, CV_8UC3);
  Mat img2(source_img.rows, source_img.cols, CV_8UC3);

  for (int i = 0; i < source_img.rows; i++) {
    for (int j = 0; j < source_img.cols; j++) {
      img0.at<Vec3b> (i,j)[0] = source_img.at<Vec3b> (i,j)[0];
      img1.at<Vec3b> (i,j)[1] = source_img.at<Vec3b> (i,j)[1];
      img2.at<Vec3b> (i,j)[2] = source_img.at<Vec3b> (i,j)[2];
    }
  }

  namedWindow("Check_channels");
  imshow("Check_channels", img0);
  waitKey(0);
  imshow("Check_channels", img1);
  waitKey(0);
  imshow("Check_channels", img2);
  waitKey(0);
}

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

  check_channels(img);

  std::cout << "The button pressed was " << c << "\n";
  return 0;
}