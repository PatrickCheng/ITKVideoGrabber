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
 * This example performs basic video grabbing from the default device
 * (first available camera interface)
 */
int main ( int argc, char **argv )
{
    // capture from video device #1
    CvCapture* capture = cvCreateCameraCapture(0);

    std::cout << "cvCreateCameraCapture passed" << std::endl;

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

    std::cout << "cvNamedWindow passed" << std::endl;

    cvMoveWindow(windowName.c_str(), 100, 100);

    std::cout << "cvMoveWindow passed" << std::endl;

    IplImage* img_video = 0;
    // capture a frame 
    if(!cvGrabFrame(capture))
    {
        std::cerr << "Could not grab a frame" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "cvGrabFrame passed" << std::endl;

    int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);

    printf ("Number of frames: %d\n",numFrames);

    cvQueryFrame(capture);  // this call is necessary to get correct capture properties

    std::cout << "cvQueryFrame passed" << std::endl;

    // Read the video's frame size
    CvSize frame_size;

    frame_size.height = (int) cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT );
    printf ("Frame height: %d\n",frame_size.height);

    frame_size.width = (int) cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH );
    printf ("Frame width: %d\n",frame_size.width);

    int fps = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    printf ("Frames per second: %d\n",fps);
    //cvSetCaptureProperty (capture,CV_CAP_PROP_POS_AVI_RATIO,1);
   // double numFrames = cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES);
    //cvSetCaptureProperty (capture,CV_CAP_PROP_POS_AVI_RATIO,0);

    double sec_per_frame = (1.0/fps)*1000;
    printf ("milliseconds per frame: %f <-> %d\n", sec_per_frame,(int)sec_per_frame);

    int c=-1;
    while(1)
    {
        cvGrabFrame(capture);                   // capture a frame
        img_video=cvRetrieveFrame(capture);     // retrieve the captured frame

        cvShowImage(windowName.c_str(), img_video );

        c=cvWaitKey(10);

        // escape key terminates program
        if(c == 27)
           break;
    }

    cvReleaseCapture(&capture);
    std::cout << "cvReleaseCapture passed" << std::endl;

    cvDestroyWindow(windowName.c_str());
    std::cout << "cvDestroyWindow passed" << std::endl;

    return EXIT_SUCCESS;
}
