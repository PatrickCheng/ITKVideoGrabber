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

/** Set up a spatial region with the given dimensions */
RGBFrameType::RegionType SetUpSpatialRegion(unsigned int x, unsigned int y)
{
  RGBFrameType::RegionType out;
  RGBFrameType::RegionType::SizeType size;
  RGBFrameType::RegionType::IndexType start;
  size[0] = x;
  size[1] = y;
  start.Fill( 0 );
  out.SetSize( size );
  out.SetIndex( start );
  return out;
}

/*
 * This example performs basic video grabbing from the default device
 * (first available camera interface) using itkOpenCVVideoGrabberInterface
 */
int main ( int argc, char **argv )
{

    RGBVideoStreamType ::Pointer videoStream = RGBVideoStreamType::New();

    // Set the buffered temporal region
    RGBVideoStreamType::TemporalRegionType temporalRegion;
    unsigned long startFrame = 0;
    unsigned long numFrames = 5;
    temporalRegion.SetFrameStart( startFrame );
    temporalRegion.SetFrameDuration( numFrames );
    videoStream->SetLargestPossibleTemporalRegion( temporalRegion );
    videoStream->SetRequestedTemporalRegion( temporalRegion );
    videoStream->SetBufferedTemporalRegion( temporalRegion );

    // Initialize all frames in the buffered temporal region
    videoStream->InitializeEmptyFrames();

    // Set the buffered spatial region for each frame
    RGBFrameType::RegionType largestSpatialRegion = SetUpSpatialRegion(100, 100);
    RGBFrameType::RegionType requestedSpatialRegion = SetUpSpatialRegion(40, 40);
    RGBFrameType::RegionType bufferedSpatialRegion = SetUpSpatialRegion(50, 40);
    videoStream->SetAllLargestPossibleSpatialRegions( largestSpatialRegion );
    videoStream->SetAllRequestedSpatialRegions( requestedSpatialRegion );
    videoStream->SetAllBufferedSpatialRegions( bufferedSpatialRegion );

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
