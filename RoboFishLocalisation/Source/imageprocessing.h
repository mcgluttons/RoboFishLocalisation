/*
** File: imageprocessing.h
** Author: Justin Wolf
** Date: 03/11/2016
** Description: Header file for imageprocessing.cpp
*/

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

/*
******************************************* Include Declarations ******************************************
*/

#include <iostream>
#include "opencv2/opencv.hpp"
#include "myopencv.h"
#include "colorprocessing.h"
#include "contourprocessing.h"


/*
******************************************* Method Declarations *******************************************
*/

void performManualColorThreshold(cv::Mat);
void testColorThreshold(cv::Mat, int);
void findContourCenter(cv::Mat);
cv::Mat displayContours(cv::Mat, cv::Mat);
cv::Mat performColorThreshold(cv::Mat, int);
cv::Mat frameSubtraction(cv::Mat, cv::Mat);

#endif // !IMAGEPROCESSING_H
