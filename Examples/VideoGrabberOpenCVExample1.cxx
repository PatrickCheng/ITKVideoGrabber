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

/*
 * This example performs basic video grabbing from the default device
 * (first available camera interface)
 */
int main ( int argc, char **argv )
{
    // allocate memory for an image
    IplImage *img;

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

    // create a window to display the images
    std::string windowName = "Example #1: basic video grabbing with OpenCV";
    cvNamedWindow(windowName.c_str(), CV_WINDOW_AUTOSIZE);
    // position the window
    cvMoveWindow(windowName.c_str(), 100, 100);
    int c = 0;

    while(1)
    {
      // retrieve the captured frame
      img=cvQueryFrame(capture);
      // show the image in the window
      cvShowImage(windowName.c_str(), img );
      // wait 10 ms for a key to be pressed
      c=cvWaitKey(10);
      // escape key terminates program
      if(c == 27)
         break;
    }

  cvDestroyWindow(windowName.c_str());

  return EXIT_SUCCESS;
}
