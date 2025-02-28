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

#ifndef __itkVideoGrabber_h
#define __itkVideoGrabber_h

#include "itkVideoSource.h"
#include "itkVideoGrabberInterfaceBase.h"
#include "itkDefaultConvertPixelTraits.h"

namespace itk
{

/** \class VideoGrabber
 * \brief Grabber captures a VideoStream from devices
 *
 * This class is responsible for reading video information from frame grabbers. It is a
 * subclass of VideoSource, giving it functionality to connect to other
 * TemporalProcessObject classes (specifically, VideoToVideoFilter classes). It
 * uses the temporal streaming implementation provided by TemporalProcessObject
 * to acquire a single frame at a time into the frame buffer of the output
 * VideoSource.
 *
 * \ingroup Video-Grabber
 */
template< class TOutputVideoStream >
class ITK_EXPORT VideoGrabber : public VideoSource< TOutputVideoStream >
{
public:

  typedef VideoGrabber                      Self;
  typedef VideoSource< TOutputVideoStream > Superclass;
  typedef SmartPointer<Self>                Pointer;
  typedef TOutputVideoStream                VideoStreamType;

  typedef typename TOutputVideoStream::FrameType OutputFrameType;
  typedef typename OutputFrameType::RegionType   OutputFrameSpatialRegionType;
  typedef typename OutputFrameType::PixelType    OutputFramePixelType;

  /** Pixel conversion typedefs */
  typedef DefaultConvertPixelTraits<OutputFramePixelType> ConvertPixelTraits;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(VideoGrabber, VideoSource);

  /** Specify the device number to acquire from. This is forwarded to the
   * VideoGrabberInterfaceBase instance. */
  itkSetMacro(DeviceNumber, int);
  itkGetMacro(DeviceNumber, int);

  /** Get/Set IFrameSafe. If true, the last IFrame will be reported as the last
   * frame for the largest possible temporal region */
  itkSetMacro(IFrameSafe, bool);
  itkGetMacro(IFrameSafe, bool);

  /** Set up the output information */
  virtual void UpdateOutputInformation();

  /** Set the internal VideoGrabberInterfaceBase pointer */
  void SetVideoGrabberInterface(VideoGrabberInterfaceBase*);

  /** Get the current position as frame, ratio, or MSec */
  unsigned long GetCurrentPositionFrame();
  double GetCurrentPositionRatio();
  double GetCurrentPositionMSec();

  /** Get number of frames */
  unsigned long GetNumberOfFrames();

  /** Get framerate */
  double GetFpS();

protected:

  VideoGrabber();
  virtual ~VideoGrabber();

  void PrintSelf(std::ostream &os, Indent indent) const;

  /** Override TemporalStreamingGenerateData to generate output a single frame.
   * We don't override ThreadedGenerateData because we read whole frames one at
   * a time. As such, we have to handle the allocation of the frames here. */
  virtual void TemporalStreamingGenerateData();

  /** Convert buffer for output */
  void DoConvertBuffer(void* inputData, unsigned long frameNumber);

  /** Set up a new VideoGrabberInterface using VideoGrabberInterfaceFactory
   * Warning: this will overwrite any currently set VideoGrabberInterface */
  void InitializeVideoGrabber();

  /** The device ID to open */
  int m_DeviceNumber;

  /** VideoGrabberInterfaceBase used to acquire video */
  VideoGrabberInterfaceBase::Pointer m_VideoGrabberInterface;

  /** Flag to store whether or not the pixel type needs to be converted */
  bool m_PixelConversionNeeded;

  /** Flag to indicate whether to report the last frame as the last IFrame. On
   * by default */
  bool m_IFrameSafe;

private:
  VideoGrabber(const Self &); // purposely not implemented
  void operator=(const Self &);  // purposely not implemented

};


} // end namespace itk

#if ITK_TEMPLATE_TXX
#include "itkVideoGrabber.txx"
#endif

#endif 
