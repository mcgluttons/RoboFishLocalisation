/*
** Author: Justin Wolf
** Date: 17/10/2016
**
** File: myopencv
** Description:
*/



#include "myopencv.h"


int imageCount = 0;

/*
* Function: openVideoCapture
* Parameters: std::string
* Return: cv::VideoCapture
* Purpose: Open a stream to a camera and return it
*/
cv::VideoCapture openVideoCapture(std::string arg) {
	cv::VideoCapture capture(arg);
	if (!capture.isOpened()) {
		capture.open(std::stoi(arg));
		if (!capture.isOpened()) {
			std::cout << "Camera failed to open" << std::endl;
			exit(EXIT_FAILURE);
		}
		return capture;
	}
	return capture;
}

/*
* Function: createDisplay
* Parameters: std::string
* Return: void
* Purpose: create a display window
*/
void createDisplay(std::string windowName) {
	cv::namedWindow(windowName, CV_WINDOW_KEEPRATIO);
}

/*
* Function: displayFrame
* Parameters: std::string, cv::Mat
* Return: void
* Purpose: display the frame in a named window
*/
void displayFrame(std::string windowName, cv::Mat frame) {
	if (!frame.empty()) {
		cv::imshow(windowName, frame);
		cv::waitKey(5);
	}
}

/*
* Function: saveFrame
* Parameters: cv::Mat
* Return: void
* Purpose: save a frame to a png image
*/
void saveFrame(cv::Mat frame) {
	std::stringstream ss;
	ss << imageCount++;

	std::string filename = "capture.png";
	//	+  ss.str()
	//	+ ".png";
	cv::imwrite(filename, frame);
}

/*
* Function: createVideoWriter
* Parameters: cv::VideoCapture
* Return: cv::VideoWriter
* Purpose: create a video writer for a specific video capture
*/
cv::VideoWriter makeVideoWriter(cv::VideoCapture capture) {
	int frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter recorder("input_recording.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30, cv::Size(frame_width, frame_height), true);
	return recorder;
}

/*
* Function: saveFrameToVideo
* Parameters: cv::VideoWriter, cv::Mat
* Return: void
* Purpose: save a frame to a video file
*/
void saveFrameToVideo(cv::VideoWriter recorder, cv::Mat frame) {
	recorder.write(frame);
}

/*
* Function: openImage
* Parameters: char*
* Return: cv::Mat
* Purpose: Open an image
*          Return image if successful
*/
cv::Mat openImage(char* fileName) {
	cv::Mat image = cv::imread(fileName, CV_LOAD_IMAGE_COLOR);
	if (!image.data) {
		std::cout << fileName << " failed to open" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << fileName << " opened successfully" << std::endl;
		return image;
	}
}