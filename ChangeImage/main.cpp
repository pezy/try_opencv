#include <stdio.h>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: ChangeImage <image path>\n");
    return -1;
  }
  
  cv::Mat image = cv::imread(argv[1]);
  if (!image.data) {
    printf("No image data!\n");
    return -1;
  }

  cv::Mat gray_image;
  cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
  imwrite("../Gray_Image.jpg", gray_image);
  
  cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
  cv::namedWindow("Gray Image", cv::WINDOW_NORMAL);

  cv::imshow("Display Image", image);
  cv::imshow("Gray Image", gray_image);

  cv::waitKey(0);

  return 0;
}