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

 using namespace std;
using namespace cv;
char key;

bool hot;
double  firstd, secondd;
double hori, vert;


//public static removeNoise(int a, int b){
//float area = a * b;

 //if(area < smallarea){
   //omit
// }return area;
//}return area;

bool autonomous (double a, double  b)
{
	hot = false;

	double area = a * b;
if (area < 3) {
	//cout << area << endl;

	if(area > 660 && area < 760) {
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
double teleop (float a, float b)
{
	double distance;

 	if(a>b) {

	firstd = 44.099407801909 * pow(0.91175211621759,a);

}
	if(b>a) {

	secondd = 1234 * pow(234,a);

}
	distance = (firstd + secondd)/2;

	return distance;
}

int main()
{
    //ideoCapture imgcapture(CV_CAP_ANY);
   cvNamedWindow("Camera_Output2", 1);
   	CvCapture* capture = cvCreateCameraCapture(0);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
	cvSetCaptureProperty(capture, CV_CAP_PROP_BRIGHTNESS, 0.7);
   do
   {
	IplImage* frame2 = cvLoadImage("real7ft6in.jpg", CV_LOAD_IMAGE_COLOR);
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
	cvThreshold(gray,gray,70,255,CV_THRESH_BINARY);

	cvShowImage("Camera_Output2", frame2);
	//cvShowImage("Camera_Output2", gray);

	//cvFindContours(gray, storage,&contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));	
        cvFindContours(frame2, storage,&contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

	while (contours) {
	   result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);

//	   removeNoise();
	   if (result -> total == 4) {

		CvPoint *pt[4];
		CvPoint npt[4];
	     	for (int i = 0; i < 4; i++) {
		    pt[i] = (CvPoint*)cvGetSeqElem(result, i);
		}

		//cout <<"pt 0: " << pt[0]->x<< ", "  << pt[0]->y << endl;
		//cout <<"pt 1: " << pt[1]->x<< ", "  << pt[1]->y << endl;
		//cout <<"pt 2: " << pt[2]->x<< ", "  << pt[2]->y << endl;
		//cout <<"pt 3: " << pt[3]->x<< ", "  << pt[3]->y << endl
	int ptzeroy=pt[0]->y;
	int ptoney=pt[1]->y;
	int pttwoy=pt[2]->y;
	int ptthreey=pt[3]->y;
	int avgy = ((ptzeroy) + (ptoney) + (pttwoy) + (ptthreey));
	int avgx = ((pt[0]->x) + (pt[1]->x) + (pt[2]->x) + (pt[3]->x))/4;
	for(int a = 0;a < 4;a++) {
		if(pt[a]->y > avgy && pt[a]->x > avgx) {
		npt[0]= *pt[a];
	}
		if(pt[a]->y < avgy && pt[a]->x > avgx) {
		npt[1]= *pt[a];
	}
		if(pt[a]->y > avgy && pt[a]->x < avgx) {
		npt[2] = *pt[a];
	}
		if(pt[a]->y < avgy && pt[a]->x < avgx) {
		npt[3] = *pt[a];
	}

	}

		float sideleft = npt[1].y - npt[0].y;
		float sideright = npt[3].y - npt[2].y;
		float  height = (sideleft + sideright)/2;

		float sidetop = npt[2].x - npt[0].x;
		float sidebottom = npt[3].x - npt[1].x;
		float  width = (sidetop + sidebottom)/2;

		if(height > 0) {
		//cout << height <<endl;
	 	}

		if(width > 0) {
		//cout << width << endl;
		}


/*		if(height<width) {
		hori = npt[0].x;
		}

		if(width<height) {
		vert = npt[0].x;
		}
*/
	/*	if(hori<vert) {
		cout << "Goal is on the left." <<endl;
		}else if(vert<hori) {
		cout << "Goal is on the right." <<endl;
		}
*/
		hot = autonomous(height, width);

		if(hot == true) {
		cout << "Goal is Hot" << endl;
		}
		else {
		cout << "Goal is Cool" <<endl;
		}


		double distancefinal = teleop(height, width);
		//cout << distancefinal << endl;

		cvLine(frame, *pt[0], *pt[1], cvScalar(0, 255, 0), 4);
		cvLine(frame, *pt[1], *pt[2], cvScalar(0, 255, 0), 4);
		cvLine(frame, *pt[2], *pt[3], cvScalar(0, 255, 0), 4);
		cvLine(frame, *pt[3], *pt[0], cvScalar(0, 255, 0), 4);

	   }
	    	contours = contours->h_next;
		//cvSmooth(frame, get, CV_GAUSSIAN, 11, 11);
		//cvCvtColor(get, get3, CV_RGB2GRAY);
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


   }while(true);

   cvReleaseCapture(&capture);
   cvDestroyWindow("Camera_Output");
   return 0;
}
