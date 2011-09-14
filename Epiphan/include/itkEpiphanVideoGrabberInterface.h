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
#ifndef __itkEpiphanVideoGrabberInterface_h
#define __itkEpiphanVideoGrabberInterface_h

// Define support for EpiphanVideo
#ifndef ITK_VIDEO_USE_EPIPHAN
#define ITK_VIDEO_USE_EPIPHAN
#endif

#include "itkVideoGrabberInterfaceBase.h"

namespace itk
{
/** \class EpiphanVideoGrabberInterface
 *
 * \brief Video grabber interface class using Epiphan
 *
 *
 * \ingroup Video-Grabber-Epiphan
 *
 */
class ITK_EXPORT EpiphanVideoGrabberInterface: public VideoGrabberInterfaceBase
{
public:
  /** Standard class typedefs. */
  typedef EpiphanVideoGrabberInterface       Self;
  typedef VideoGrabberInterfaceBase          Superclass;
  typedef SmartPointer< Self > Pointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(EpiphanVideoGrabberInterface, Superclass);

  /** Return whether or not we can acquire video from a given device */
  virtual bool CanReadGrabber( unsigned long cameraID );

  /** Set the spacing and dimension information for the set filename. */
  virtual void ReadImageInformation();

  /** Grab a single frame into the memory buffer provided. */
  virtual bool GrabSingleFrame(void *buffer);

  /** Close the active device */
  virtual bool CloseGrabber();

  /** Set device #index as the active */
  virtual bool OpenGrabber(int index);

  /** Start grabbing from active device */
  virtual bool StartGrabbing();

  /** Stop active device */
  virtual bool StopGrabbing();

  /** Accessor functions for video specific information */
  virtual double GetPositionInMSec();
  virtual double GetRatio();
  virtual unsigned long GetFrameTotal();
  virtual double GetFpS();
  virtual unsigned long GetCurrentFrame();
  virtual unsigned int GetIFrameInterval();
  virtual unsigned long GetLastIFrame();

  /** Override Accessors to pass through to internal image reader */
  virtual double GetSpacing(unsigned int i) const;
  virtual double GetOrigin(unsigned int i) const;
  virtual std::vector< double > GetDirection(unsigned int i) const;

  /** Get/Set the camera index */
  virtual void SetCameraIndex(int idx);
  virtual int GetCameraIndex();

protected:
  EpiphanVideoGrabberInterface();
  ~EpiphanVideoGrabberInterface();

  void PrintSelf(std::ostream & os, Indent indent) const;

  /** Reset member variables to empty state closed */
  void ResetMembers();

  void UpdateGrabberProperties();

private:
  EpiphanVideoGrabberInterface(const Self &);     //purposely not implemented
  void operator=(const Self &); //purposely not implemented

};
} // end namespace itk

#endif // __itkEpiphanVideoGrabberInterface_h
