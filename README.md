# DMD_Main_OL_v0
This code was developed in November 2016 by Elizabeth E. Hunter at the University of Pennsylvania School of Engineering and Applied Science.

########################################################### 
Compatible OS:  
Ubuntu 14.04, 16.04  
OSX 10.11.6  
(Never tested with Windows, but should work in theory)  
##########################################################  
Required Packages: 
OpenCV http://opencv.org/ There are many online tutorials detailing how to install OpenCV. These tutorials are usually OS specific. Google accordingly.   

Cmake https://cmake.org/  
Google for install instructions.  
  
MATLAB R2016b (other versions will also work)  
##########################################################  
Instructions  
0. Displaying an Image using DMD as Extended Display (2nd Monitor)  
Open up a new terminal window. Navigate to the directory containing 'DisplayImageDMD.cpp' and make sure the CMakeLists.txt file is correct. Run:

ccmake .  
make    

This should return an executable, which you can then run from your terminal by typing: 

./DisplayImageDMD  
You might need or want to edit a few things in this file before compiling and running. (dmd_w,dmd_h) is the resolution of the image you want to project. (display_x,display_y) is the physical position you would like the display window to appear. Adjust this based on your monitor. Change the filename of the image you want to project. By default, it is set to 'dmd_calib_img.bmp'.  

1. Running a new calibration 
Open up a new terminal window. Navigate to the directory 'calib_camToDMD' and make sure the CMakeLists.txt file is correct. Run:

ccmake .  
make

This should return an executable, which you can then run from your termainal by typing: 

./calib_camToDMD  

Prior to running calib_camToDMD, we need to project a calibration image with the DMD and take a picture of it with our camera. Run ./DisplayImageDMD so that it projects 'dmd_calib_img.bmp'. Save the picture as 'cam_calib_img.jpg' and in the same directory as 'calib_camToDMD'  
  
* Run ./DisplayImageDMD with the projected image 'calibration_img.bmp'.
* Take a picture of this image with your camera and save the image as 'cam_calib_img.jpg' in the directory 'calib_camToDMD'.  
* Run ./calib_camToDMD  
* This program will output 'homography.txt' and a few image files which verify that your calibration worked properly. 
   
2. Creating a ROI (Mask) for Projection
Run 'dmd_util' from Matlab's command line. A GUI should appear with two figure axes and an array of push buttons. 

* Load Camera Image: Loads image taken with camera into axes1. 
* Single ROI: Select and Draw a Single ROI into axes1 (LHS figure axes).
* Multiple ROI: Select and Draw Multiple ROI into axes1 (LHS figure axes).
* Detect Edges: Currently does nothing. Function handle exists in dmd_util.m if you want to upgrade this function.
* Redraw: Erases everything from axes1.
* Intensity Adjustment: Adjusts the mask you drew and changes pixels between 0 and 255.
* Threshold Adjustment (Edges): Currently does nothing, but the function handle exists in dmd_util.m.
* Save DMD image: Image is saved to the current directoy as 'cam_img_mask.bmp'.

2.5. Creating a ROI (Mask) for Projection (CPP)
Compile the .cpp file into an executable as described in 0 and 1. Run ./SelectROIDMD. User input should be self-explanatory. Ouptut is a binary image containing the user selected mask.  

3. Displaying a ROI (Mask) for Projection
