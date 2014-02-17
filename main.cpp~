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
#include <math.h>
#include <fstream>

 using namespace std;
using namespace cv;
char key;

bool hot;
double  firstd, secondd, distancefinal;
double hori, vert;
double mindist=5,maxdist=35;
bool autonomous (double a)
{
	hot = false;

	double area = a;
if (area < 3) {

	if(area > 140 && area < 200) {
	//cout << "Hot" << endl;
	hot = true;
	}
/*
	if(area > 100) {
	cout << area << endl;
	}
*/
}
	return hot;
}
//		height,width
double teleop (double a, double b)
{
	double distance;

 	if(a>b) {

	firstd = 41.43139314 * pow(.9859750957,a);

}
	if(b>a) {

	secondd = 35.670583878669 * pow(.98285941516385,b);

}
	distance = (secondd + firstd) / 2;
	return distance;
}

double angle (double a)
{

	double final;

	final = a;

	return final;

}

int main()
{
	double potread;
    	//videoCapture imgcapture(CV_CAP_ANY);
   	cvNamedWindow("Camera_Output2", 1);
   	CvCapture* capture = cvCreateCameraCapture(0);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
	cvSetCaptureProperty(capture, CV_CAP_PROP_BRIGHTNESS, 0.7);
   do
   {
	//IplImage* frame2 = cvLoadImage("real5ft.jpg");
	IplImage* frame = cvQueryFrame(capture);
	IplImage* get = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
	IplImage* get2 = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	IplImage* get3 = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	IplImage* graybefore = cvCreateImage(cvGetSize(frame),8,1);
	IplImage* gray = cvCreateImage(cvGetSize(frame),8,1);
	CvSeq* contours;
	CvSeq* result;
	CvMemStorage* storage = cvCreateMemStorage(0);
	//cvShowImage("Camera_Output2", frame);
	key = cvWaitKey(10);

	cvCvtColor(frame,gray,CV_BGR2GRAY);
	cvThreshold(gray,gray,64,255,CV_THRESH_BINARY);
	//cvShowImage("Camera_Output2", frame2);
	cvShowImage("Camera_Output2", gray);

	cvFindContours(gray, storage,&contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));	
	while (contours) {
	   result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);

	   if (result -> total == 4) {

		CvPoint *pt[4];
		CvPoint npt[6];
	     	for (int i = 0; i < 4; i++) {
		    pt[i] = (CvPoint*)cvGetSeqElem(result, i);
		}

		//cout <<"pt 0: " << pt[0]->x<< ", "  << pt[0]->y << endl;
		//cout <<"pt 1: " << pt[1]->x<< ", "  << pt[1]->y << endl;
		//cout <<"pt 2: " << pt[2]->x<< ", "  << pt[2]->y << endl;
		//cout <<"pt 3: " << pt[3]->x<< ", "  << pt[3]->y << endl;

	int ptzeroy=pt[0]->y;
	int ptoney=pt[1]->y;
	int pttwoy=pt[2]->y;
	int ptthreey=pt[3]->y;
	int avgy = ((ptzeroy) + (ptoney) + (pttwoy) + (ptthreey))/4;
	int avgx = ((pt[0]->x) + (pt[1]->x) + (pt[2]->x) + (pt[3]->x))/4;
	//cout << "Average y: " << avgy <<endl;
	//cout << "Average x: " << avgx <<endl;
	for(int a = 0;a < 4;a++) {
		if(pt[a]->y > avgy && pt[a]->x > avgx) {
		npt[3]= *pt[a];
	}
		if(pt[a]->y < avgy && pt[a]->x > avgx) {
		npt[2]= *pt[a];
	}
		if(pt[a]->y > avgy && pt[a]->x < avgx) {
		npt[1] = *pt[a];
	}
		if(pt[a]->y < avgy && pt[a]->x < avgx) {
		npt[0] = *pt[a];
	}
/*
	npt[5].x = avgx;
	npt[5].y = (npt[0].y + npt[2].y) / 2;

	npt[6].x = avgx;
	npt[6].y = (npt[1].y + npt[3].y) / 2;
*/
	}

		float sideleft = npt[1].y - npt[0].y;
		float sideright = npt[3].y - npt[2].y;
		float  height = (sideleft + sideright)/2;

		float sidetop = npt[2].x - npt[0].x;
		float sidebottom = npt[3].x - npt[1].x;
		float  width = (sidetop + sidebottom)/2;

		if(height > 0) {
		cout <<"Height: " << height <<endl;
	 	}

		if(width > 0) {
		cout <<"Width: " << width << endl;
		}

		double area = height * width;
		if(area>0) {
		//cout <<"Area: " << area <<endl;
		}

		if(height>0 && width>0) {
		hot = autonomous(area);

		if(hot == true) {
		//cout << "Goal is Hot" << endl;
		}
		else {
		//cout << "Goal is Cool" <<endl;
		}
		}

		if(height>0 && width>0) {
		distancefinal = teleop(height, width);
//if(distancefinal>mindist && distancefinal<maxdist)
		cout << "Distance: " << distancefinal << endl;
		}
		if(distancefinal > 0) {
		potread = angle(distancefinal);
		//cout<< "Reading for Hot: " << potread <<endl;
		}

		cvLine(frame, npt[0], npt[1], cvScalar(0, 255, 0), 4);
		cvLine(frame, npt[1], npt[2], cvScalar(0, 255, 0), 4);
		cvLine(frame, npt[2], npt[3], cvScalar(0, 255, 0), 4);
		cvLine(frame, npt[3], npt[0], cvScalar(0, 255, 0), 4);

	   }
	    	contours = contours->h_next;
		//cvSmooth(frame, get, CV_GAUSSIAN, 11, 11);
		//cvCvtColor(get, get2, CV_RGB2GRAY);
		//cvCanny(get2, get3, 10, 10, 3);
		//Canny(capture, contours, 35, 90);

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

	   cvSaveImage("Im age Bro.pgm", frame);
	}

	if (char(key) == 49) {
		cvSaveImage("real5ft.jpg", gray);
}
	if (char(key) == 50) {
		cvSaveImage("real7ft6in.jpg",gray);
}
	if (char(key) == 51) {
		cvSaveImage("real10ft.jpg",gray);
}
	if (char(key) == 52) {
		cvSaveImage("real12ft6in.jpg", gray);
}
	if (char(key) == 53) {
		cvSaveImage("real15ft.jpg", gray);
}
if (char(key) == 54) {
		cvSaveImage("real17ft6in.jpg", frame);
}

if (char(key) == 55) {
		cvSaveImage("real20ft.jpg", frame);
}
if (char(key) == 56) {
		cvSaveImage("real22ft5in.jpg", frame);
}
if (char(key) == 57) {
		cvSaveImage("real15ft.jpg", frame);
}

ofstream test;
test.open ("test.txt");
test <<"Distancefinal, " << distancefinal <<endl;
test <<"Hot," << hot<<endl;
test.close();

   }while(true);

   cvReleaseCapture(&capture);
   cvDestroyWindow("Camera_Output");
   return 0;
}
