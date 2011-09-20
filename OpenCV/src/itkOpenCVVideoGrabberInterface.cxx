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
#include "itkOpenCVVideoGrabberInterface.h"

#include "itkImage.h"
#include "itkImportImageFilter.h"

namespace itk
{

//
// Constructor
//
OpenCVVideoGrabberInterface::OpenCVVideoGrabberInterface()
{
  this->ResetMembers();
}

//
// Destructor
//
OpenCVVideoGrabberInterface::~OpenCVVideoGrabberInterface()
{
  this->CloseGrabber();
}

//
// PrintSelf
//
void OpenCVVideoGrabberInterface::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
  if (this->m_CVImage != NULL)
    {
    os << indent << "Image dimensions : ["<<this->m_CVImage->width<<","
        <<this->m_CVImage->height<<"]"<<std::endl;
    os << indent << "Origin : "<<this->m_CVImage->origin<<std::endl;
    os << indent << "Image spacing (in bits) : "<<this->m_CVImage->depth<<std::endl;
    os << indent << "Image Size : "<<this->m_CVImage->imageSize<<std::endl;
    os << indent << "Color model : "<<this->m_CVImage->colorModel
        <<" ("<<this->m_NumberOfComponents<<" channels)"<<std::endl;
    }
}

//
// GetPositionInMSec
//
double OpenCVVideoGrabberInterface::GetPositionInMSec()
{
  return this->m_PositionInMSec;
}

//
// GetRatio
//
double OpenCVVideoGrabberInterface::GetRatio()
{
  return this->m_Ratio;
}

//
// GetFrameTotal
//
unsigned long OpenCVVideoGrabberInterface::GetFrameTotal()
{
  return this->m_FrameTotal;
}

//
// GetFpS
//
double OpenCVVideoGrabberInterface::GetFpS()
{
  return this->m_FpS;
}

//
// GetCurrentFrame
//
unsigned long OpenCVVideoGrabberInterface::GetCurrentFrame()
{
  return this->m_CurrentFrame;
}

//
// GetIFrameInterval
//
unsigned int OpenCVVideoGrabberInterface::GetIFrameInterval()
{
  return this->m_IFrameInterval;
}

//
// GetLastIFrame
//
unsigned long OpenCVVideoGrabberInterface::GetLastIFrame()
{
  return this->m_LastIFrame;
}

//
// SetCameraIndex
//
void OpenCVVideoGrabberInterface::SetCameraIndex(int idx)
{
  this->m_CameraIndex = idx;
}

//
// GetCameraIndex
//
int OpenCVVideoGrabberInterface::GetCameraIndex()
{
  return this->m_CameraIndex;
}

void OpenCVVideoGrabberInterface::ReadImageInformation()
{

}

//
// Checks if we can read a given camera
//
bool OpenCVVideoGrabberInterface::CanReadGrabber( unsigned long cameraID )
{
  // Try capture from current camera index
  CvCapture* localCapture = cvCaptureFromCAM( cameraID );
  if (!localCapture)
    {
    return false;
    }

  // Close the file and return true if successful
  cvReleaseCapture(&localCapture);
  return true;
}

//
// Grabs a single frame from the current camera. Updates grabber properties
//
bool OpenCVVideoGrabberInterface::GrabSingleFrame(void *buffer)
{
  // If grabber is not already open, open it and keep it open
  if (!this->m_GrabberIsOpen)
    {
    this->OpenGrabber(this->m_CameraIndex);
    }

  // Read the desired frame
  //
  // Note: This will advance to the next frame in the stream, so SetNextFrameToRead
  //       doesn't need to be called before GrabSingleFrame is called again unless you want to
  //       skip to a different location. Be warned, though. SetNextFrameToRead can
  //       only skip to I-Frames, so there can be unexpected behavior
  IplImage* tempIm = cvQueryFrame(this->m_Capture);
  if (tempIm == NULL)
    {
    itkExceptionMacro(<< "Error reading frame " << this->m_CurrentFrame);
    }

  // Convert to RGB rather than BGR
  if (this->m_CVImage == NULL)
    {
    this->m_CVImage = cvCreateImage( cvSize(this->m_Dimensions[0],this->m_Dimensions[1]),
                                     IPL_DEPTH_8U, this->m_NumberOfComponents );
    }
  cvCvtColor(tempIm, this->m_CVImage, CV_BGR2RGB);

  // Update the frame-dependent properties
  this->UpdateGrabberProperties();

  // Put the frame's buffer into the supplied output buffer
  void* tempBuffer = reinterpret_cast<void*>(this->m_CVImage->imageData);
  size_t bufferSize = this->m_CVImage->imageSize;
  memcpy(buffer, tempBuffer, bufferSize);

  return true;
}


