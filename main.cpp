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
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
char key;
int main()
{
   cvNamedWindow("Camera_Output", 1);
   CvCapture* capture = cvCaptureFromCAM(0);
   while (1)
   {
	IplImage* frame = cvQueryFrame(capture);
	cvShowImage("Camera_Output", frame);
	//cvSaveImage("soome.pgm", &frame);
	key = cvWaitKey(10);

	if (char(key) == 27) {
	   break;	
	}
   }

   cvReleaseCapture(&capture);
   cvDestroyWindow("Camera_Output");
   return 0;
}
