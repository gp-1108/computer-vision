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
  for( size_t i = 0; i < lines.size(); i++ )
  {
     float rho = lines[i][0], theta = lines[i][1];
     Point pt1, pt2;
     double a = cos(theta), b = sin(theta);
     double x0 = a*rho, y0 = b*rho;
     pt1.x = cvRound(x0 + 10000*(-b));
     pt1.y = cvRound(y0 + 10000*(a));
     pt2.x = cvRound(x0 - 10000*(-b));
     pt2.y = cvRound(y0 - 10000*(a));
     line(hough_lines, pt1, pt2, Scalar(0,0,255));
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
  for( size_t i = 0; i < lines.size(); i++ )
  {
     float rho = lines[i][0], theta = lines[i][1];
     Point pt1, pt2;
     double a = cos(theta), b = sin(theta);
     double x0 = a*rho, y0 = b*rho;
     pt1.x = cvRound(x0 + 10000*(-b));
     pt1.y = cvRound(y0 + 10000*(a));
     pt2.x = cvRound(x0 - 10000*(-b));
     pt2.y = cvRound(y0 - 10000*(a));
     line(hough_lines, pt1, pt2, Scalar(0,0,255));
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
  for( size_t i = 0; i < lines.size(); i++ )
  {
     float rho = lines[i][0], theta = lines[i][1];
     Point pt1, pt2;
     double a = cos(theta), b = sin(theta);
     double x0 = a*rho, y0 = b*rho;
     pt1.x = cvRound(x0 + 10000*(-b));
     pt1.y = cvRound(y0 + 10000*(a));
     pt2.x = cvRound(x0 - 10000*(-b));
     pt2.y = cvRound(y0 - 10000*(a));
     line(hough_lines, pt1, pt2, Scalar(0,0,255));
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
  for( size_t i = 0; i < lines.size(); i++ )
  {
     float rho = lines[i][0], theta = lines[i][1];
     Point pt1, pt2;
     double a = cos(theta), b = sin(theta);
     double x0 = a*rho, y0 = b*rho;
     pt1.x = cvRound(x0 + 10000*(-b));
     pt1.y = cvRound(y0 + 10000*(a));
     pt2.x = cvRound(x0 - 10000*(-b));
     pt2.y = cvRound(y0 - 10000*(a));
     line(hough_lines, pt1, pt2, Scalar(0,0,255));
  }
  imshow("Threshold", hough_lines);
  
  return;
}