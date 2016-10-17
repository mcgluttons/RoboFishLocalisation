#include <iostream>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\opencv.hpp"
#include "opencv2\imgproc.hpp"
#include "myopencv.h"

void help();
void localiseFish(cv::Mat);

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

		cv::Mat frame, diff_frame, thresh_frame;
		cv::Mat gray_frame1, gray_frame2;
		createDisplay("Difference Image");
		createDisplay("Threshold Image");
		createDisplay("Blurred");
		for (;;) {
			capture >> frame;
			cv::cvtColor(frame, gray_frame1, CV_BGR2GRAY);
			capture >> frame;
			cv::cvtColor(frame, gray_frame2, CV_BGR2GRAY);
			cv::absdiff(gray_frame1, gray_frame2, diff_frame);
			displayFrame("Difference Image", diff_frame);
			cv::threshold(diff_frame, thresh_frame, 20, 255, CV_THRESH_BINARY);
			displayFrame("Threshold Image", thresh_frame);
			cv::blur(thresh_frame, thresh_frame, cv::Size(10, 10));
			cv::threshold(thresh_frame, thresh_frame, 20, 255, CV_THRESH_BINARY);
			displayFrame("Blurred", thresh_frame);
			localiseFish(thresh_frame);
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

void localiseFish(cv::Mat thresh_frame) {
	cv::Mat local_frame;
	thresh_frame.copyTo(local_frame);

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(local_frame, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	if (contours.size() > 0) {
		std::cout << "contours found!!!" << std::endl;
		//for (int i = 0; i < contours.size(); i++) {
		//	std::cout << i << ": " << contours[i] << std::endl;
		//}
		
		std::vector<std::vector<cv::Point>> largestContour;
		largestContour.push_back(contours.at(contours.size() - 1));
		//std::cout << largestContour[0] << std::endl;
		cv::Rect boundingRectangle = cv::Rect(0, 0, 0, 0);
		boundingRectangle = cv::boundingRect(largestContour.at(0));
		int xpos = boundingRectangle.x + (boundingRectangle.width / 2);
		int ypos = boundingRectangle.y + (boundingRectangle.width / 2);

		cv::Scalar color = cv::Scalar(255, 0, 255);
		cv::rectangle(local_frame, boundingRectangle.tl(), boundingRectangle.br(), color, 2, 8, 0);
		displayFrame("rectangles", local_frame);
	}


}