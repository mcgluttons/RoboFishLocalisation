#include <iostream>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\opencv.hpp"
#include "myopencv.h"

void help();

int main(int argc, char** argv) {
	help();
	// select what the input type will be
	if (argc < 2) { // argv[0] will be executable name
		std::cout << "Please use a valid command following the program executable." << std::endl;
		return 0;
	}
	if (std::strcmp(argv[1], "-vid") == 0) {
		
		// open video stream, display frame to user, and save frames to new video file
		cv::VideoCapture capture = openVideoCapture(argv[2]);
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
		return 1;
	}
	else if (std::strcmp(argv[1], "-frame") == 0) {
		// open single frame from video stream
	}
	else if (std::strcmp(argv[1], "-test") == 0) {
		
		cv::VideoCapture capture = openVideoCapture(argv[2]);

		cv::Mat frame;
		for (;;) {
			capture >> frame;
			cv::Mat gray_frame;
			cv::cvtColor(frame, gray_frame, CV_BGR2GRAY);
		}

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