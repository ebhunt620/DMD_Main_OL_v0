//This code was developed in November 2016 by Elizabeth E. Hunter at the
//University of Pennsylvania School of Engineering and Applied Science.
// ebeattie (at) seas (dot) upenn (dot) edu

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/nonfree/features2d.hpp>
# include "opencv2/nonfree/nonfree.hpp"

using namespace cv;
using namespace std;

int dmd_w, dmd_h, display_x, display_y;
int cam_w, cam_h;
Mat mask_im_dmd, mask_im_src;

int main() {
	//specify the size of the dmd
	dmd_w = 1024;
	dmd_h = 768;
	//MASK SOURCE IMAGE
  mask_im_src = imread("cam_img_mask.bmp");
  namedWindow("mask from user defined ROI",CV_WINDOW_AUTOSIZE);
  resize(mask_im_src, mask_im_src, Size(), 0.25, 0.25);
  imshow("mask from user defined ROI",mask_im_src);
  cam_w = mask_im_src.size().width;
  cam_h = mask_im_src.size().height;

  //Read in the homography matrix
 Mat h; // this is the matrix to store the transform
 FileStorage fs2("homography.xml",FileStorage::READ);
 fs2["homography"] >> h;
 fs2.release();
 cout << "Homography: " << h << endl;

 warpPerspective(mask_im_src, mask_im_dmd, h, Size(dmd_w,dmd_h));
 
  //open new window to hold mask image
  namedWindow( "warped_image_dmd", CV_WINDOW_AUTOSIZE);
  // Specify the position of the figure window. THIS IS SPECIFIC TO YOUR MAIN MONITOR.
  display_x = 0;
  display_y = 880;
  moveWindow("warped_image_dmd",display_x,display_y);
  imshow( "warped_image_dmd", mask_im_dmd);
  imwrite("mask_im_dmd.jpg",mask_im_dmd);
	//open new window to hold calibration (destination) image

  //Confirmation that camera mask and dmd mask are aligned: 
    Mat blend;
    double alpha = 0.5;
    double beta = ( 1.0 - alpha );
    Mat im_dmd = imread("dmd_calib_img.bmp");
    addWeighted( im_dmd, alpha, mask_im_dmd, beta, 0.0, blend);
    namedWindow("Cam2DMD and DMD Overlaid",CV_WINDOW_AUTOSIZE);
    imshow("Cam2DMD and DMD Overlaid",blend);
   
    //setWindowProperty("destination_img",CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
  
 
     

    waitKey(0); // displays the image indefinitely
  

return 0;
}