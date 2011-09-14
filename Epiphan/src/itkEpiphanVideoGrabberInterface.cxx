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
#include "itkEpiphanVideoGrabberInterface.h"

#include "itkImage.h"
#include "itkImportImageFilter.h"
#include "itkImageIOFactory.h"

namespace itk
{

//
// Constructor
//
EpiphanVideoGrabberInterface::EpiphanVideoGrabberInterface()
{
  this->ResetMembers();
}

//
// Destructor
//
EpiphanVideoGrabberInterface::~EpiphanVideoGrabberInterface()
{
  this->CloseGrabber();
}

//
// PrintSelf
//
void EpiphanVideoGrabberInterface::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
}


bool EpiphanVideoGrabberInterface::CloseGrabber()
{
return false;
}

bool EpiphanVideoGrabberInterface::StartGrabbing()
{
  return false;
}

bool EpiphanVideoGrabberInterface::StopGrabbing()
{
  return false;
}

bool EpiphanVideoGrabberInterface::GrabSingleFrame(void *buffer)
{
  // If grabber is not already open, open it and keep it open
   if (!this->m_GrabberIsOpen)
     {
     this->OpenGrabber(this->m_CameraIndex);
     }

   // get frame

   // convert color space

   // Update the frame-dependent properties
   this->UpdateGrabberProperties();

   // Put the frame's buffer into the supplied output buffer
   //void* tempBuffer = reinterpret_cast<void*>(this->m_CVImage->imageData);
   //size_t bufferSize = this->m_CVImage->imageSize;
   //memcpy(buffer, tempBuffer, bufferSize);
}

//
// UpdateGrabberProperties
//
void EpiphanVideoGrabberInterface::UpdateGrabberProperties()
{
  this->m_CurrentFrame = 0;
  this->m_PositionInMSec = 0.0;
  this->m_FpS = 0;
 // this->m_Ratio = 0.0;
 // this->m_FourCC = 0;
}

//
// GetPositionInMSec
//
double EpiphanVideoGrabberInterface::GetPositionInMSec()
{
  return m_PositionInMSec;
}

//
// GetRatio
//
double EpiphanVideoGrabberInterface::GetRatio()
{
  return m_Ratio;
}

//
// GetFrameTotal
//
unsigned long EpiphanVideoGrabberInterface::GetFrameTotal()
{
  return m_FrameTotal;
}

//
// GetFpS
//
double EpiphanVideoGrabberInterface::GetFpS()
{
  return m_FpS;
}

//
// GetCurrentFrame
//
unsigned long EpiphanVideoGrabberInterface::GetCurrentFrame()
{
  return m_CurrentFrame;
}

//
// GetIFrameInterval
//
unsigned int EpiphanVideoGrabberInterface::GetIFrameInterval()
{
  return m_IFrameInterval;
}

//
// GetLastIFrame
//
unsigned long EpiphanVideoGrabberInterface::GetLastIFrame()
{
  return m_LastIFrame;
}

//
// CanReadCamera
//
bool EpiphanVideoGrabberInterface::CanReadGrabber( unsigned long cameraID )
{
  return false;
}


//
// ReadImageInformation
//
void EpiphanVideoGrabberInterface::ReadImageInformation()
{

}

//
// ResetMembers
//
void EpiphanVideoGrabberInterface::ResetMembers()
{
    this->m_GrabberIsOpen = false;
    this->m_FpS = 0;
//    this->m_FourCC = 0;
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
