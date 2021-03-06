/*
** File: main.cpp
** Author: Justin Wolf
** Date: 04/11/16
** Description: main function for RoboFishLocalisation program
*/

#include <iostream>
#include <fstream>
#include "opencv2\imgproc.hpp"
#include "myopencv.h"
#include "imageprocessing.h"

cv::Point2d centroid1;
//cv::Point2d centroid2;

void help();
void mouseCallBack(int, int, int, int, void*);
void writeToFile(std::ofstream&, int, cv::Point2d);

int main(int argc, char** argv) {
	std::cout << "Use -h for a list of all possible settings." << std::endl;

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
	//cv::VideoCapture capture2;
	int frame1Count = 0;
	//int frame2Count = 0;

	for (int i = 1; i < argc; i++) {
		if (std::strcmp(argv[i], "-h") == 0) {
			help();
			return 1;
		}
		else if (std::strcmp(argv[i], "-d") == 0) {
			// perform image differencing
			diffDetection = true;
		}
		else if (std::strcmp(argv[i], "-t") == 0) {
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

	createDisplay("Window1");
	//createDisplay("Window2");

	cv::Mat frame1, frame2, frame3, frame4, binaryFrame1, binaryFrame2;
	std::ofstream outputFile1;
	//std::ofstream outputFile2;
	outputFile1.open("output1.txt");
	//outputFile2.open("output2.txt");
	while (1) {

		// check for ending of recorded input capture
		if (openRecording) {
			if (capture1.get(CV_CAP_PROP_POS_FRAMES) + 1 == capture1.get(CV_CAP_PROP_FRAME_COUNT) - 1) {
				return 1;
			}
		}

		if (diffDetection) {
			if (frame1Count != 0) {
				frame1 = frame3;
				//frame2 = frame4;
			}
			else {
				capture1 >> frame1;
				frame1Count++;
				//capture2 >> frame2;
				//frame2Count++;

				displayFrame("Window1", frame1);
				//displayFrame("Window2", frame2);

			}
		}
		else {
			capture1 >> frame1;
			frame1Count++;
			//capture2 >> frame2;
			//frame2Count++;

			displayFrame("Window1", frame1);
			//displayFrame("Window2", frame2);
		}

		if (recordInput) {
			saveFrameToVideo(inRecorder1, frame1);
			//saveFrameToVideo(inRecorder2, frame2);
		}

		if (manualCenterSelection) {
			centroid1.x = -1;
			centroid1.y = -1;

			displayFrame("Input", frame1);
			cv::setMouseCallback("Input", mouseCallBack, NULL);
			writeToFile(outputFile1, frame1Count, centroid1);
			char c = (char)cv::waitKey(0);
			if (c == 27) {
				break;
			}
			continue;
		}
		else if (diffDetection) {
			capture1 >> frame3;
			frame1Count++;
			//capture2 >> frame4;
			//frame2Count++;

			displayFrame("Window1", frame3);
			//displayFrame("Window2", frame4);

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
			getContourCenter(binaryFrame1, centroid1);
			//getContourCenter(binaryFrame2, centroid2);
			writeToFile(outputFile1, frame1Count, centroid1);
			//writeToFile(outputFile2, frame1Count, centroid2);
		}

		char c = (char)cv::waitKey(5);
		if (c == 27) {
			break;
		}

	} // end of while

	outputFile1.close();
	//outputFile2.close();

	return 1;
}

/*
* Function: help
* Parameters: N/A
* Return: void
* Purpose: Prints all operators for the RoboFishLocalisation program
*/
void help() {
	std::cout << "Please use the following list of commands for the RoboFishLocalistion System." << std::endl;
	std::cout << "Use -h for a list of all possible settings." << std::endl;
	std::cout << "Use -d to use the image differencing detection method." << std::endl;
	std::cout << "Use -w to specify whether a webcamera is built into your PC. 0 for no and 1 for yes." << std::endl;
	std::cout << "Use -r to open a video file. This must be followed by the file location." << std::endl;
	std::cout << "Use -l to show the input capture in a display window." << std::endl;
	std::cout << "Use -i to record the input capture." << std::endl;
	std::cout << "Use -o to record the output if drawing contours is enabled." << std::endl;
	std::cout << "Use -c to show the contouring of the captured frames." << std::endl;
	std::cout << "Use -t to perform manual color thresholding." << std::endl;
	std::cout << "Use -s to operate in a manual tracking mode." << std::endl;
}

/*
* Function: mouseCallBack
* Parameters: int, int, int, int, void*
* Return: void
* Purpose: Prints out the location of the mouse pointer in a frame on a left button press
*/
void mouseCallBack(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		centroid1.x = x;
		centroid1.y = y;
	}
}

void writeToFile(std::ofstream& outputFile, int frameCount, cv::Point2d centroid) {
	outputFile << "Frame " << frameCount << ": Coordinate(" << centroid.x << ", " << centroid.y << ")" << std::endl;
}


