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

#ifndef __itkVideoGrabber_txx
#define __itkVideoGrabber_txx

#include "itkConvertPixelBuffer.h"

namespace itk
{

//
// Constructor
//
template< class TOutputVideoStream >
VideoGrabber< TOutputVideoStream >
::VideoGrabber()
{
  // Initialize members
//  m_VideoGrabberInterface = NULL;
  m_PixelConversionNeeded = false;
  m_IFrameSafe = true;

  // TemporalProcessObject inherited members
  this->m_UnitOutputNumberOfFrames = 1; //TemporalProcessObject::
  this->m_FrameSkipPerOutput = 1; //TemporalProcessObject::
  this->m_InputStencilCurrentFrameIndex = 0; //TemporalProcessObject::
}


//
// Destructor
//
template< class TOutputVideoStream >
VideoGrabber< TOutputVideoStream >
::~VideoGrabber()
{}


//
// PrintSelf
//
template< class TOutputVideoStream >
void
VideoGrabber< TOutputVideoStream >
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  if (m_VideoGrabberInterface.IsNotNull())
    {
    std::cout << indent << "VideoGrabberInterface:" << std::endl;
    m_VideoGrabberInterface->Print(os, indent.GetNextIndent());
    }
}

//
// GenerateOutputInformation
//
template< class TOutputVideoStream >
void
VideoGrabber< TOutputVideoStream >
::UpdateOutputInformation()
{
  //
  // Generate a VideoGrabberInterfaceBase if needed
  //
  if (m_VideoGrabberInterface.IsNull())
    {
    this->InitializeVideoGrabber();
    }

  //
  // Check that the desired dimension matches that exposed by the frame grabber
  //
  if (m_VideoGrabberInterface->GetNumberOfDimensions() != FrameType::ImageDimension)
    {
    itkExceptionMacro("Output dimension doesn't match dimension of read data");
    }

  //
  // Set up the largest possible temporal region for the output
  //
  TemporalRegion largestPossibleTemporalRegion;
  largestPossibleTemporalRegion.SetFrameStart(0);
  if (m_IFrameSafe)
    {
    largestPossibleTemporalRegion.SetFrameDuration(m_VideoGrabberInterface->GetLastIFrame()+1);
    }
  else
    {
    largestPossibleTemporalRegion.SetFrameDuration(m_VideoGrabberInterface->GetFrameTotal());
    }
    
  this->GetOutput()->SetLargestPossibleTemporalRegion(largestPossibleTemporalRegion);

  //
  // Set up the information for the output frames
  //

  // Set up largest possible spatial region
  typename FrameType::RegionType region;
  typename FrameType::SizeType size;
  typename FrameType::IndexType start;
  typename FrameType::PointType origin;
  typename FrameType::SpacingType spacing;
  typename FrameType::DirectionType direction;
  for (unsigned int i = 0; i < FrameType::ImageDimension; ++i)
    {
    size[i] = m_VideoGrabberInterface->GetDimensions(i);
    origin[i] = m_VideoGrabberInterface->GetOrigin(i);
    spacing[i] = m_VideoGrabberInterface->GetSpacing(i);
    for (unsigned int j = 0; j < FrameType::ImageDimension; ++j)
      {
      direction[j][i] = m_VideoGrabberInterface->GetDirection(i)[j];
      }
    }
  start.Fill(0);
  region.SetSize(size);
  region.SetIndex(start);
  this->GetOutput()->SetAllLargestPossibleSpatialRegions(region);
  this->GetOutput()->SetAllBufferedSpatialRegions(region);
  this->GetOutput()->SetAllRequestedSpatialRegions(region);

  this->GetOutput()->SetAllFramesSpacing(spacing);
  this->GetOutput()->SetAllFramesOrigin(origin);
  this->GetOutput()->SetAllFramesDirection(direction);
}

//
// GetCurrentPositionFrame
//
template< class TOutputVideoStream >
unsigned long
VideoGrabber< TOutputVideoStream >
::GetCurrentPositionFrame()
{
  if(m_VideoGrabberInterface.IsNull())
    {
    this->InitializeVideoGrabber();
    }
  return m_VideoGrabberInterface->GetCurrentFrame();
}


