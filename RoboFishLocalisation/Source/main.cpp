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
	
	bool diffDetection = false;
	bool threshTesting = false;
	bool webCamera = false;
	bool camChecked = false;
	bool recordInput = false;
	cv::VideoCapture capture1;
	cv::VideoCapture capture2;

	help();
	
	for (int i = 1; i < argc - 1; i++) {
		if (std::strcmp(argv[i], "-d")) {
			// perform image differencing
			diffDetection = true;
		}
		else if (std::strcmp(argv[i], "-c")) {
			// perform color threshold testing
			threshTesting = true;
		}
		else if (std::strcmp(argv[i], "-o")) {
			// open recording as video capture
			capture1 = openVideoRecording(argv[i + 1]);
			i++;
		}
		else if (std::strcmp(argv[i], "-r")) {
			// record input capture
			recordInput = true;
		}
		else if (std::strcmp(argv[i], "-w")) {
			camChecked = true;
			// web camera or not
			if (std::stoi(argv[i]) != 0) {
				webCamera = true;
			}
			i++;
		}
		else if (std::strcmp(argv[1], "-h") == 0) {
			help();
		}
		else {
			std::cout << "Please type -h to see all possible commands." << std::endl;
			return 0;
		}
	}

	// webcamera parameter must be specified
	if (!camChecked) {
		std::cout << "Please specify whether there is a webcamera on your PC." << std::endl;
		return(0);
	}

	// capture.get(CV_CAP_PROP_POS_FRAMES) + 1 < capture.get(CV_CAP_PROP_FRAME_COUNT) - 1

	// start a live capture if a recorded one is not provided
	if (!capture1.isOpened) {
		if (!webCamera) {
			capture1 = openVideoCapture(0);
			capture2 = openVideoCapture(1);
		}
		else {
			capture1 = openVideoCapture(1);
			capture2 = openVideoCapture(2);
		}
	}

	if (diffDetection) {
		// do motion
	}
	else {
		// do color
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
	cv::Mat frame, thresh_frame, output;
	//cv::VideoWriter recorder = makeVideoWriter(capture, "output.avi");
	cv::VideoWriter recorder = makeVideoWriter(capture, "lalala");
	int imageCount = 0;
	while (capture.get(CV_CAP_PROP_POS_FRAMES) < capture.get(CV_CAP_PROP_FRAME_COUNT) - 1) {
		capture >> frame;
		if (!frame.empty()) {
			thresh_frame = performColorThreshold(frame);
			displayFrame("thresh", thresh_frame);
			output = findContours(frame, thresh_frame);
			saveFrameToVideo(recorder, thresh_frame);
			//saveFrameToVideo(recorder, output);
			//saveFrame(frame, imageCount);
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
	cv::VideoWriter recorder = makeVideoWriter(capture, "input.avi");
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

