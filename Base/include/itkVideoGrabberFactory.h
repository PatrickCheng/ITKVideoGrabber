/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkVideoIOFactory.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkVideoGrabberFactory_h
#define __itkVideoGrabberFactory_h

#include "itkObject.h"
#include "itkVideoGrabberBase.h"


namespace itk
{

/** \class VideoGrabberFactory
 * \brief Create instances of VideoGrabber objects using an object factory.
 *
 * This class will create a VideoGrabber instance that can read/write to/from the
 * desired file or camera. In order for a specific VideoGrabber type to be
 * considered, it must be registered with the ITK ObjectFactoryBase.
 *
 * \ingroup Video-IO-Base
 */
class ITK_EXPORT VideoGrabberFactory:public Object
{
public:
  /** Standard class typedefs. */
  typedef VideoGrabberFactory             Self;
  typedef Object                     Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Mode in which the VideoGrabber is intended to be used */
  typedef enum { ReadFileMode, ReadCameraMode, WriteMode } IOModeType;

  /** Runtime type information (and related methods). **/
  itkTypeMacro(VideoGrabberFactory, Object);

  /** Create the appropriate ImageIO depending on the particulars of the file.
   *  Note: arg can either be a path for reading/writing from/to a file or a
   *        a string containing an integer to use for a cameraID if reading
   *        from a camera
   */
  static VideoGrabberBase::Pointer CreateVideoGrabber( IOModeType mode, const char* arg );

  /** Register Builtin factories **/
  static void RegisterBuiltInFactories();

protected:
  VideoGrabberFactory();
  ~VideoGrabberFactory();
private:
  VideoGrabberFactory(const Self &); //purposely not implemented
  void operator=(const Self &);     //purposely not implemented
};

} // end namespace itk


#endif
