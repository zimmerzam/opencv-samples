#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <sstream>

using namespace cv;

int main( int argc, char** argv )
{

	for(int i = 1; i < argc; i++){
		// Import and show original image (binary)
    Mat src = imread(argv[i], 0);
		int value = 245;
		threshold( src, src, value, 255, THRESH_BINARY);
		
		namedWindow( "Original Image" , CV_WINDOW_NORMAL );
		imshow( "Original Image" , src );

		// Find contours
    Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours( src, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
//		std::cout << "I have found " << hierarchy.size() << " pieces of glass" << std::endl;

    // iterate through all the top-level contours,
    // draw each connected component with its own random color
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] ){
			Moments moment = moments(Mat(contours[idx]));
			Point barycenter(moment.m10/moment.m00, moment.m01/moment.m00);
			double area = contourArea(Mat(contours[idx]));
			double length = arcLength(Mat(contours[idx]),true);

			RotatedRect rect = minAreaRect( Mat(contours[idx]) );
			double minSize, maxSize;
			if(rect.size.height >= rect.size.width){
				maxSize = rect.size.height;
				minSize = rect.size.width;
			}
			else{
				minSize = rect.size.height;
				maxSize = rect.size.width;
			}

			vector<Point> approx;
			double epsilon = (2*area/length)/7;
			approxPolyDP( Mat(contours[idx]), approx, epsilon, true );
			std::cout << idx+1 << "\t" << area << "\t" << length << "\t" << minSize << "\t" << maxSize << "\t" << approx.size() << "\t" << barycenter.x << "\t" << barycenter.y << std::endl;

	    Scalar color( rand()&255, rand()&255, rand()&255 );
	    drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
//	    Scalar color1( 255, 255, 255 );
//			vector< vector<Point> > all_app; all_app.push_back(approx); 			
//	    drawContours( dst, all_app, -1, color1);
			circle(dst, barycenter, int(minSize/2.), 255, 2, 8, 0);
			circle(dst, barycenter, int(maxSize/2.), 255, 2, 8, 0);
    }
    namedWindow( "Control Image", CV_WINDOW_NORMAL );
    imshow( "Control Image", dst );
		stringstream index;
		index << i;
		imwrite( "processed_"+index.str()+".png", dst ); 
    waitKey(0);
	}

}
