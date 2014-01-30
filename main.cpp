/* 
 * File:   main.cpp
 * Author: markvandermerwe
 *
 * Created on January 23, 2014, 6:06 PM
 */
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <cstdlib>

using namespace std;
using namespace cv;

/*
 * 
 */


int main(int argc, char** argv) {

    //float height, width;
    Mat img;
    cvCapture* capture = 0;//Creates a new capture object for capturing the image.
    capture = cvCaptureFromCAM(0);//Captures image from the camera.
    if(!capture) <<cout "No camera detected. No image captured.\n";//Lets the user know no image was captured.
    
    if(capture)
    {
        Iplimage* iplImg = cvQueryFrame(capture);//Takes the captured image and places it into iplImg.
        img = iplImg;//Sets img equal to the image from capture.
        namedWindow("NEWIMAGE",CV_WINDOW_AUTOSIZE);//Creates window.
        imshow("NEWIMAGE",img);//Puts image into window and displays it.
        waitKey(0);//Waits for keystroke.
        destroyWindow("NEWIMAGE");//Gets rid of the window.
        double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
        double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
        cout << "Frame size : " << dWidth << " x " << dHeight << endl;

        /*
        //Next we are going to find countors and if anything has more or less than 4 get rid of it.
        CvSeq* countors;//Sets pointer to countor within storage.
        CvSeq* result;//Sets pointer to result sequence.
        CvMemStorage *storage = cvCreateMemStorage(0);//Creates a storage area for countors.
        //This finds the separate countors.
        cvFindCountors(img,storage,&countors,sizeof(CVCountor),CV_RETR_LIST,CV_CHAIN_APPROX_NONE,cvPoint(0,0));
        
        while(countors)
        {
            result = ApproxPoly(countors, sizeof(CVCountor),storage,CV_POLY_APPROX_DP,)//Obtain sequence of countors.
                    
            if(result->total == 4)//This tests to make sure it is a square.
            {
                CvPoint *pt[4];
                for(int i=0;i<4;i++)
                {
                    pt[i]=(cvPoint*)cvGetSeqElement(result,i);
                }//Sets points equal.
                
                <<cout "Point one: " + *pt[0];
                <<cout "Point two: " + *pt[1];
                <<cout "Point three: " + *pt[2];
                <<cout "Point four: " + *pt[3];
                
            }
        }*/
    }
    return 0;
}

