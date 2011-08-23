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

int OpenCVVideoGrabberTest1( int argc, char *argv[] )
{
    int c;
    // allocate memory for an image
    IplImage *img;
    // capture from video device #1
    CvCapture* capture = cvCaptureFromCAM(0);
    // create a window to display the images
    cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);
    // position the window
    cvMoveWindow("mainWin", 5, 5);
    // retrieve the captured frame
    img=cvQueryFrame(capture);
    // show the image in the window
    cvShowImage("mainWin", img );
    // wait 10 ms for a key to be pressed
    c=cvWaitKey(10);

    return 0;
}

