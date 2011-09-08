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

}

//
// FinishReadingOrWriting
//
void EpiphanVideoGrabberInterface::FinishReadingOrWriting()
{
  this->ResetMembers();
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
// SplitFileNames ','
//
std::vector<std::string> EpiphanVideoGrabberInterface::SplitFileNames(const char* fileList)
{
  std::string str = fileList;

  std::vector<std::string> out;

  int pos = 0;
  int len = str.length();
  while (pos != -1 && len > 0)
    {
    // Get the substring
    str = str.substr(pos, len);

    // Update pos
    pos = str.find(',');

    // Add the filename to the list
    out.push_back(str.substr(0,pos));

    // Move past the delimiter
    if (pos != -1)
      {
      pos++;
      }
    len -= pos;
    }

  return out;
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
// SetNextFrameToRead
//
bool EpiphanVideoGrabberInterface::SetNextFrameToRead(unsigned long frameNumber)
{

  if (frameNumber >= m_FrameTotal)
    {
    return false;
    }

  m_CurrentFrame = frameNumber;
  return true;
}

// CanWriteFile
//
bool EpiphanVideoGrabberInterface::CanWriteFile(const char* filename)
{

  // Make sure file names have been specified
  std::vector<std::string> fileList = SplitFileNames(filename);
  if (fileList.size() == 0)
    {
    return false;
    }

  // Make sure all file names have the same extension
  for (unsigned int i = 1; i < fileList.size(); ++i)
    {
    int prevExtPos = fileList[i-1].rfind(".");
    int extPos = fileList[i].rfind(".");
    if (prevExtPos == -1 || extPos == -1)
      {
      return false;
      }
    std::string prevExt = fileList[i-1].substr(prevExtPos + 1, fileList[i-1].length()-prevExtPos-1);
    std::string ext = fileList[i].substr(extPos + 1, fileList[i].length()-extPos-1);

    if (strcmp(prevExt.c_str(), ext.c_str()))
      {
      return false;
      }
    }

  // Make sure we can instantiate an ImageIO to write the first file
  ImageIOBase::Pointer ioTemp = ImageIOFactory::CreateImageIO(
      fileList[0].c_str(), ImageIOFactory::WriteMode);
  if (ioTemp.IsNull())
    {
    return false;
    }

  return true;
}

//
// WriteImageInformation
//
void EpiphanVideoGrabberInterface::WriteImageInformation()
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