//
// GetCurrentPositionRatio
//
template< class TOutputVideoStream >
double
VideoGrabber< TOutputVideoStream >
::GetCurrentPositionRatio()
{
  if(m_VideoGrabberInterface.IsNull())
    {
    this->InitializeVideoGrabber();
    }
  return m_VideoGrabberInterface->GetRatio();
}


//
// GetCurrentPositionMSec
//
template< class TOutputVideoStream >
double
VideoGrabber< TOutputVideoStream >
::GetCurrentPositionMSec()
{
  if(m_VideoGrabberInterface.IsNull())
    {
    this->InitializeVideoGrabber();
    }
  return m_VideoGrabberInterface->GetPositionInMSec();
}


//
// GetNumberOfFrames
//
template< class TOutputVideoStream >
unsigned long
VideoGrabber< TOutputVideoStream >
::GetNumberOfFrames()
{
  if(m_VideoGrabberInterface.IsNull())
    {
    this->InitializeVideoGrabber();
    }
  return m_VideoGrabberInterface->GetFrameTotal();
}


//
// GetFpS
//
template< class TOutputVideoStream >
double
VideoGrabber< TOutputVideoStream >
::GetFpS()
{
  if(m_VideoGrabberInterface.IsNull())
    {
    this->InitializeVideoGrabber();
    }
  return m_VideoGrabberInterface->GetFpS();
}

//
// InitializeVideoGrabber
//
template< class TOutputVideoStream >
void
VideoGrabber< TOutputVideoStream >
::InitializeVideoGrabber()
{
// todo: decide where to set the cameraID
  m_VideoGrabberInterface = itk::VideoGrabberInterfaceFactory::CreateVideoGrabber(0);
  m_VideoGrabberInterface->SetCameraIndex(0);
  m_VideoGrabberInterface->ReadImageInformation();

  // Make sure the input video has the same number of dimensions as the desired
  // output
  //
  // Note: This may be changed with the implementation of the Image
  //       Interpretation Layer
  if (m_VideoGrabberInterface->GetNumberOfDimensions() != FrameType::ImageDimension)
  	{
	itkExceptionMacro("Cannot convert " << m_VideoGrabberInterface->GetNumberOfDimensions() << "D "
	  "image set to " << FrameType::ImageDimension << "D");
	}

  // See if a buffer conversion is needed
  VideoGrabberInterfaceBase::IOComponentType ioType = VideoGrabberInterface
    ::MapPixelType< ITK_TYPENAME ConvertPixelTraits::ComponentType >::CType;
  if ( m_VideoGrabberInterface->GetComponentType() != ioType ||
       m_VideoGrabberInterface->GetNumberOfComponents() != ConvertPixelTraits::GetNumberOfComponents() )
    {
    // the pixel types don't match so a type conversion needs to be
    // performed
    itkDebugMacro( << "Buffer conversion required from: "
                   << m_VideoGrabberInterface->GetComponentTypeAsString(m_VideoGrabber->GetComponentType())
                   << " to: "
                   << m_VideoGrabberInterface->GetComponentTypeAsString(ioType)
                   << " ConvertPixelTraits::NumComponents "
                   << ConvertPixelTraits::GetNumberOfComponents()
                   << " m_VideoGrabberInterface->GetNumberOfComponents "
                   << m_VideoGrabberInterface->GetNumberOfComponents() );
    m_PixelConversionNeeded = true;
    }
  else
    {
    m_PixelConversionNeeded = false;
    }
}


//
// TemporalStreamingGenerateData
//
template< class TOutputVideoStream >
void
VideoGrabber< TOutputVideoStream >
::TemporalStreamingGenerateData()
{
  // Allocate the output frames
  this->AllocateOutputs();

  // Get the current frame number
  unsigned long frameNum = this->GetOutput()->GetRequestedTemporalRegion().GetFrameStart();

  // Figure out if we need to skip frames
  unsigned long currentIOFrame = m_VideoGrabberInterface->GetCurrentFrame();
  if (frameNum != currentIOFrame)
    {
    m_VideoGrabberInterface->SetNextFrameToRead(frameNum);
    }

  // Read a single frame
  if (m_PixelConversionNeeded)
    {
    // Set up temporary buffer for reading
    size_t bufferSize = m_VideoGrabberInterface->GetImageSizeInBytes();
    char* loadBuffer = new char[bufferSize];

    // Read into a temporary buffer
    m_VideoGrabberInterface->GrabSingleFrame(static_cast<void*>(loadBuffer));

    // Convert the buffer into the output buffer location
    this->DoConvertBuffer(static_cast<void*>(loadBuffer), frameNum);
    }
  else
    {
    FrameType* frame = this->GetOutput()->GetFrame(frameNum);
    m_VideoGrabberInterface->GrabSingleFrame(reinterpret_cast<void*>(frame->GetBufferPointer()));
    }

  // Mark ourselves modified
  this->Modified();
}


