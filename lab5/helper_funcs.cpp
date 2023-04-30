#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

void processImageAsphalt(const Mat& img, Mat& dst, double sigma, int mean_thresh, int pixel_thresh) {
  Mat newImg = img.clone();
  equalizeHist(newImg, newImg);
  GaussianBlur(newImg, newImg, Size(7, 7), (double) sigma);

  Mat mean_processed(img.rows, img.cols, CV_8U);
  int radius = 3;
  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      if (i - radius < 0 || j - radius < 0 || i + radius >= img.rows || j + radius >= img.cols) {
        mean_processed.at<unsigned char> (i,j) = 0;
        continue;
      }
      Rect rect(j - radius, i - radius, (2*radius) + 1, (2*radius) + 1);
      Scalar mean = cv::mean(newImg(rect));
      unsigned char pixel = newImg.at<unsigned char> (i, j);
      if (mean[0] < mean_thresh && pixel < pixel_thresh) {
        mean_processed.at<unsigned char> (i, j) = 0;
      } else {
        mean_processed.at<unsigned char> (i, j) = 255;
      }
    }
  }

  mean_processed.copyTo(dst);
}

void processImageStreet(const Mat& img, Mat& dst) {
  Mat newImg = img.clone();
  GaussianBlur(newImg, newImg, Size(7, 7), 2.0);

  Mat sky_mask(img.rows, img.cols, CV_8UC3);
  Mat road_mask(img.rows, img.cols, CV_8UC3);

  int radius = 3;
  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      if (i - radius < 0 || j - radius < 0 || i + radius >= img.rows || j + radius >= img.cols) {
        sky_mask.at<Vec3b> (i,j) = Vec3b(0, 0, 0);
        continue;
      }
      Rect rect(j - radius, i - radius, (2*radius) + 1, (2*radius) + 1);
      Scalar mean = cv::mean(newImg(rect));

      // Road detection
      double max_ratio = std::max(mean[0] / mean[1], mean[0] / mean[2]);
      max_ratio = std::max(max_ratio, mean[1] / mean[0]);
      max_ratio = std::max(max_ratio, mean[1] / mean[2]);
      max_ratio = std::max(max_ratio, mean[2] / mean[0]);
      max_ratio = std::max(max_ratio, mean[2] / mean[1]);
      double magnitude = sqrt(pow(mean[0], 2) + pow(mean[1], 2) + pow(mean[2], 2));
      if (max_ratio < 1.15 && magnitude > 150) {
        road_mask.at<Vec3b> (i, j) = Vec3b(0, 0, 255);
      }

      // Sky detection
      double ratio = std::max(mean[0] / mean[1], mean[0] / mean[2]);
      // Not only you must hvae a high blue value, but also a high blue value compared to the other two
      if (mean[0] > 200 && ratio > 1.3) {
        sky_mask.at<Vec3b> (i, j) = Vec3b(255, 0, 0);
      }
    }
  }

  // Applying erosion on the mask just for the red pixels (road)
  int erosion_size = 3;
  Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
  erode(road_mask, road_mask, element);
  erode(road_mask, road_mask, element);

  // Copying the road mask to the sky mask
  for (int i = 0; i < sky_mask.rows; i++) {
    for (int j = 0; j < sky_mask.cols; j++) {
      if (road_mask.at<Vec3b> (i, j) == Vec3b(0, 0, 255)) {
        sky_mask.at<Vec3b> (i, j) = Vec3b(0, 0, 255);
      }
    }
  }

  sky_mask.copyTo(dst);
}

void processImageRobot(const Mat& img, Mat& dst) {
  Mat newImg = img.clone();
  GaussianBlur(newImg, newImg, Size(7, 7), 2.0);

  Mat robot_mask(img.rows, img.cols, CV_8UC3);

  // Filtering with average of a rect with 4 pixel of radius
  int radius = 4;
  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {

      if (i - radius < 0 || j - radius < 0 || i + radius >= img.rows || j + radius >= img.cols) {
        continue;
      }

      Rect rect(j - radius, i - radius, (2*radius) + 1, (2*radius) + 1);
      Scalar mean = cv::mean(newImg(rect));
      bool is_ordered = mean[0] < mean[1] && mean[1] < mean[2];
      double r_on_g = (mean[1] == 0) ? 100.0 : mean[2] / mean[1];
      if (is_ordered && r_on_g <= 1.7) {
        robot_mask.at<Vec3b> (i, j) = Vec3b(32, 240, 160);
      }
    }
  }



  // Eroding smaller particles
  int erosion_size = 5;
  Mat element = getStructuringElement(MORPH_CROSS, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
  erode(robot_mask, robot_mask, element);

  // Dilating
  int dilation_size = 2;
  Mat element2 = getStructuringElement(MORPH_ELLIPSE, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
  dilate(robot_mask, robot_mask, element2);

  // Copying the robot mask to the original image
  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {

      if (robot_mask.at<Vec3b> (i, j) != Vec3b(32, 240, 160)) {
        robot_mask.at<Vec3b> (i, j) = img.at<Vec3b> (i, j);
      }
    }
  }

  robot_mask.copyTo(dst);
}