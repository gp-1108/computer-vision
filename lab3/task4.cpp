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

  Mat mask(image.rows, image.cols, CV_8U);

  cout << "Choose a threshold: ";
  int t = 0;
  cin >> t;

  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      Vec3b pixel = image.at<Vec3b> (i,j);
      
      int distance_B = abs(pixel[0] - mean[0]);
      int distance_G = abs(pixel[1] - mean[1]);
      int distance_R = abs(pixel[2] - mean[2]);

      if (distance_B <= t && distance_G <= t && distance_R <= t) {
        mask.at<unsigned char> (i,j) = 255;
      } else {
        mask.at<unsigned char> (i,j) = 0;
      }
    }
  }

  namedWindow("Mask");
  imshow("Mask", mask);
  waitKey(0);
  destroyWindow("Mask");

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