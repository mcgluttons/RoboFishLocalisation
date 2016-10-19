/*
** File: contourprocessing.cpp
** Author: Justin Wolf
** Date:
** Description:
*/

#include "contourprocessing.h"


#define MIN_AREA 10000
#define MAX_AREA 100000

std::vector<cv::Vec4i> hierarchy;

std::vector<std::vector<cv::Point>> getFrameContours(cv::Mat frame) {
	std::vector<std::vector<cv::Point>> contours;
	
	cv::findContours(frame, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	return contours;
}

bool contoursExist(std::vector<std::vector<cv::Point>> contours) {
	if (contours.size() != 0) {
		return true;
	}
	else {
		return false;
	}
}

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

void findContourCenter(std::vector<cv::Point> contour, int& x, int& y) {
	cv::Rect boundingRectangle = cv::boundingRect(contour);
	
	x = boundingRectangle.x + (boundingRectangle.width / 2);
	y = boundingRectangle.y + (boundingRectangle.width / 2);
}


/*
* Function: drawContours
* Parameters: cv::Mat, cv::vector<cv::vector<cv::Point>>, int
* Return:
* Purpose: Draw all contours
*/
cv::Mat drawContours(cv::Mat source_image, std::vector<std::vector<cv::Point>> contours) {
	cv::drawContours(source_image, contours, -1, CV_RGB(250, 255, 0), 2, 6, hierarchy);
	return source_image;
}

cv::Point analyseThresholdedFrameContours(cv::Mat thresh_frame) {
	int x, y;
	std::vector<std::vector<cv::Point>> profiles;
	std::vector<std::vector<cv::Point>> contours = getFrameContours(thresh_frame);
	if (contoursExist(contours)) {
		// find center of the contour that meets the area criteria
		profiles = findContourByArea(contours, MIN_AREA, MAX_AREA);
		if (profiles.size() > 0) {
			findContourCenter(profiles[0], x, y);
			cv::Point contourCenter = cv::Point(x, y);
			return contourCenter;
		}
	}
	return(cv::Point(0, 0));
}



