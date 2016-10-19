/*
** File: contourprocessing.h
** Author: Justin Wolf
** Date:
** Description: 
*/

#ifndef CONTOURPROCESSING_H
#define CONTOURPROCESSING_H

#include "opencv2\imgproc.hpp"
#include <iostream>

/*
******************************************* Method Declarations *******************************************
*/

std::vector<std::vector<cv::Point>> getFrameContours(cv::Mat);
int findLargestContourIndex(std::vector<std::vector<cv::Point>>);
std::vector<std::vector<cv::Point>> findContourByArea(std::vector<std::vector<cv::Point>>, double, double);
void findContourCenter(std::vector<cv::Point>, int&, int&);
cv::Point analyseThresholdedFrameContours(cv::Mat);




#endif CONTOURPROCESSING_H
