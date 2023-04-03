#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

struct EventStruct{
  int threshold;
  int sigma;
  cv::Mat image;
  cv::Mat gray_scale;
};

using namespace cv;

void trackBarChangeThreshold(int pos, void* userdata) {
  EventStruct* event = (EventStruct*) userdata;
  event->threshold = pos;

  Mat edges(event->image.rows, event->image.cols, CV_8U);
  GaussianBlur(event->gray_scale, edges, Size(5,5), event->sigma);

  Canny(edges, edges, event->threshold, 3 * event->threshold, 3, false);
  imshow("Threshold", edges);

  return;
}

void trackBarChangeSigma(int pos, void* userdata) {
  EventStruct* event = (EventStruct*) userdata;
  event->sigma = pos;

  Mat edges(event->image.rows, event->image.cols, CV_8U);
  GaussianBlur(event->gray_scale, edges, Size(5,5), event->sigma);

  Canny(edges, edges, event->threshold, 3 * event->threshold, 3, false);
  imshow("Threshold", edges);

  return;
}

int main (int argc, char** argv) {
  if (argc < 2) {
    std::cout << "The usage is ./exec <image_path>\n";
    return -1;
  }

  Mat img = imread(argv[1]);

  if (img.data == NULL) {
    std::cout << "Pleace choose an existing image path\n";
    return -1; 
  }

  EventStruct* my_pane = new EventStruct;
  my_pane->threshold = 0;
  my_pane->sigma = 1.5;
  my_pane->image = img;
  cvtColor(img, my_pane->gray_scale, COLOR_BGR2GRAY);

  namedWindow("Threshold");

  createTrackbar("Min Threshold: ", "Threshold", nullptr, 100, trackBarChangeThreshold, (void*) my_pane);
  setTrackbarPos("Min Threshold: ", "Threshold", my_pane->threshold);

  createTrackbar("Sigma: ", "Threshold", nullptr, 100, trackBarChangeSigma, (void*) my_pane);
  setTrackbarPos("Sigma: ", "Threshold", my_pane->threshold);

  imshow("Threshold", my_pane->image);
  waitKey(0);

  delete(my_pane);
  return 0;
}