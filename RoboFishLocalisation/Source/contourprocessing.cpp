/*
** File: contourprocessing.cpp
** Author: Justin Wolf
** Date: 03/11/13
** Description: Uses opencv's contour functionality to obtain and analyse the contours of binary frames.
*/

/*
******************************************* Include Declarations ******************************************
*/

#include "contourprocessing.h"

/*
****************************************** Variable Declarations ******************************************
*/
#define MIN_AREA 10000
#define MAX_AREA 100000

std::vector<cv::Vec4i> hierarchy;

/*
****************************************** Method Implementations ******************************************
*/

/*
** Function: getFrameContours
** Parameters: cv::Mat
** Return: std::vector<std::vector<cv::Point>>
** Purpose: Get all the contours from a frame
*/
std::vector<std::vector<cv::Point>> getFrameContours(cv::Mat frame) {
	std::vector<std::vector<cv::Point>> contours;
	
	cv::findContours(frame, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	return contours;
}

/*
** Function: contoursExist
** Parameters: std::vector<std::vector<cv::Point>>
** Return: bool
** Purpose: Checks if even contours were found
*/
bool contoursExist(std::vector<std::vector<cv::Point>> contours) {
	if (contours.size() != 0) {
		return true;
	}
	else {
		return false;
	}
}

/*
** Function: findContourByArea
** Parameters: std::vector<std::vector<cv::Point>>, double, double
** Return: std::vector<std::vector<cv::Point>>
** Purpose: Find all contours within the vector of contours that match the area restrictions
*/
std::vector<std::vector<cv::Point>> findContourByArea(std::vector<std::vector<cv::Point>> contours, double minArea, double maxArea) {
	int desiredContourIndex;
	std::vector<std::vector<cv::Point>> desiredContour;
	for (int i = 0; i < contours.size(); i++) {
		double contourArea = cv::contourArea(contours[i], false);
		if (contourArea >= minArea && contourArea <= maxArea) {
			desiredContourIndex = i;
			desiredContour.push_back(contours[i]);
			break;
		}
	}
	return desiredContour;
}

/*
** Function: findLargestContourIndex
** Parameters: std::vector<std::vector<cv::Point>>
** Return: int
** Purpose: Finds the largest contour in a vector of contours
*/
int findLargestContourIndex(std::vector<std::vector<cv::Point>> contours) {
	int largestContourIndex;
	double largestArea = 0;
	std::vector<std::vector<cv::Point>> desiredContour;
	if (contours.size() != 0) {
		for (int i = 0; i < contours.size(); i++) {
			double contourArea = cv::contourArea(contours[i], false);
			if (contourArea > largestArea) {
				largestArea = contourArea;
				largestContourIndex = i;
			}
		}
	}
	if (largestArea > 1200) {
		return largestContourIndex;
	}
	else {
		return -1;
	}
}

/*
** Function: findContourCenter
** Parameters: std::vector<cv::Point>, int&, int&
** Return: void
** Purpose: Draws a bounding rectangle around the contour and then finds the centre of this rectangle.
*/
void findContourCenter(std::vector<cv::Point> contour, int& x, int& y) {
	cv::Rect boundingRectangle = cv::boundingRect(contour);
	
	x = boundingRectangle.x + (boundingRectangle.width / 2);
	y = boundingRectangle.y + (boundingRectangle.width / 2);
}


/*
** Function: drawContours
** Parameters: cv::Mat, cv::vector<cv::vector<cv::Point>>
** Return: cv::Mat
** Purpose: Draw all contours
*/
cv::Mat drawContours(cv::Mat source_image, std::vector<std::vector<cv::Point>> contours) {
	cv::drawContours(source_image, contours, -1, CV_RGB(250, 255, 0), 2, 6, hierarchy);
	return source_image;
}



