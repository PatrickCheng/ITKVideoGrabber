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
#include <stdio.h>

#include <itkVideoStream.h>
#include <itkVideoGrabber.h>
#include <itkOpenCVVideoGrabberInterfaceFactory.h>
#include <itkOpenCVVideoGrabberInterface.h>

typedef itk::RGBPixel<unsigned char>              RGBPixelType;
typedef itk::Image<RGBPixelType, 2>               RGBFrameType;
typedef itk::VideoStream<RGBFrameType>            RGBVideoStreamType;
typedef itk::VideoGrabber<RGBVideoStreamType >    VideoGrabberType;

/*
 * This example performs basic video grabbing from the default device
 * (first available camera interface) using itkOpenCVVideoGrabberInterface
 */
int main ( int argc, char **argv )
{
   VideoGrabberType::Pointer grabber = VideoGrabberType::New();
  // itk::ObjectFactoryBase::RegisterFactory( itk::OpenCVVideoGrabberInterfaceFactory::New() );

//   itk::OpenCVVideoGrabberInterface::Pointer grabber = itk::OpenCVVideoGrabberInterface::New();
/*
   if (!grabber->OpenGrabber(0))
   {
      std::cerr << "Could not open default grabber device" << std::endl;
      return EXIT_FAILURE;
   }
//   grabber->GrabSingleFrame();
*/
   return EXIT_SUCCESS;
}
