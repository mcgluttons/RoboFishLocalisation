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
void mouseCallBack(int, int, int, int, void*);

int main(int argc, char** argv) {

	bool diffDetection = false;
	bool threshTesting = false;
	bool openRecording = false;
	bool webCamera = false;
	bool camChecked = false;
	bool recordInput = false;
	bool recordOutput = false;
	bool showContours = false;
	bool manualCenterSelection = false;
	cv::VideoCapture capture1;
	cv::VideoCapture capture2;

	for (int i = 1; i < argc; i++) {
		if (std::strcmp(argv[i], "-h") == 0) {
			help();
			return 1;
		}
		else if (std::strcmp(argv[i], "-d") == 0) {
			// perform image differencing
			diffDetection = true;
		}
		else if (std::strcmp(argv[i], "-t") == 0) {    // need to implement
			// perform manual color thresholding
			threshTesting = true;
		}
		else if (std::strcmp(argv[i], "-r") == 0) {
			// open recording
			capture1 = openVideoRecording(argv[i + 1]);
			openRecording = true;
			i++;
		}
		else if (std::strcmp(argv[i], "-i") == 0) {
			// record input capture
			recordInput = true;
		}
		else if (std::strcmp(argv[i], "-o") == 0) {
			recordOutput = true;
		}
		else if (std::strcmp(argv[i], "-w") == 0) {
			// web camera or not
			camChecked = true;
			if (std::stoi(argv[i + 1]) != 0) {
				webCamera = true;
			}
			i++;
		}
		else if (std::strcmp(argv[i], "-c") == 0) {
			// show contouring 
			showContours = true;
		}
		else if (std::strcmp(argv[i], "-s") == 0) {
			// manual selection of center point
			if (openRecording) {
				manualCenterSelection = true;
			}
			else {
				std::cout << "Cannot be done on a live capture." << std::endl;
				std::cout << "Please use a recorded capture." << std::endl;
				return 1;
			}
			
		}
		else {
			std::cout << "Please type -h to see all possible commands." << std::endl;
			return 1;
		}
	}

	// webcamera parameter must be specified if a live capture is going to be used
	if (!camChecked && !openRecording) {
		std::cout << "Please specify whether there is a webcamera on your PC." << std::endl;
		return(0);
	}

	// start a live capture if a recorded one is not provided
	if (!capture1.isOpened()) {
		if (!webCamera) {
			capture1 = openVideoCapture(0); // camera 1
			//capture2 = openVideoCapture(1); // camera 2
		}
		else {
			capture1 = openVideoCapture(1); // camera 1
			//capture2 = openVideoCapture(2); // camera 2
		}
	}

	cv::VideoWriter inRecorder1 = makeVideoWriter(capture1, "input1.avi");
	cv::VideoWriter outRecorder1 = makeVideoWriter(capture1, "output1.avi");
	//cv::VideoWriter inRecorder2 = makeVideoWriter(capture2, "input2.avi");
	//cv::VideoWriter outRecorder2 = makeVideoWriter(capture2, "output2.avi");

	cv::Mat frame1, frame2, frame3, frame4, binaryFrame1, binaryFrame2;
	while (1) {
		if (openRecording) {
			if (capture1.get(CV_CAP_PROP_POS_FRAMES) + 1 == capture1.get(CV_CAP_PROP_FRAME_COUNT) - 1) {
				return 1;
			}
		}
		capture1 >> frame1;
		//capture2 >> frame2;
		if (recordInput) {
			saveFrameToVideo(inRecorder1, frame1);
			//saveFrameToVideo(inRecorder2, frame2);
		}
		if (manualCenterSelection) {
			displayFrame("Input", frame1);
			cv::setMouseCallback("Input", mouseCallBack, NULL);

			char c = (char)cv::waitKey(0);
			if (c == 27) {
				break;
			}
			continue;
		}
		else if (diffDetection) {
			capture1 >> frame3;
			//capture2 >> frame4;
			if (recordInput) {
				saveFrameToVideo(inRecorder1, frame3);
				//saveFrameToVideo(inRecorder2, frame4);
			}
			binaryFrame1 = frameSubtraction(frame1, frame3);
			//binaryFrame2 = frameSubtraction(frame2, frame4);
		}
		else {
			// color detection
			if (!threshTesting) {
				binaryFrame1 = performColorThreshold(frame1, YELLOW1);
				//binaryFrame2 = performColorThreshold(frame2, YELLOW2);
			}
			else {
				performManualColorThreshold(frame1);
				char c = (char)cv::waitKey(5);
				if (c == 27) {
					break;
				}
				continue;
			}
		}
		if (showContours) {
			displayContours(frame1, binaryFrame1);
			//displayContours(frame2, binaryFrame2);
			if (recordOutput) {
				saveFrameToVideo(outRecorder1, frame1);
				//saveFrameToVideo(outRecorder2, frame2);
			}
		}
		else {
			findContourCenter(binaryFrame1);
			//findContourCenter(binaryFrame2);
		}

	} // end of while

	return 1;
}

void help() {
	std::cout << "Please use the following list of commands for the RoboFishLocalistion System." << std::endl;
	// add all commands with descriptions
}

void mouseCallBack(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
	}
	
}


