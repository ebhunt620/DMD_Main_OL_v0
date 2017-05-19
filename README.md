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

Cmake https://cmake.org/ Google for install instructions.

MATLAB R2016b (other versions will also work)
##########################################################
Instructions
0. Displaying an Image using DMD as Extended Display (2nd Monitor)
Open up a new terminal window. Navigate to the directory containing 'DisplayImageDMD.cpp' and make sure the CMakeLists.txt file is correct. Run:

ccmake .
make 

This should return an executable, which you can then run from your terminal by typing: 

./DisplayImageDMD

1. Running a new calibration 
Open up a new terminal window. Navigate to the directory 'calib_camToDMD' and make sure the CMakeLists.txt file is correct. Run:

ccmake .
make

This should return an executable, which you can then run from your termainal by typing: 

./calib_camToDMD
2. Creating a ROI (Mask) for Projection
Run 'dmd_util' from Matlab's command line. A GUI should appear with two figure axes and an array of push buttons. 
3. Displaying a ROI (Mask) for Projection

