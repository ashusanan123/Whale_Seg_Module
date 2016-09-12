#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;


void HSV_Thresholding(Mat& , Mat& );
void Find_Seg_Whale(Mat& Seg_Whale, Mat& Final_Segmented_Whale, Mat& Whale_Original);