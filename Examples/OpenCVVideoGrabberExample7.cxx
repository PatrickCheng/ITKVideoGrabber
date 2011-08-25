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

#include <highgui.h>
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"

#include <itkVideoStream.h>
#include <itkCurvatureFlowImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkThresholdImageFilter.h>
#include <itkImageFilterToVideoFilterWrapper.h>
#include <itkFrameDifferenceVideoFilter.h>
#include <itkVideoFileReader.h>
#include <itkVideoFileWriter.h>
#include <itkOpenCVVideoIOFactory.h>

int main ( int argc, char **argv )
{
    double sec_per_frame;

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

    cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("mainWin", 100, 100);

    IplImage* img_video, img_edges;
// capture a frame
    if(!cvGrabFrame(capture))
    {
        std::cerr << "Could not grab a frame" << std::endl;
        return EXIT_FAILURE;
    }

    cvQueryFrame(capture);  // this call is necessary to get correct
                            // capture properties
//      int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
//      int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int fps = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    cvSetCaptureProperty (capture,CV_CAP_PROP_POS_AVI_RATIO,1);
    int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES);

    cvSetCaptureProperty (capture,CV_CAP_PROP_POS_AVI_RATIO,0);

    printf ("Frames per Second: %d\n",fps);
    printf ("Numer of Frames: %d\n",numFrames);

    sec_per_frame = (1.0/fps)*1000;
    printf ("milliseconds per frame: %f <-> %d\n",sec_per_frame,(int)sec_per_frame);

    while(1)
    {
        printf ("Iter X\n");
        cvGrabFrame(capture);                   // capture a frame
        img_video=cvRetrieveFrame(capture);     // retrieve the captured frame
        cv::GaussianBlur(*img_video, img_edges, cv::Size(7,7), 1.5, 1.5);
        cvCanny(*img_edges, img_edges, 0, 30, 3);
        cvShowImage("mainWin", img_edges );
        int key = cvWaitKey(30);
        printf ("key: %d\n",key);

        if (key==10) {
                printf ("Enter pressed!");
                break;
        } else if (key == 65470) {
                printf ("ESC pressed!");
                break;
        }
    }

    cvReleaseCapture(&capture);

    cvWaitKey(5);

    return EXIT_SUCCESS;
}
