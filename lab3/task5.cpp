#include <opencv2/highgui.hpp>
#include <iostream>

#define Y_NEIGHBORHOOD 9
#define X_NEIGHBORHOOD 9

using namespace cv;
using namespace std;

struct Click_Structure {
  bool has_mask;
  cv::Mat image;
};


// One click to show the mask, one click to make it fade out and reveal the original image
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

  Mat image = click->image.clone();

  int ray_x = (Y_NEIGHBORHOOD - 1) / 2;
  int ray_y = (Y_NEIGHBORHOOD - 1) / 2;
  
  if (x - ray_x < 0 || x + ray_x >= image.cols || y - ray_y < 0 || y + ray_y >= image.rows) {
    // Out of bound
    return;
  }

  Rect rect(x - ray_x, y - ray_y, X_NEIGHBORHOOD, Y_NEIGHBORHOOD);
  Scalar mean = cv::mean(image(rect));

  Mat mask(image.rows, image.cols, CV_8UC3);

  cout << "Choose a threshold: ";
  int t = 0;
  cin >> t;

  // The color is the RGB tuple (92, 37, 201)
  Vec3b color_mask(201, 37, 201);

  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      Vec3b pixel = image.at<Vec3b> (i,j);
      
      int distance_B = abs(pixel[0] - mean[0]);
      int distance_G = abs(pixel[1] - mean[1]);
      int distance_R = abs(pixel[2] - mean[2]);

      if (distance_B <= t && distance_G <= t && distance_R <= t) {
        mask.at<Vec3b> (i,j) = color_mask;
      } else {
        mask.at<Vec3b> (i,j) = pixel;
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