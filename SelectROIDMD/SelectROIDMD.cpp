#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int cam_w, cam_h;
Point point;
Mat image;
vector<Point> contour;


void onmouse(int event, int x, int y, int flags, void* userdata)
{
    if(event==EVENT_LBUTTONDOWN)
    {


        //Mat &image = *((Mat*)(userdata)); // 1st cast it back, then deref
        point = Point(x, y);
        contour.push_back(point);

        circle(image,point,4,Scalar(0,255,0),-1,8,0); //draw the point that the user selected

        const Point *pts = (const Point*) Mat(contour).data;
		int numpts = Mat(contour).rows;
        polylines(image, &pts,&numpts, 1,
	    		false, 			// draw closed contour (i.e. joint end to start) 
	            Scalar(255,255,255),// colour RGB ordering (here = white) 
	    		3, 		        // line thickness
			    CV_AA, 0);
        
        imshow("input - click ROI - press enter when complete",image);
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
   		cout << "Stored point" << contour << endl;

    }
    
}


int main() {
    namedWindow("input - click ROI - press enter when complete",CV_WINDOW_AUTOSIZE);
    image = imread("Pim_test.bmp");
    //specify variables to hold size of camera image
    cam_w = image.size().width;
    cam_h = image.size().height;
    resize(image, image, Size(), 0.5, 0.5);
    setMouseCallback("input - click ROI - press enter when complete",onmouse, (void*)&contour); 
    imshow("input - click ROI - press enter when complete",image);
    //pass a pointer to `p` as parameter
    
    waitKey(0); // displays the image indefinitely

    // create a pointer to the data as an array of points (via a conversion to 
	// a Mat() object)

	const Point *contour_pts = (const Point*) Mat(contour).data;
	int npts = Mat(contour).rows;
    cout << "Number of points"<< npts << endl;

    namedWindow("output - Press any key to quit");
    Mat black(Size(cam_w, cam_h), CV_8UC3, Scalar(0, 0, 0));
    resize(black, black, Size(), 0.5, 0.5);
    polylines(black, &contour_pts,&npts, 1,
	    		true, 			// draw closed contour (i.e. joint end to start) 
	            Scalar(255,255,255),// colour RGB ordering (here = white) 
	    		3, 		        // line thickness
			    CV_AA, 0);
    fillPoly(black, &contour_pts,&npts,1,Scalar(255,255,255));
    resize(black, black, Size(), 2.0, 2.0);
    imshow("output - Press any key to quit",black);
    imwrite("cam_mask.jpg",black);
    waitKey(0);
	//Mat black(Size(dmd_w, dmd_h), CV_8UC3, Scalar(0, 0, 0));
    // p will update with new mouse-click image coordinates 
    // whenever user clicks on the image window 

return 0;
}