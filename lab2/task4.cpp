#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
int main (int argc, char **argv) {
  Mat img = imread(argv[1]);

  if (img.data == NULL) {
    std::cout << "Please choose an existing file image!\n";
    return -1;
  }

  namedWindow("gray scale");
  // Showing color image
  imshow("gray scale", img);
  waitKey(0);


  // Converting to gray scale
  Mat gray_scale_img(img.rows, img.cols, CV_8U);
  cvtColor(img, gray_scale_img, COLOR_BGR2GRAY, 0);

  // Computing histogram
  Mat b_hist;
  int hist_size = 256;
  float range[] = {0, 256};
  const float *hist_range = { range };
  bool uniform = true, accumulate = false;
  calcHist(&gray_scale_img, 1, 0, Mat(), b_hist, 1, &hist_size, &hist_range, uniform, accumulate);

  // Drawing the histogram
  int hist_w = 512, hist_h = 400;
  int bin_w = cvRound((double) hist_w / hist_size);
  Mat hist(hist_h, hist_w, CV_8U, Scalar(0, 0, 0));
  normalize(b_hist, b_hist, 0, hist.rows, NORM_MINMAX, -1, Mat());
  for (int i = 1; i < hist_size; i++) {
    line(hist, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 255, 255), 2, 8, 0);
  }

  imshow("gray scale", hist);
  waitKey(0);
  destroyAllWindows();
  return 0;
}