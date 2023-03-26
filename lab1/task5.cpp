#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char **argv) {
  Mat vertical_grad(256, 256, CV_8U);
  Mat horizontal_grad(256, 256, CV_8U);

  // Filling gradients
  for (int i = 0; i < vertical_grad.rows; i++) {
    for (int j = 0; j < vertical_grad.cols; j++) {
      vertical_grad.at<unsigned char> (i,j) = i;
      horizontal_grad.at<unsigned char> (i, j) = j;
    }
  }

  namedWindow("Window");
  imshow("Window", vertical_grad);
  waitKey(0);
  imshow("Window", horizontal_grad);
  waitKey(0);

  // Creating chessboards
  Mat chessboard_20px(300, 300, CV_8U);
  Mat chessboard_50px(300, 300, CV_8U);

  int x_counter = 0, y_counter = 0;
  bool is_white = true;

  // Filling the 50px chessboard
  for (int i = 0; i < 300; i++) {
    for (int j = 0; j < 300; j++) {
      y_counter++;
      if (y_counter >= 50) {
        is_white = !is_white;
        y_counter = 0;
      }

      if (is_white) {
        chessboard_50px.at<unsigned char> (i, j) = 255;
      } else {
        chessboard_50px.at<unsigned char> (i, j) = 0;
      }
    }
    x_counter++;
    if (x_counter >= 50) {
      is_white = !is_white;
      x_counter = 0;
    }
  }

  // Filling the 20px chessboard
  x_counter = 0;
  y_counter = 0;
  is_white = true;
  for (int i = 0; i < 300; i++) {
    for (int j = 0; j < 300; j++) {
      y_counter++;
      if (y_counter >= 20) {
        is_white = !is_white;
        y_counter = 0;
      }

      if (is_white) {
        chessboard_20px.at<unsigned char> (i, j) = 255;
      } else {
        chessboard_20px.at<unsigned char> (i, j) = 0;
      }
    }
    x_counter++;
    if (x_counter >= 20) {
      is_white = !is_white;
      x_counter = 0;
    }
  }


  imshow("Window", chessboard_50px);
  waitKey(0);
  imshow("Window", chessboard_20px);
  waitKey(0);

  return 0;
}