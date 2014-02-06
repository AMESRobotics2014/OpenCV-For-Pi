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

float area, areavert, areahori, totarea;
int x;

int main()
{
  
   cvNamedWindow("Camera_Output2", 1);
   CvCapture* capture = cvCaptureFromCAM(0);
   do
   {
	IplImage* frame = cvQueryFrame(capture);
	IplImage* graybefore = cvCreateImage(cvGetSize(frame),8,1);
	IplImage* gray = cvCreateImage(cvGetSize(frame),8,1);
	CvSeq* contours;
	CvSeq* result;
	CvMemStorage* storage = cvCreateMemStorage(0);
	//cvShowImage("Camera_Output", frame);
	//cvSaveImage("soome.pgm", &frame);
	key = cvWaitKey(10);

	cvCvtColor(frame,graybefore,CV_BGR2GRAY);
	graybefore = gray + Scalar(75,75,75);
	cvThreshold(gray,gray,64,255,CV_THRESH_BINARY);

	cvShowImage("Camera_Output2", gray);

	cvFindContours(gray, storage,&contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));	
	x=0;
	while (contours) {
	   result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);

	   if (result -> total == 4) {
                
		CvPoint *pt[4];

	     	for (int i = 0; i < 4; i++) {
		    pt[i] = (CvPoint*)cvGetSeqElem(result, i);
		}

		//cout << pt[0]->x<< ", "  << pt[0]->y << endl;
		//cout << pt[1]->x<< ", "  << pt[1]->y << endl;
		//cout << pt[2]->x<< ", "  << pt[2]->y << endl;
		//cout << pt[3]->x<< ", "  << pt[3]->y << endl;

	        //float heightOne = pt[3]->y - pt[0]->y;
		//float hieghtTwo = pt[2]->y - pt[1]->y;
		//float side = (hieghtOne + hieghtTwo)/2;

		float sideleft = pt[1] -> y - pt[0] -> y;
		float sideright = pt[3] -> y - pt[2] ->y;
		float  height = (sideleft + sideright)/2;

		float sidetop = pt[2] -> x - pt[0] -> x;
		float sidebottom = pt[3] -> x - pt[1] -> x;
		float  width = (sidetop + sidebottom)/2;

		//area = height * width;
		//cout<<area<<endl;
		if(x==2){
		//cout << "Hot" <<endl;
		}else{
		//cout << "Not Hot" <<endl;
		}

		cvLine(frame, *pt[0], *pt[0], cvScalar(0, 255, 0), 4);
		cvLine(frame, *pt[1], *pt[1], cvScalar(0, 255, 0), 4);
		cvLine(frame, *pt[2], *pt[2], cvScalar(0, 255, 0), 4);
		cvLine(frame, *pt[3], *pt[3], cvScalar(0, 255, 0), 4);

	   }
	    	contours = contours->h_next;
		x++;

	}
	//cvShowImage("Camera_Output2", frame);

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
