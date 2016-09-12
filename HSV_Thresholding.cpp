#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

void HSV_Thresholding(Mat& Whale_HSV, Mat& Seg_Whale)
{
	for(int i=0; i<Whale_HSV.rows; i++)
	{
		for(int j=0; j<Whale_HSV.cols; j++)
		{
			uchar b = Whale_HSV.at<Vec3b>(i,j)[0];
			uchar g = Whale_HSV.at<Vec3b>(i,j)[1];
			uchar r = Whale_HSV.at<Vec3b>(i,j)[2];


			if(((g > 10) && (g < 60)) && ((b < 30) || (b > 107)) && ((r < 180) || (r > 220) ))
			{
				Seg_Whale.at<uchar>(i,j) = 255;
			}
			else
			{
				Seg_Whale.at<uchar>(i,j) = 0;
			}
		}
	}

	erode(Seg_Whale, Seg_Whale, Mat(), Size(-1, -1), 1);
	dilate(Seg_Whale, Seg_Whale, Mat(), Size(-1, -1), 7);
}