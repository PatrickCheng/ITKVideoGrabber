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
#ifndef __itkVideoGrabberInterfaceBase_h
#define __itkVideoGrabberInterfaceBase_h

#include "itkLightProcessObject.h"
#include "itkExceptionObject.h"
#include "vnl/vnl_vector.h"

#include <string>

namespace itk
{
/** \class VideoGrabberInterfaceBase
 * \brief Abstract superclass defines video grabber interface.
 *
 * VideoGrabberInterfaceBase is an abstract base class for ITK video grabber classes
 *
 * A Pluggable factory pattern is used. This allows different kinds of
 * frame grabbers to be registered (even at run time) without having to
 * modify the code in this class.
 *
 * \sa VideoFileWriter
 * \sa VideoFileReader
 *
 * \ingroup Video-Grabber-Base
 */
class ITK_EXPORT VideoGrabberInterfaceBase: public LightProcessObject
{
public:

     // enums
     enum VideoMode
     {
         e320x240,
         e640x480,
         e800x600,
         e768x576,
         e1024x768,
         e1280x960,
         e1600x1200,
         eNone
     };

     enum ColorMode
     {
         eRGB24,
         eBayerPatternToRGB24,
         eGrayScale,
         eYUV411ToRGB24
     };

     enum FrameRate
     {
         e60fps,
         e30fps,
         e15fps,
         e7_5fps,
         e3_75fps,
         e1_875fps
     };

     /** Enums used to manipulate the pixel type. The pixel type provides
        * context for automatic data conversions (for instance, RGB to
        * SCALAR, VECTOR to SCALAR). */
       typedef  enum { UNKNOWNPIXELTYPE, SCALAR, RGB, RGBA }  VideoFramePixelType;

public:

  /** Standard class typedefs. */
  typedef VideoGrabberInterfaceBase   Self;
  typedef LightProcessObject          Superclass;
  typedef SmartPointer< Self > Pointer;
  typedef unsigned int         SizeValueType;

  /** Run-time type information (and related methods). */
  itkTypeMacro(VideoGrabberInterfaceBase, Superclass);

  /** Establish connection and opens the active frame grabber */
  virtual bool OpenGrabber() = 0;

  /** Disconnect the active frame grabber */
  virtual bool CloseGrabber() = 0;

  /** Start grabbing from active device */
  virtual bool StartGrabbing() = 0;

  /** Grab a single frame into the memory buffer provided. */
  virtual bool GrabSingleFrame(void *buffer) = 0;

  /** Stop active device */
  virtual bool StopGrabbing() = 0;

  /** Return whether or not we can read from a given grabber */
  virtual bool CanReadGrabber( unsigned long grabberID ) = 0;

  /** Virtual accessor functions to be implemented in each derived class */
  virtual double GetPositionInMSec() = 0;
  virtual double GetRatio() = 0;
  virtual unsigned long GetFrameTotal() = 0;
  virtual double GetFpS() = 0;
  virtual unsigned long GetCurrentFrame() = 0;
  virtual unsigned long GetLastIFrame() = 0;


protected:
  VideoGrabberInterfaceBase(){};
  ~VideoGrabberInterfaceBase(){};

  void PrintSelf(std::ostream & os, Indent indent) const;
  
  /** Member Variables */
  double          m_FpS;
  unsigned long   m_FrameTotal;
  unsigned long   m_CurrentFrame;
  unsigned int    m_IFrameInterval;
  unsigned long   m_LastIFrame;
  double          m_Ratio;
  double          m_PositionInMSec;
  bool            m_GrabberIsOpen;

  /** device index for reading from a camera (may move to base class) */
  int m_CameraIndex;

  /** The array which stores the number of pixels in the x, y, z directions. */
   std::vector< SizeValueType > m_Dimensions;

   /** The array which stores the spacing of pixels in the
    * x, y, z directions. */
   std::vector< double > m_Spacing;

   /** The array which stores the origin of the image. */
   std::vector< double > m_Origin;

   /** The arrays which store the direction cosines of the image. */
   std::vector< std::vector< double > > m_Direction;

   /** Stores the number of components per pixel. This will be 1 for
      * grayscale images, 3 for RGBPixel images, and 4 for RGBPixelA images. */
   unsigned int m_NumberOfComponents;

   /** Used internally to keep track of the type of the pixel. */
   VideoFramePixelType m_PixelType;

private:
  VideoGrabberInterfaceBase(const Self &);    //purposely not implemented
  void operator=(const Self &); //purposely not implemented

};


} // end namespace itk

#endif // __itkVideoGrabberInterfaceBase_h