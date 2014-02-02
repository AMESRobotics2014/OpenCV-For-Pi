#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/photo/photo.hpp"
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
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
char key;
//int counter = 0;
//const char* name;

//Hey ALi- we can access the points through pt[1]->x and pt[1]->y. I will try to set up some basic code on the issue tonight.

double TAPELIMIT = 50;
double VERTICALLIMIT = 50;
double LRLimit = 50;

struct Scores {
   double rectangularity;
double aspectRatioVertical;
double aspectRatioHorizontal;
};

struct TargetReport {
int verticalIndex;
int horizontalIndex;
bool hot;
double totalScore;
double leftScore; 
double rightScore;
double tapeWidthScore;
double verticalScore;
};

int main()
{
  
   cvNamedWindow("Camera_Output2", 1);
   CvCapture* capture = cvCaptureFromCAM(0);
   do
   {
	IplImage* frame = cvQueryFrame(capture);
	IplImage* gray = cvCreateImage(cvGetSize(frame),8,1);
	CvSeq* contours;
	CvSeq* result;
	CvMemStorage* storage = cvCreateMemStorage(0);
	//cvShowImage("Camera_Output", frame);
	//cvSaveImage("soome.pgm", &frame);
	key = cvWaitKey(10);

	cvCvtColor(frame,gray,CV_BGR2GRAY);
	cvThreshold(gray,gray,32,255,CV_THRESH_BINARY);

	cvShowImage("Camera_Output2", gray);

	cvFindContours(gray, storage,&contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));	
	
	while (contours) {
	   result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);

	   if (result -> total == 4) {
                
		CvPoint *pt[4];

	     	for (int i = 0; i < 4; i++) {
		    pt[i] = (CvPoint*)cvGetSeqElem(result, i);
		}
		
		
		
		//cout << pt[0]->x<<endl;
		//cout << *pt[1]<<endl;
		//cout << *pt[2]<<endl;
		//cout << *pt[3]<<endl;
		
		//cvLine(frame, *pt[0], *pt[1], cvScalar(0, 255, 0), 4);
		//cvLine(frame, *pt[1], *pt[2], cvScalar(0, 255, 0), 4);
		//cvLine(frame, *pt[2], *pt[3], cvScalar(0, 255, 0), 4);
		//cvLine(frame, *pt[3], *pt[0], cvScalar(0, 255, 0), 4);

		cvBoundingRect(pt,0);

	   }
	    contours = contours->h_next;
	}
	

	if (char(key) == 27) {
	 // cvDestroyAllWindows();
	 // cvReleaseMemStorage(&storage);
	 // cvReleaseImage(frame);
	 // cvReleaseImage(gray);
	   break;	
	}

	if (char(key) == 99) {
	   //counter++;
	   
	   cvSaveImage("Im age Bro.pgm", gray);	
	}

	//cvShowImage("Camera_Output2", gray);

	
   }while(true);

   cvReleaseCapture(&capture);
   cvDestroyWindow("Camera_Output");
   return 0;
}
