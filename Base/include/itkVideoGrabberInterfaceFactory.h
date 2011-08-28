/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkVideoGrabberInterfaceFactory.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkVideoGrabberInterfaceFactory_h
#define __itkVideoGrabberInterfaceFactory_h

#include "itkObject.h"
#include "itkVideoGrabberInterfaceBase.h"


namespace itk
{

/** \class VideoGrabberInterfaceFactory
 * \brief Create instances of VideoGrabberInterface objects using an object factory.
 *
 * This class will create a VideoGrabberInterface instance that can acquire video from the
 * desired camera. In order for a specific VideoGrabberInterface type to be
 * considered, it must be registered with the ITK ObjectFactoryBase.
 *
 * \ingroup Video-IO-Base
 */
class ITK_EXPORT VideoGrabberInterfaceFactory:public Object
{
public:
  /** Standard class typedefs. */
  typedef VideoGrabberInterfaceFactory        Self;
  typedef Object                     Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Mode in which the VideoGrabber is intended to be used */
  typedef enum { ReadFileMode, ReadCameraMode, WriteMode } IOModeType;

  /** Runtime type information (and related methods). **/
  itkTypeMacro(VideoGrabberInterfaceFactory, Object);

  /** Create the appropriate ImageIO depending on the particulars of the file.
   *  Note: arg can either be a path for reading/writing from/to a file or a
   *        a string containing an integer to use for a cameraID if reading
   *        from a camera
   */
  static VideoGrabberInterfaceBase::Pointer CreateVideoGrabber( IOModeType mode, const char* arg );

  /** Register Builtin factories **/
  static void RegisterBuiltInFactories();

protected:
  VideoGrabberInterfaceFactory();
  ~VideoGrabberInterfaceFactory();

private:
  VideoGrabberInterfaceFactory(const Self &); //purposely not implemented
  void operator=(const Self &);     //purposely not implemented
};

} // end namespace itk


#endif
