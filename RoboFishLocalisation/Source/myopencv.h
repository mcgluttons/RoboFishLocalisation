#ifndef MYOPENCV_H
#define MYOPENCV_H

#include <iostream>
#include <string>
#include "opencv2\highgui\highgui.hpp"



cv::VideoCapture openVideoCapture(std::string);
void createDisplay(std::string);
void displayFrame(std::string, cv::Mat);
void saveFrame(cv::Mat);
cv::VideoWriter makeVideoWriter(cv::VideoCapture);
void saveFrameToVideo(cv::VideoWriter, cv::Mat);
cv::Mat openImage(char*);

#endif // !MYOPENCV_H

