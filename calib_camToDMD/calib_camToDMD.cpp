//This code was developed in November 2016 by Elizabeth E. Hunter at the
//University of Pennsylvania School of Engineering and Applied Science.
// ebeattie (at) seas (dot) upenn (dot) edu

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
# include "opencv2/core/core.hpp"
# include "opencv2/features2d/features2d.hpp"
# include "opencv2/highgui/highgui.hpp"
# include "opencv2/nonfree/nonfree.hpp"

using namespace cv;
using namespace std;

int dmd_w, dmd_h, points_per_colum, points_per_row,display_x, display_y;
Mat dst, dst_gray, src, src_gray;
vector<Point2f> dst_corners, src_corners, pts_src, pts_dst;

int main() {
	//specify the size of the dmd
	dmd_w = 1024;
	dmd_h = 768;
	//CALIBRATION DESTINATION IMAGE
	//open new window to hold calibration (destination) image
  //This should be a checkerboard image projected to the DMD
  //The DMD is used as a 2nd (extended display) monitor
  // Specify the position of the figure window. THIS IS SPECIFIC TO YOUR MAIN MONITOR.
    display_x = 0;
    display_y = 880; 
    namedWindow("destination_img",CV_WINDOW_FULLSCREEN);
    moveWindow("destination_img",display_x, display_y);
    resizeWindow("destination_img", dmd_w, dmd_h);
    //setWindowProperty("destination_img",CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    // Specify the image you want to display. CHANGE THIS TO YOUR DESIRED IMAGE.
    dst = imread("dmd_calib_img.bmp");
    cvtColor( dst, dst_gray, CV_BGR2GRAY ); //convert to grayscale
    imshow("destination_img",dst_gray); //show destination image on the screen
    

  /// Copy the destination (dmd) image
  Mat copy_dst;
  copy_dst = dst.clone();

// Apply corner detection on destination (DMD) image
points_per_row = 9;
points_per_colum = 13;
Size patternSize = Size(points_per_row,points_per_colum);
findChessboardCorners(dst_gray, patternSize, dst_corners);
  

// WRITE DETECTED CORNERS IN DESTINATION IMAGE TO TEXT FILE
	// std::fstream outfile("dst_corners.txt", std::fstream::out);
 //  outfile <<  dst_corners << std::endl;
 //  outfile.close();


  /// Draw corners detected
  cout<<"** Number of corners detected: "<<dst_corners.size()<<endl;

  for( int i = 0; i < dst_corners.size(); i++ )
     { circle( copy_dst, dst_corners[i], 4, Scalar(0,0,255), -1, 8, 0 ); }

  /// Show what you got
  namedWindow( "detected_dst_corners", CV_WINDOW_AUTOSIZE );
  imshow( "detected_dst_corners", copy_dst );
  imwrite("detected_dst_corners.jpg",copy_dst);
  //CALIBRATION SOURCE IMAGE (FROM CAMERA)
	//open new window to hold camera (source) image
    namedWindow("source_img",CV_WINDOW_AUTOSIZE);
    src = imread("cam_calib_img.jpg");
    resize(src, src, Size(), 0.25, 0.25);
    cvtColor( src, src_gray, CV_RGB2GRAY ); //convert to grayscale
    imshow("source_img",src_gray); //show source (camera) image on the screen

    /// Copy the source (camera) image
	Mat copy_src;
  	copy_src = src.clone();

  	/// Apply corner detection
  findChessboardCorners(src_gray, patternSize, src_corners);
// WRITE DETECTED CORNERS IN CAMERA IMAGE TO TEXT FILE
	// std::fstream outfile("src_corners.txt", std::fstream::out);
 //  outfile <<  src_corners << std::endl;
 //  outfile.close();

  cout<<"** Number of corners detected: "<<src_corners.size()<<endl;

  for( int i = 0; i < src_corners.size(); i++ )
     { circle( copy_src, src_corners[i], 4, Scalar(0,0,255), -1, 8, 0 ); }

  /// Show what you got
  namedWindow( "detected_src_corners", CV_WINDOW_AUTOSIZE );
  //resize(copy_src, copy_src_rsz,Size(), 0.5,0.5);
  imshow( "detected_src_corners", copy_src );
  imwrite("detected_src_corners.jpg",copy_src);
  // pts_src and pts_dst are vectors of points in the source (camera) and
  // destination (dmd) iamges. They are of the type vector<Point2f>. We need
  // at least 4 corresponding points.
  pts_dst = dst_corners;
  pts_src = src_corners;


  //draw the results; 
  // namedWindow("matches",1);
  // Mat img_matches;
  // drawMatches(dst_gray, keypoints1, src_gray, keypoints2, matches, img_matches);
  // imshow("matches",img_matches);

  Mat h = findHomography(pts_src, pts_dst);
  //Mat h = getAffineTransform(pts_src, pts_dst);
// WRITE HOMOGRAPHY MATRIX TO TEXT FILE
	// std::fstream outfile("homography.txt", std::fstream::out);
 //   outfile <<  h << std::endl;
 //   outfile.close();
  FileStorage fs("homography.xml",FileStorage::WRITE);
  fs << "homography" << h;
  fs.release();

  //The calculated homography can be used to warp the source image to the
  //destination. im_src and im_dst  are of type Mat. Size is the size (width,
  //height) of im_dst.  This is a check to make sure that the homography is
  //valid. Warp the camera image to the dmd.   The output should be a window
  //displaying the same image that is being  projected to the dmd.
 Mat im_dmd, im_src, im_show;
 im_src = src;
  warpPerspective(im_src, im_dmd, h, Size(dmd_w,dmd_h));

  namedWindow( "cam2dmd_warped", CV_WINDOW_AUTOSIZE );
 
  imshow( "cam2dmd_warped", im_dmd);
  imwrite("cam2dmd_warped.jpg",im_dmd);

  waitKey(0); // displays the image indefinitely // press any key to end
  

return 0;
}