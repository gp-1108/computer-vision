#pragma once
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "EventStruct.hpp"

using namespace cv;

void trackBarChangeThreshold(int pos, void* userdata) {
  EventStruct* event = (EventStruct*) userdata;
  event->threshold = pos;

  // Adding blur
  Mat edges(event->image.rows, event->image.cols, CV_8U);
  GaussianBlur(event->gray_scale, edges, Size(5,5), event->sigma);

  // Processing canny image
  Canny(edges, edges, event->threshold, 3 * event->threshold, 3, false);

  // Processing hough lines
  std::vector<Vec2f> lines;
  HoughLines(edges, lines, 1, CV_PI/event->rads, event->hough, 0, 0);

  // Displaying hough lines [TODO]
  Mat hough_lines = event->image.clone();
  for (int i = 0; i < lines.size(); i++) {
    float rho = lines[i][0], theta = lines[i][1];
    Point a(0, static_cast<int>(rho / std::sin(theta)));
    Point b(static_cast<int>(rho / std::cos(theta)), 0);
    line(hough_lines, a, b, Scalar(0,0,255));
  }

  imshow("Threshold", hough_lines);

  return;
}

void trackBarChangeSigma(int pos, void* userdata) {
  EventStruct* event = (EventStruct*) userdata;
  event->sigma = pos;

  Mat edges(event->image.rows, event->image.cols, CV_8U);
  GaussianBlur(event->gray_scale, edges, Size(5,5), event->sigma);

  Canny(edges, edges, event->threshold, 3 * event->threshold, 3, false);

  std::vector<Vec2f> lines;
  HoughLines(edges, lines, 1, CV_PI/event->rads, event->hough, 0, 0);

  // Displaying hough lines [TODO]
  Mat hough_lines = event->image.clone();
  for (int i = 0; i < lines.size(); i++) {
    float rho = lines[i][0], theta = lines[i][1];
    Point a(0, static_cast<int>(rho / std::sin(theta)));
    Point b(static_cast<int>(rho / std::cos(theta)), 0);
    line(hough_lines, a, b, Scalar(0,0,255));
  }

  imshow("Threshold", hough_lines);

  return;
}

void trackBarChangeHough(int pos, void* userdata) {
  EventStruct* event = (EventStruct*) userdata;
  event->hough = pos;

  Mat edges(event->image.rows, event->image.cols, CV_8U);
  GaussianBlur(event->gray_scale, edges, Size(5,5), event->sigma);

  Canny(edges, edges, event->threshold, 3 * event->threshold, 3, false);

  std::vector<Vec2f> lines;
  HoughLines(edges, lines, 1, CV_PI/event->rads, event->hough, 0, 0);

  // Displaying hough lines [TODO]
  Mat hough_lines = event->image.clone();
  for (int i = 0; i < lines.size(); i++) {
    float rho = lines[i][0], theta = lines[i][1];
    Point a(0, static_cast<int>(rho / std::sin(theta)));
    Point b(static_cast<int>(rho / std::cos(theta)), 0);
    line(hough_lines, a, b, Scalar(0,0,255));
  }

  imshow("Threshold", hough_lines);
  return;
}

void trackBarChangeRads(int pos, void* userdata) {
  EventStruct* event = (EventStruct*) userdata;
  event->rads = pos;

  Mat edges(event->image.rows, event->image.cols, CV_8U);
  GaussianBlur(event->gray_scale, edges, Size(5,5), event->sigma);

  Canny(edges, edges, event->threshold, 3 * event->threshold, 3, false);

  std::vector<Vec2f> lines;
  HoughLines(edges, lines, 1, CV_PI/event->rads, event->hough, 0, 0);

  // Displaying hough lines [TODO]
  Mat hough_lines = event->image.clone();
  for (int i = 0; i < lines.size(); i++) {
    float rho = lines[i][0], theta = lines[i][1];
    Point a(0, static_cast<int>(rho / std::sin(theta)));
    Point b(static_cast<int>(rho / std::cos(theta)), 0);
    line(hough_lines, a, b, Scalar(0,0,255));
  }

  imshow("Threshold", hough_lines);
  return;
}