//
// DoConvertBuffer (much borrowed from itkImageFileReader)
//
template< class TOutputVideoStream >
void
VideoGrabber< TOutputVideoStream >::
DoConvertBuffer(void* inputData, unsigned long frameNumber)
{
  PixelType* outputData =
    this->GetOutput()->GetFrame(frameNumber)->GetPixelContainer()->GetBufferPointer();
  unsigned int numberOfPixels =
    this->GetOutput()->GetFrame(frameNumber)->GetPixelContainer()->Size();
  bool isVectorImage(strcmp(this->GetOutput()->GetFrame(frameNumber)->GetNameOfClass(),
                            "VectorImage") == 0);
                            
#define ITK_CONVERT_BUFFER_IF_BLOCK(_CType,type)                        \
  else if(m_VideoGrabberInterface->GetComponentType() == _CType)        \
    {                                                                   \
    if (isVectorImage)                                                  \
      {                                                                 \
      ConvertPixelBuffer<type,                                          \
                         PixelType,                                     \
                         ConvertPixelTraits                             \
                         >                                              \
        ::ConvertVectorImage(static_cast< type * >( inputData ),        \
                             m_VideoGrabber->GetNumberOfComponents(),   \
                             outputData,                                \
                             numberOfPixels);                           \
      }                                                                 \
    else                                                                \
      {                                                                 \
      ConvertPixelBuffer<type,                                          \
                         PixelType,                                     \
                         ConvertPixelTraits                             \
                         >                                              \
        ::Convert(static_cast< type * >( inputData ),                   \
                  m_VideoGrabber->GetNumberOfComponents(),              \
                  outputData,                                           \
                  numberOfPixels);                                      \
      }                                                                 \
    }

  if(0) {}
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::UCHAR,unsigned char)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::CHAR,char)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::USHORT,unsigned short)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::SHORT,short)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::UINT,unsigned int)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::INT,int)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::ULONG,unsigned long)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::LONG,long)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::FLOAT,float)
  ITK_CONVERT_BUFFER_IF_BLOCK(ImageIOBase::DOUBLE,double)
  else
    {
#define TYPENAME_VideoGrabber(x)                                     \
    m_VideoGrabberInterface->GetComponentTypeAsString                 \
      (ImageIOBase::MapPixelType<x>::CType)

    ExceptionObject e(__FILE__, __LINE__);
    std::ostringstream       msg;
    msg << "Couldn't convert component type: "
        << std::endl << "    "
        << m_VideoGrabber->GetComponentTypeAsString( m_VideoGrabber->GetComponentType() )
        << std::endl << "to one of: "
        << std::endl << "    " << TYPENAME_VideoGrabber( unsigned char )
        << std::endl << "    " << TYPENAME_VideoGrabber( char )
        << std::endl << "    " << TYPENAME_VideoGrabber( unsigned short )
        << std::endl << "    " << TYPENAME_VideoGrabber( short )
        << std::endl << "    " << TYPENAME_VideoGrabber( unsigned int )
        << std::endl << "    " << TYPENAME_VideoGrabber( int )
        << std::endl << "    " << TYPENAME_VideoGrabber( unsigned long )
        << std::endl << "    " << TYPENAME_VideoGrabber( long )
        << std::endl << "    " << TYPENAME_VideoGrabber( float )
        << std::endl << "    " << TYPENAME_VideoGrabber( double )
        << std::endl;
    e.SetDescription( msg.str().c_str() );
    e.SetLocation(ITK_LOCATION);
    throw e;
    return;
    }
#undef ITK_CONVERT_BUFFER_IF_BLOCK

}

} // end namespace itk

#endif
