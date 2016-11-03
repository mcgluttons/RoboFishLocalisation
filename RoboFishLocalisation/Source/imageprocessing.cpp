/*
** File: imageprocessing.cpp
** Author: Justin Wolf
** Date:
** Description:
*/



#include "imageprocessing.h"

/*
******************************************* Method Declarations (Color Method) *******************************************
*/

/*
* Function: testColorThreshold
* Parameters: cv::Mat
* Return: void
* Purpose: Displaying the results of the threshold set values
*/
void testColorThreshold(cv::Mat frame, int color) {
	cv::Mat thresh_frame;
	thresh_frame = colorThreshold(frame, color);
	displayFrame("Original", frame);
	displayFrame("Color Thresholded", thresh_frame);
}

/*
* Function: performColorThreshold
* Parameters: cv::Mat
* Return: cv::Mat
* Purpose:
*/
cv::Mat performColorThreshold(cv::Mat frame, int color) {
	cv::Mat thresh_frame;
	thresh_frame = colorThreshold(frame, color);
	return thresh_frame;
}

/*
* Function: performManualColorThreshold
* Parameters: cv::Mat
* Return: void
* Purpose: Allow manual color thresholding
*/
void performManualColorThreshold(cv::Mat frame) {
	cv::Mat thresh_frame;
	createColorTrackBars();
	thresh_frame = manualColorThreshold(frame);
	displayFrame("Original", frame);
	displayFrame("Color Thresholded", thresh_frame);
}

/*
******************************************* Method Declarations (Image Differencing Method) *******************************************
*/
cv::Mat frameSubtraction(cv::Mat frame1, cv::Mat frame2) {
	cv::Mat gray_frame1, gray_frame2, thresh_frame, diff_frame;
	gray_frame1 = convertToGREY(frame1);
	gray_frame2 = convertToGREY(frame2);
	cv::cvtColor(frame2, gray_frame2, CV_BGR2GRAY);
	cv::absdiff(gray_frame1, gray_frame2, diff_frame);
	//displayFrame("Difference Image", diff_frame);
	cv::threshold(diff_frame, thresh_frame, 20, 255, CV_THRESH_BINARY);
	//displayFrame("Threshold Image", thresh_frame);
	cv::blur(thresh_frame, thresh_frame, cv::Size(10, 10));
	cv::threshold(thresh_frame, thresh_frame, 20, 255, CV_THRESH_BINARY);
	//displayFrame("Blurred", thresh_frame);
	return thresh_frame;
}

/*
******************************************* Method Declarations (General Functions) *******************************************
*/

/*
* Function: findContours
* Parameters: cv::Mat
* Return: void
* Purpose: Allow manual color thresholding
*/
void findContourCenter(cv::Mat thresh_frame) {
	int x, y;
	std::vector<std::vector<cv::Point>> contours;
	contours = getFrameContours(thresh_frame);
	int index = findLargestContourIndex(contours);
	if (index != -1) {
		findContourCenter(contours[index], x, y);
		std::cout << "x: " << x << " y: " << y << std::endl;
	}
}

cv::Mat displayContours(cv::Mat frame, cv::Mat thresh_frame) {
	int x, y;
	std::vector<std::vector<cv::Point>> contours;
	contours = getFrameContours(thresh_frame);
	int index = findLargestContourIndex(contours);
	if (index != -1) {
		cv::drawContours(frame, contours, index, CV_RGB(255, 0, 255), 2);
		findContourCenter(contours[index], x, y);
		cv::putText(frame, "Fish at (" + std::to_string(x) + "," + std::to_string(y) + ")", cv::Point(x, y), 1, 1, CV_RGB(0, 255, 255), 2);
	}
	displayFrame("Contours", frame);
	return frame;
}