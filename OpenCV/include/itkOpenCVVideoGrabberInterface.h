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
#ifndef __itkOpenCVVideoGrabberInterface_h
#define __itkOpenCVVideoGrabberInterface_h

// Define support for OpenCVVideo
#ifndef ITK_VIDEO_USE_OPENCV
#define ITK_VIDEO_USE_OPENCV
#endif

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#include "itkVideoGrabberInterfaceBase.h"
#include "cv.h"
#include "highgui.h"


namespace itk
{
/** \class OpenCVVideoGrabberInterface
 *
 * \brief Video grabber interface class using OpenCV
 *
 * \ingroup Video-Grabber-OpenCV
 */
class ITK_EXPORT OpenCVVideoGrabberInterface: public VideoGrabberInterfaceBase
{
public:
  /** Standard class typedefs. */
  typedef OpenCVVideoGrabberInterface Self;
  typedef VideoGrabberInterfaceBase   Superclass;
  typedef SmartPointer< Self > Pointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(OpenCVVideoGrabberInterface, Superclass);

  /** Establish connection and opens the active frame grabber
  * it it is not already open */
  virtual bool OpenGrabber(int index);

  /** Disconnect the active frame grabber */
  virtual bool CloseGrabber();

  /** Start grabbing from active device */
  virtual bool StartGrabbing();

  /** Stop active device */
  virtual bool StopGrabbing();

  /** Grab a single frame into the memory buffer provided. */
  virtual bool GrabSingleFrame(void *buffer);

  /** Return whether or not we can read from a given grabber */
  virtual bool CanReadGrabber( unsigned long grabberID );

  /** Set the spacing and dimension information for the set filename. */
  virtual void ReadImageInformation();

  /** Accessor functions for video specific information */
  virtual double GetPositionInMSec();
  virtual double GetRatio();
  virtual unsigned long GetFrameTotal();
  virtual double GetFpS();
  virtual unsigned long GetCurrentFrame();
  virtual unsigned int GetIFrameInterval();
  virtual unsigned long GetLastIFrame();

  /** Get/Set the camera index */
  virtual void SetCameraIndex(int idx);
  virtual int GetCameraIndex();

protected:
  OpenCVVideoGrabberInterface();
  ~OpenCVVideoGrabberInterface();

  void PrintSelf(std::ostream & os, Indent indent) const;

  /** Update the local members from the internal capture */
  void UpdateGrabberProperties();

  /** Reset member variables to empty state closed */
  void ResetMembers();


private:
  OpenCVVideoGrabberInterface(const Self &);     //purposely not implemented
  void operator=(const Self &); //purposely not implemented

  /** Member Variables */
  IplImage*           m_CVImage;
  IplImage*           m_TempImage;
  CvCapture*          m_Capture;
  int                 m_FourCC;

};
} // end namespace itk

#endif // __itkOpenCVVideoGrabberInterface_h
