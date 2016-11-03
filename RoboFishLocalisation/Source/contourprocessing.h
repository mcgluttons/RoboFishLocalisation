/*
** File: contourprocessing.h
** Author: Justin Wolf
** Date: 03/11/16
** Description: Header file for contourprocessing.cpp
*/

#ifndef CONTOURPROCESSING_H
#define CONTOURPROCESSING_H

/*
******************************************* Include Declarations ******************************************
*/

#include "opencv2\imgproc.hpp"
#include <iostream>

/*
******************************************* Method Declarations *******************************************
*/

std::vector<std::vector<cv::Point>> getFrameContours(cv::Mat);
bool contoursExist(std::vector<std::vector<cv::Point>>);
std::vector<std::vector<cv::Point>> findContourByArea(std::vector<std::vector<cv::Point>>, double, double);
int findLargestContourIndex(std::vector<std::vector<cv::Point>>);
void findContourCenter(std::vector<cv::Point>, int&, int&);
cv::Mat drawContours(cv::Mat, std::vector<std::vector<cv::Point>>);

#endif CONTOURPROCESSING_H
