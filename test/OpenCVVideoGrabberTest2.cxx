/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include <iostream>
#include <stdio.h>
#include <highgui.h>


int OpenCVVideoGrabberTest2( int argc, char *argv[] )
{
    int i;	
	double sec_per_frame;
	
	CvCapture* capture = cvCreateCameraCapture(0);
	
	cvWaitKey(5);
	
	i = 0;
	while(!capture && i < 100) {
		capture = cvCreateCameraCapture(0);	
		printf ("Try: %d\n",i++);
	}

    /*
        // Testcapture for movie file 
  	CvCapture* capture = cvCreateFileCapture("test.mov");#include <unistd.h>
  
  	if(!capture){
    	printf("Could not load video file: %s\n","hellovideo");
    	exit(0);
  	}*/
  	
  	cvNamedWindow("mainWin_video", CV_WINDOW_AUTOSIZE); 
 	cvMoveWindow("mainWin_video", 100, 100);
  
  	IplImage* img_video = 0; 
	if(!cvGrabFrame(capture)){              // capture a frame 
  		printf("Could not grab a frame\n\n");
  		exit(0);
	}
	
	cvQueryFrame(capture);  // this call is necessary to get correct 
                                // capture properties
//	int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
//	int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	cvSetCaptureProperty (capture,CV_CAP_PROP_POS_AVI_RATIO,1);
	int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES);

	cvSetCaptureProperty (capture,CV_CAP_PROP_POS_AVI_RATIO,0);
	
	printf ("Frames per Second: %d\n",fps);
	printf ("Numer of Frames: %d\n",numFrames);
	
	sec_per_frame = (1.0/fps)*1000;	
	printf ("milliseconds per frame: %f <-> %d\n",sec_per_frame,(int)sec_per_frame);
	
	printf ("Iter X\n");
	cvGrabFrame(capture);                   // capture a frame
  	img_video=cvRetrieveFrame(capture);     // retrieve the captured frame
  	
	cvShowImage("mainWin_video", img_video );
	int key = cvWaitKey(30);
	printf ("key: %d\n",key);
	  	
  	cvReleaseCapture(&capture);

    return 0;
}

