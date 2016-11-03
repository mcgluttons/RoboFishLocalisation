/*
** File: colorprocessing.h
** Author: Justin Wolf
** Date: 03/11/16
** Description: Header file for colorprocessing.cpp
*/

#ifndef COLORPROCESSING_H
#define COLORPROCESSING_H

/*
******************************************* Include Declarations ******************************************
*/
#include <iostream>

#include "opencv2/opencv.hpp"

/*
****************************************** Constants Declarations ******************************************
*/

const int RED = 0;
const int YELLOW1 = 1;
const int WHITE = 2;
const int BLUE = 3;
const int GREEN = 4;
const int YELLOW2 = 5;

/*
******************************************* Method Declarations *******************************************
*/
cv::Mat convertToHSV(cv::Mat);
cv::Mat convertToGREY(cv::Mat);
cv::Mat colorThreshold(cv::Mat, int);
cv::Mat manualColorThreshold(cv::Mat);
void createColorTrackBars();

#endif
