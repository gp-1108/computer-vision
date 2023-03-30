#include <opencv2/highgui.hpp>
#include <iostream>

#define Y_NEIGHBORHOOD 9
#define X_NEIGHBORHOOD 9

struct Click_Structure {
  bool has_mask;
  cv::Mat image;
};

using namespace cv;
using namespace std;

void on_click(int event, int x, int y, int flags, void* userdata) {
  if (event != EVENT_LBUTTONDOWN) {
    return;
  }
  Click_Structure* click = (Click_Structure*) userdata;

  if (click->has_mask) {
    imshow("Robocop", click->image);
    click->has_mask = false;
    return;
  }

  int ray_x = (Y_NEIGHBORHOOD - 1) / 2;
  int ray_y = (Y_NEIGHBORHOOD - 1) / 2;
  
  if (x - ray_x < 0 || x + ray_x >= click->image.cols || y - ray_y < 0 || y + ray_y >= click->image.rows) {
    // Out of bound
    return;
  }

  Rect rect(x - ray_x, y - ray_y, X_NEIGHBORHOOD, Y_NEIGHBORHOOD);
  Scalar mean = cv::mean(click->image(rect));

  Mat mask(click->image.rows, click->image.cols, CV_8U);

  cout << "Choose a threshold: ";
  int t = 0;
  cin >> t;

  for (int i = 0; i < click->image.rows; i++) {
    for (int j = 0; j < click->image.cols; j++) {
      Vec3b pixel = click->image.at<Vec3b> (i,j);
      
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

  imshow("Robocop", mask);
  click->has_mask = true;

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

  Click_Structure* my_pane = new Click_Structure;
  my_pane->has_mask = false;
  my_pane->image = img;
  setMouseCallback("Robocop", on_click, (void*) my_pane);
  waitKey(0);
  destroyWindow("Robocop");

  delete(my_pane);
  return 0;
} 