//
// UpdateGrabberProperties
//
void OpenCVVideoGrabberInterface::UpdateGrabberProperties()
{
  this->m_CurrentFrame = 
    cvGetCaptureProperty(this->m_Capture,CV_CAP_PROP_POS_FRAMES);
  this->m_PositionInMSec = 
    cvGetCaptureProperty(this->m_Capture,CV_CAP_PROP_POS_MSEC);
  this->m_FpS = static_cast<double>
    (cvGetCaptureProperty( this->m_Capture, CV_CAP_PROP_FPS ));
  this->m_Ratio = 
    cvGetCaptureProperty(this->m_Capture,CV_CAP_PROP_POS_AVI_RATIO);
  this->m_FourCC =
    cvGetCaptureProperty(this->m_Capture,CV_CAP_PROP_FOURCC);
}

//
// OpenGrabber
//
bool OpenCVVideoGrabberInterface::OpenGrabber(int index)
{
  this->m_CameraIndex = index;

  if (this->m_GrabberIsOpen)
    {
    itkExceptionMacro("Cannot open grabber if already open");
    }

  // Set up a local capture and image
    CvCapture* localCapture;
    IplImage* tempImage;

    // Open the camera capture
    localCapture = cvCaptureFromCAM( this->m_CameraIndex );

    // Make sure it opened right
    if (!localCapture)
      {
      itkExceptionMacro(<< "Could not open OpenCV video grabber " << this->m_CameraIndex);
      }

    // Query the frame and set the frame total to 1
    tempImage = cvQueryFrame(localCapture);
    this->m_FrameTotal = 1;

    // Populate member variables
    this->m_FpS = static_cast<double>
      (cvGetCaptureProperty( localCapture, CV_CAP_PROP_FPS ));

    // Set width, height
    this->m_Dimensions.clear();
    this->m_Dimensions.push_back( cvGetCaptureProperty( localCapture, CV_CAP_PROP_FRAME_WIDTH ) );
    this->m_Dimensions.push_back( cvGetCaptureProperty( localCapture, CV_CAP_PROP_FRAME_HEIGHT ) );

    this->m_NumberOfComponents = tempImage->nChannels;

    // Set the pixel type
    if (this->m_NumberOfComponents == 1)
      {
      this->m_PixelType = SCALAR;
      }
    else if (this->m_NumberOfComponents == 3)
      {
      this->m_PixelType = RGB;
      }
    else if (this->m_NumberOfComponents == 4)
      {
      this->m_PixelType = RGBA;
      }
    else
      {
      itkExceptionMacro("OpenCV video grabber only supports Mono, RGB, and RGBA input");
      }

    // Release the local capture and image
    cvReleaseCapture(&localCapture);

    this->m_Capture = cvCaptureFromCAM( this->m_CameraIndex );
    if (this->m_Capture != NULL)
      {
      this->m_GrabberIsOpen = true;
      }
    else
      {
      itkExceptionMacro("OpenCV video grabber failed to open");
      }

    return true;
}

bool OpenCVVideoGrabberInterface::CloseGrabber()
{
  if (this->m_Capture != NULL)
    {
    cvReleaseCapture(&(this->m_Capture));
    this->m_Capture = 0;
    }
  if (this->m_CVImage != NULL)
    {
    cvReleaseImage(&(this->m_CVImage));
    m_CVImage = 0;
    }

  this->ResetMembers();

  return true;
}

bool OpenCVVideoGrabberInterface::StartGrabbing()
{

  return false;
}

bool OpenCVVideoGrabberInterface::StopGrabbing()
{
  return false;
}

//
// ResetMembers
//
void OpenCVVideoGrabberInterface::ResetMembers()
{
  this->m_CVImage = 0;
  this->m_TempImage = 0;
  this->m_Capture = 0;
  this->m_GrabberIsOpen = false;
  this->m_FpS = 0;
  this->m_FourCC = 0;
  this->m_FrameTotal = 0;
  this->m_CurrentFrame = 0;
  this->m_IFrameInterval = 0;
  this->m_LastIFrame = 0;

  // Default to reading from a file
  this->m_CameraIndex = 0;

  this->m_Dimensions.clear();
  this->m_NumberOfComponents = 0;
  this->m_PixelType = SCALAR;
  this->m_ComponentType = UCHAR;
//  this->SetNumberOfDimensions(2);
  this->m_Spacing[0] = 1.0;
  this->m_Spacing[1] = 1.0;
  this->m_Origin[0] = 0.0;
  this->m_Origin[1] = 0.0;
}


} // end namespace itk
