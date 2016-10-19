/*
** File: imageprocessing.h
** Author: Justin Wolf
** Date:
** Description:
*/

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>

#include "opencv2/opencv.hpp"

#include "myopencv.h"
#include "colorprocessing.h"
#include "contourprocessing.h"


/*
******************************************* Method Declarations *******************************************
*/

void performManualColorThreshold(cv::Mat);
void testColorThreshold(cv::Mat);
void findContours(cv::Mat);
cv::Mat performColorThreshold(cv::Mat);

#endif // !IMAGEPROCESSING_H
