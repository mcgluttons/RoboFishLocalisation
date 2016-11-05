/*
** File: imageprocessing.cpp
** Author: Justin Wolf
** Date: 03/11/16
** Description: Uses the lower level functions from contourprocessing and colorporcessing to link
**              together the needed functions to achieve tracking.
*/

/*
******************************************* Include Declarations ******************************************
*/

#include "imageprocessing.h"

/*
******************************************* Method Declarations (Color Method) *******************************************
*/

/*
* Function: testColorThreshold
* Parameters: cv::Mat
* Return: void
* Purpose: Displays the binary frame resulting from applying the defined threshold values
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
* Purpose: Applies the defined color thresholds and returns a binary image
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
* Purpose: Allow manual color thresholding uses the threshold values set by the trackbars
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

/*
* Function: frameSubtraction
* Parameters: cv::Mat, cv::Mat
* Return: cv::Mat
* Purpose: Finds the difference between two frames while applying some basi filters
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
* Function: findContourCenter
* Parameters: cv::Mat
* Return: cv::Point2d
* Purpose: Finds the centre of the contour in the binary image
*/
void getContourCenter(cv::Mat thresh_frame, cv::Point2d& centroid) {
	int x, y;
	std::vector<std::vector<cv::Point>> contours;
	contours = getFrameContours(thresh_frame);
	int index = findLargestContourIndex(contours);
	if (index != -1) {
		findContourCenter(contours[index], x, y);
		centroid.x = x;
		centroid.y = y;
	}
}

/*
* Function: displayContours
* Parameters: cv::Mat, cv::Mat
* Return: cv::Mat
* Purpose: Show tracking data on the input image
*/
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