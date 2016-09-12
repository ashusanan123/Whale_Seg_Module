#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



using namespace cv;
using namespace std;


void Find_Seg_Whale(Mat& Seg_Whale, Mat& Final_Segmented_Whale, Mat& Whale_Original)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours(Seg_Whale, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point> >hull( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    {  
    	convexHull( Mat(contours[i]), hull[i], false ); 
    }

    double max_area = 0;
    int max_index = 0;
    for( int i = 0; i< hull.size(); i++ )
    {
    	if(contourArea(hull[i]) > max_area)
    	{
    		max_area = contourArea(hull[i]);
    		max_index = i;
    	}
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        // drawContours( Whale_Original, contours, i, Scalar(0,255.0), 1, 8, vector<Vec4i>(), 0, Point() );
        // drawContours( Whale_Original, hull, i, Scalar(0,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
    }

    // drawContours( Whale_Original, hull, max_index, Scalar(0,0,255), 1, 8, vector<Vec4i>(), 0, Point() );

    RotatedRect box = cv::minAreaRect(hull[max_index]);

    cv::Point2f vertices[4];
    	box.points(vertices);

    	Mat Whale_Cropped;
    	Whale_Original.copyTo(Whale_Cropped);

    	for(int i = 0; i < 4; ++i)
    	{
    	cv::line(Whale_Original, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 0, 255), 1, CV_AA);
    	}

    	float box_angle = box.angle;
    	Size box_size = box.size;
    	Mat M, rotated, cropped;

    	if (box_angle < -45.0) 
    	{
    	box_angle += 90.0;
    	swap(box_size.width, box_size.height);
    }

    // get the rotation matrix
    M = getRotationMatrix2D(box.center, box_angle, 1.0);
    // perform the affine transformation
    warpAffine(Whale_Cropped, rotated, M, Whale_Cropped.size(), INTER_CUBIC);
    // crop the resulting image
    getRectSubPix(rotated, box_size, box.center, cropped);

    cropped.copyTo(Final_Segmented_Whale);
}