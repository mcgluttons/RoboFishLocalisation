/*
** File: main.cpp
** Author: Justin Wolf
** Date:
** Description:
*/

#include <iostream>
#include "opencv2\imgproc.hpp"
#include "myopencv.h"
#include "imageprocessing.h"

void help();
void processCaptureMotion(cv::VideoCapture);
void processRecCaptureColor(cv::VideoCapture);
void recordInputCapture(cv::VideoCapture);
void getColorThresholdValues(cv::VideoCapture);
void getContourAreaValues(cv::VideoCapture);

int main(int argc, char** argv) {
	help();
	// select what the input type will be
	if (argc < 2) { // argv[0] will be executable name
		std::cout << "Please use a valid command following the program executable." << std::endl;
		return 0;
	}
	if (std::strcmp(argv[1], "-cap") == 0) {
		// open a live capture and do real time processing
	}
	else if (std::strcmp(argv[1], "-vid") == 0) {
		// open an existing video file
		cv::VideoCapture capture = openVideoCapture(argv[2]);

		while (capture.get(CV_CAP_PROP_POS_FRAMES) + 1 < capture.get(CV_CAP_PROP_FRAME_COUNT) - 1) {
			// do the processing
		}
	}
	else if (std::strcmp(argv[1], "-test") == 0) {
		// test color filtering instead of image differences
		cv::VideoCapture capture = openVideoCapture(argv[2]);
		//getColorThresholdValues(capture);
		processRecCaptureColor(capture);
	}
	else if (std::strcmp(argv[1], "-rec") == 0) {
		// open video stream, display frame to user, and save frames to new video file
		cv::VideoCapture capture = openVideoCapture(argv[2]);
		recordInputCapture(capture);
	}
	else if (std::strcmp(argv[1], "-help") == 0) {
		help();
	}
	else {
		std::cout << "Please type -help to see all possible commands." << std::endl;
		return 0;
	}
	return 1;
}

void help() {
	std::cout << "Please use the following list of commands for the RoboFishLocalistion System." << std::endl;
	// add all commands with descriptions
}

void processCaptureMotion(cv::VideoCapture capture) {
	
}

void processRecCaptureColor(cv::VideoCapture capture) {
	cv::Mat frame;

	while (capture.get(CV_CAP_PROP_POS_FRAMES) < capture.get(CV_CAP_PROP_FRAME_COUNT) - 1) {
		capture >> frame;
		if (!frame.empty()) {
			findContours(frame);
		}
		else {
			break;
		}
		
		char c = (char)cv::waitKey(5);
		if (c == 27) {
			break;
		}
	}
}

void recordInputCapture(cv::VideoCapture capture) {
	cv::VideoWriter recorder = makeVideoWriter(capture);
	cv::Mat frame;
	createDisplay("Output");
	while (1) {
		capture >> frame;
		saveFrameToVideo(recorder, frame);
		displayFrame("Output", frame);
		char c = (char)cv::waitKey(5);
		if (c == 27) {
			break;
		}
	}
}

void getColorThresholdValues(cv::VideoCapture capture) {
	cv::Mat frame;
	capture >> frame;

	while (1) {
		performManualColorThreshold(frame);
		char c = (char)cv::waitKey(5);
		if (c == 27) {
			break;
		}
		else if (c == 32) {
			for (int i = 0; i < 100; i++) {
				capture >> frame;
			}
		}
	}
}

