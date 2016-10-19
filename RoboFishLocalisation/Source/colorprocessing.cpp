/*
* File: colorprocessing.cpp
* Author: Justin Wolf
* Date:
*
* Description: Uses opencv's color detection and modification features to allow an image to be thresholded
*              by its color.
*/

/*
******************************************* Include Declarations ******************************************
*/

#include "colorprocessing.h"


/*
****************************************** Variable Declarations ******************************************
*/

int iLowH = 0;
int iHighH = 179;
int iLowS = 0;
int iHighS = 255;
int iLowV = 0;
int iHighV = 255;

/*
****************************************** Method Implementations ******************************************
*/

/*
* Function: convertToHSV
* Parameters: cv::Mat
* Return: cv::Mat
* Purpose: BGR to HSV converter
*/
cv::Mat convertToHSV(cv::Mat image) {
	cv::Mat hsv_image;
	cv::cvtColor(image, hsv_image, CV_BGR2HSV);
	//std::cout << "Successfully converted BGR image to HSV image" << std::endl;
	return hsv_image;
}

/*
* Function: convertToGREY
* Parameters: cv::Mat
* Return: cv::Mat
* Purpose: BGR to Greyscale converter
*/
cv::Mat convertToGREY(cv::Mat image) {
	cv::Mat grey_image;
	cv::cvtColor(image, grey_image, CV_BGR2GRAY);
	//std::cout << "Successfully converted BGR image to Greyscale image" << std::endl;
	return grey_image;
}

/*
* Function: colorThreshold
* Parameters: cv::Mat, int
* Return: cv::Mat
* Purpose: Converts image from BGR to HSV and then creates a binary image based on color thresholds
*/
cv::Mat colorThreshold(cv::Mat image, int color_threshold) {
	cv::Mat hsv_image, threshold_image, lower_red, upper_red;
	hsv_image = convertToHSV(image);

	switch (color_threshold) {
	case RED:
		inRange(hsv_image, cv::Scalar(0, 40, 0), cv::Scalar(40, 120, 100), lower_red);
		inRange(hsv_image, cv::Scalar(160, 140, 120), cv::Scalar(255, 255, 255), upper_red);
		addWeighted(lower_red, 1.0, upper_red, 1.0, 0.0, threshold_image);
		break;
	case YELLOW:
		inRange(hsv_image, cv::Scalar(0, 138, 115), cv::Scalar(53, 255, 255), threshold_image);
		break;
	case WHITE:
		inRange(hsv_image, cv::Scalar(11, 12, 142), cv::Scalar(40, 80, 170), threshold_image);
		break;
	case BLUE:
		inRange(hsv_image, cv::Scalar(75, 75, 75), cv::Scalar(120, 255, 255), threshold_image);
		break;
	case GREEN:
		inRange(hsv_image, cv::Scalar(45, 50, 0), cv::Scalar(100, 255, 255), threshold_image);
		break;
	}
	return threshold_image;
}

/*
* Function: applyAdjustedColorThreshold
* Parameters: cv::Mat
* Return: cv::Mat
* Purpose: Converts image to HSV
*          Thresholds image based on values obtained from the trackbars
*          Returns binary image
*/
cv::Mat manualColorThreshold(cv::Mat image) {
	cv::Mat hsv_image, imageThresholded;
	hsv_image = convertToHSV(image);
	inRange(hsv_image, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imageThresholded);
	return imageThresholded;
}

/*
* Function: createColorTrackBars
* Parameters: N/A
* Return: void
* Purpose: Create the trackbars to allow thresholding of an HSV image
*/
void createColorTrackBars() {

	cv::namedWindow("Color Thresholds", CV_WINDOW_AUTOSIZE);

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Color Thresholds", &iLowH, 179); // Hue (0 - 179)
	cvCreateTrackbar("HighH", "Color Thresholds", &iHighH, 179);
	cvCreateTrackbar("LowS", "Color Thresholds", &iLowS, 255); // Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Color Thresholds", &iHighS, 255);
	cvCreateTrackbar("LowV", "Color Thresholds", &iLowV, 255); // Value (0 - 255)
	cvCreateTrackbar("HighV", "Color Thresholds", &iHighV, 255);
}






