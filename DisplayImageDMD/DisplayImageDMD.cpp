#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/nonfree/features2d.hpp>
# include "opencv2/nonfree/nonfree.hpp"

using namespace cv;
using namespace std;

// Elizabeth E. Hunter | University of Pennsylvania
// November 2016
// To run this function, navigate to its directory and run DisplayImage <imagename>.jpg
// This is a routine which loads an image into a new figure window.
// The figure is then placed at a location such that when a DMD is used in extended display mode...
// the image will be projected by the DMD.
int dmd_w, dmd_h, display_x, display_y;
Mat dst, dst_gray;


int main() {
    //specify the size of the dmd image
    dmd_w = 1024;
    dmd_h = 768;
    //CALIBRATION DESTINATION IMAGE
    //open new window to hold calibration (destination) image
    namedWindow("destination_img",CV_WINDOW_FULLSCREEN);
    // Specify the position of the figure window. THIS IS SPECIFIC TO YOUR MAIN MONITOR.
    display_x = 0;
    display_y = 880; 
    moveWindow("destination_img",0, 880);
    resizeWindow("destination_img", dmd_w, dmd_h);
    // Specify the image you want to display. CHANGE THIS TO YOUR DESIRED IMAGE.
    dst = imread("calibration_img.bmp");
    cvtColor( dst, dst_gray, CV_BGR2GRAY ); //convert to grayscale
    imshow("destination_img",dst_gray); //show destination image on the screen
    
    waitKey(0); 
    // press any key to stop
    destroyAllWindows();
    return 0;
}

