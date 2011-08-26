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

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

/*
 * This examples performs basic video grabbing from the default device
 * (first available camera interface)
 */
int main ( int argc, char **argv )
{
    // capture from video device #1
    CvCapture* capture = cvCreateCameraCapture(0);

    cvWaitKey(5);

    int i = 0;
    while (!capture && i < 100)
    {
        capture = cvCreateCameraCapture(0);
        std::cout << "Try: " << i++ << std::endl;
    }

    if(!capture)
      return EXIT_FAILURE;

    std::string windowName = "Example #2: basic video grabbing with OpenCV";
    cvNamedWindow(windowName.c_str(), CV_WINDOW_AUTOSIZE);
    cvMoveWindow(windowName.c_str(), 100, 100);

    IplImage* img_video = 0;
    // capture a frame 
    if(!cvGrabFrame(capture))
    {
        std::cerr << "Could not grab a frame" << std::endl;
        return EXIT_FAILURE;
    }

    cvQueryFrame(capture);  // this call is necessary to get correct capture properties

    int frameH = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    printf ("Frame height: %d\n",frameH);
    printf ("Frame width: %d\n",frameW);

    int fps = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    cvSetCaptureProperty (capture,CV_CAP_PROP_POS_AVI_RATIO,1);
    int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES);
    cvSetCaptureProperty (capture,CV_CAP_PROP_POS_AVI_RATIO,0);

    printf ("Frames per second: %d\n",fps);
    printf ("Number of frames: %d\n",numFrames);

    double sec_per_frame = (1.0/fps)*1000;
    printf ("milliseconds per frame: %f <-> %d\n", sec_per_frame,(int)sec_per_frame);

    while(1)
    {
        cvGrabFrame(capture);                   // capture a frame
        img_video=cvRetrieveFrame(capture);     // retrieve the captured frame

        cvShowImage(windowName.c_str(), img_video );
        int key = cvWaitKey(30);
        //printf ("key: %d\n",key);

        if (key==10)
        {
          printf ("Enter pressed!");
          break;
        }
        else if (key == 65470)
        {
          printf ("ESC pressed!");
          break;
        }
    }

    cvReleaseCapture(&capture);

    cvDestroyWindow(windowName.c_str());

    return EXIT_SUCCESS;
}
