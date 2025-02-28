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
#include "itkImageIOBase.h"
#include "itkExceptionObject.h"
#include "vnl/vnl_vector.h"

#include <string>

namespace itk
{
/** \class VideoGrabberInterfaceBase
 * \brief Abstract superclass defines video grabber interface.
 *
 * VideoGrabberInterfaceBase is an abstract base class for ITK video
 * grabber interface classes
 *
 * A pluggable factory pattern is used. This allows different kinds of
 * frame grabber interfaces to be registered (even at run time) without having to
 * modify the code in this class.
 *
 * \sa VideoStream
 *
 * \ingroup Video-Grabber-Base
 */
class ITK_EXPORT VideoGrabberInterfaceBase: public LightProcessObject
{
public:

public:

  /** Standard class typedefs. */
  typedef VideoGrabberInterfaceBase   Self;
  typedef LightProcessObject          Superclass;
  typedef SmartPointer< Self > Pointer;
  typedef unsigned int         SizeValueType;

  /** Run-time type information (and related methods). */
  itkTypeMacro(VideoGrabberInterfaceBase, Superclass);

  /** Type for representing size of bytes, and or positions along a file */
  typedef std::streamoff SizeType;

  /** Establish connection and opens the active frame grabber */
  virtual bool OpenGrabber(int index) = 0;

  /** Disconnect the active frame grabber */
  virtual bool CloseGrabber() = 0;

  /** Start grabbing from active device */
  virtual bool StartGrabbing() = 0;

  /** Grab a single frame into the memory buffer provided. */
  virtual bool GrabSingleFrame(void *buffer) = 0;

  /** Stop active device */
  virtual bool StopGrabbing() = 0;

  /** Return whether or not we can read from a given connected grabbing device */
  virtual bool CanReadGrabber( unsigned long grabberID ) = 0;

  /** Get acquisition parameters from the current (or default) grabbing device */
  virtual void ReadImageInformation() = 0;

  virtual bool SetNextFrameToRead(unsigned long frameNumber) = 0;

  /** Virtual accessor functions to be implemented in each derived class */
  virtual double GetPositionInMSec() = 0;
  virtual double GetRatio() = 0;
  virtual unsigned long GetFrameTotal() = 0;
  virtual double GetFpS() = 0;
  virtual unsigned long GetCurrentFrame() = 0;
  virtual unsigned long GetLastIFrame() = 0;

  /** Get/Set the camera index */
  virtual void SetCameraIndex(int idx) = 0;
  virtual int GetCameraIndex() = 0;

  /** Set/Get the number of independent variables (dimensions) in the
     * image being read or written. Note this is not necessarily what
     * is written, rather the IORegion controls that. */
    void SetNumberOfDimensions(unsigned int);

    itkGetConstMacro(NumberOfDimensions, unsigned int);

    /** Set/Get the image dimensions in the x, y, z, etc. directions.
     * GetDimensions() is typically used after reading the data; the
     * SetDimensions() is used prior to writing the data. */
    virtual void SetDimensions(unsigned int i, unsigned int dim);

    virtual unsigned int GetDimensions(unsigned int i) const
    { return m_Dimensions[i]; }

    /** Set/Get the image origin on a axis-by-axis basis. The SetOrigin() method
     * is required when writing the image. */
    virtual void SetOrigin(unsigned int i, double origin);

    virtual double GetOrigin(unsigned int i) const
    {
      return m_Origin[i];
    }

    /** Set/Get the image spacing on an axis-by-axis basis. The
     * SetSpacing() method is required when writing the image. */
    virtual void SetSpacing(unsigned int i, double spacing);

    virtual double GetSpacing(unsigned int i) const
    {
      return m_Spacing[i];
    }

    /** Set/Get the image direction on an axis-by-axis basis. The
     * SetDirection() method is required when writing the image. */
    virtual void SetDirection(unsigned int i, std::vector< double > & direction);

    virtual void SetDirection(unsigned int i, vnl_vector< double > & direction);

    virtual std::vector< double > GetDirection(unsigned int i) const
    {
      return m_Direction[i];
    }

    /** Return the directions to be assigned by default to recipient
     *  images whose dimension is smaller than the image dimension in file.  */
    virtual std::vector< double > GetDefaultDirection(unsigned int i) const;

   /** Return the number of pixels in the image. */
   SizeType GetImageSizeInPixels() const;

   /** Return the number of bytes in the image. */
   SizeType GetImageSizeInBytes() const;

   /** Return the number of pixels times the number
   * of components in the image. */
   SizeType GetImageSizeInComponents() const;

   /** Compute the size (in bytes) of the components of a pixel. For
   * example, an RGB pixel of unsigned char would have a
   * component size of 1 byte. This method can be invoked only after
   * the component type is set. */
  virtual unsigned int GetComponentSize() const;

   /** Set/Get the number of components per pixel in the image.
   * For SCALAR pixel types,
   * NumberOfComponents will be 1.  For other pixel types,
   * NumberOfComponents will be greater than or equal to one. */
  itkSetMacro(NumberOfComponents, unsigned int);
  itkGetConstReferenceMacro(NumberOfComponents, unsigned int);

  /** Set/Get the component type of the image. This is always a native
     * type. */
  itkSetEnumMacro(ComponentType, ImageIOBase::IOComponentType);
  itkGetEnumMacro(ComponentType, ImageIOBase::IOComponentType);

  /** Convenience method returns the VideoComponentType as a string. This can be
   * used for writing output files. */
//  static std::string GetComponentTypeAsString(ImageIOBase::IOComponentType);

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
  ImageIOBase::IOComponentType m_ComponentType;

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

   /** The number of independent dimensions in the image. */
   unsigned int m_NumberOfDimensions;

   /** Used internally to keep track of the pixel type. */
   ImageIOBase::IOPixelType m_PixelType;  

private:
  VideoGrabberInterfaceBase(const Self &);    //purposely not implemented
  void operator=(const Self &); //purposely not implemented

};


} // end namespace itk

#endif // __itkVideoGrabberInterfaceBase_h
