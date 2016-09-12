#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Whale_Segmentation.h"
#include "opencv2/imgproc/imgproc.hpp"



using namespace cv;
using namespace std;


int main(int argc, char** argv)
{

    if(argc == 1)
    {
        cout<<"Error: Please enter the image path"<< endl;
        return -1;
    }
    //Input image
    Mat Whale_Original = imread(argv[1],1);
    cout<<"<---------Reading Image------------>"<< endl;
    if(!Whale_Original.data)
    {
    	cout<<"Image not read"<< endl;
    	return -1;
    }
    // resize(Whale_Original, Whale_Original, Size(500,500));

    cout<<"<----------------Segmenting the Whale------------------>"<< endl;
    //Convert to HSV
    Mat Whale_HSV;
    cvtColor(Whale_Original, Whale_HSV, CV_BGR2HSV);

    Mat Seg_Whale;
    Seg_Whale.create(Whale_HSV.rows, Whale_HSV.cols, CV_8UC1);


    //Custom tresholding
    HSV_Thresholding(Whale_HSV, Seg_Whale);

    Mat Final_Segmented_Whale;

    Find_Seg_Whale(Seg_Whale, Final_Segmented_Whale, Whale_Original);

    cout<<"<----------------------Segmentation Done------------------------>"<< endl;

    
    // imshow("Segmented", Seg_Whale);
    imshow("Segmentation_Output", Final_Segmented_Whale);
    imshow("Whale_Original", Whale_Original);
    waitKey(0);

    return 0;
}