#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

void plot_hist(Mat img) {
  // Computing histogram
  Mat b_hist;
  int hist_size = 256;
  float range[] = {0, 256};
  const float *hist_range = { range };
  bool uniform = true, accumulate = false;
  calcHist(&img, 1, 0, Mat(), b_hist, 1, &hist_size, &hist_range, uniform, accumulate);

  // Drawing the histogram
  int hist_w = 512, hist_h = 400;
  int bin_w = cvRound((double) hist_w / hist_size);
  Mat hist(hist_h, hist_w, CV_8U, Scalar(0, 0, 0));
  normalize(b_hist, b_hist, 0, hist.rows, NORM_MINMAX, -1, Mat());
  for (int i = 1; i < hist_size; i++) {
    line(hist, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 255, 255), 2, 8, 0);
  }
  namedWindow("Histogram");
  imshow("Histogram", hist);
  waitKey(0);
  destroyWindow("Histogram");
}

int main (int argc, char **argv) {
  Mat img = imread(argv[1]);

  if (img.data == NULL) {
    std::cout << "Please choose an existing file image!\n";
    return -1;
  }



  // Converting to gray scale and showing histogram and image
  Mat gray_scale_img(img.rows, img.cols, CV_8U);
  cvtColor(img, gray_scale_img, COLOR_BGR2GRAY, 0);
  namedWindow("Image");
  imshow("Image", gray_scale_img);
  waitKey(0);
  plot_hist(gray_scale_img);

  // Equalizing the image and re-plotting
  Mat equalized(img.rows, img.cols, CV_8U);
  equalizeHist(gray_scale_img, equalized);
  imshow("Image", equalized);
  waitKey(0);
  plot_hist(equalized);

  destroyAllWindows();
  return 0;
}