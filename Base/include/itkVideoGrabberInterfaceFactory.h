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

#define VIDEO_GRABBER_USE_OpenCV

#include "itkObjectFactoryBase.h"
#include "itkVideoGrabberInterfaceBase.h"


namespace itk
{

/** \class VideoGrabberInterfaceFactory
 * \brief Create instances of VideoGrabberInterface objects using an object factory.
 *
 * This class will create a VideoGrabberInterfaceBase instance that can acquire video from the
 * desired camera. In order for a specific VideoGrabberInterfaceBase type to be
 * considered, it must be registered with the ITK ObjectFactoryBase.
 *
 * \ingroup Video-IO-Base
 */
class ITK_EXPORT VideoGrabberInterfaceFactory : public ObjectFactoryBase
{
public:
  /** Standard class typedefs. */
  typedef VideoGrabberInterfaceFactory        Self;
  typedef Object                     Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Runtime type information (and related methods). **/
  itkTypeMacro(VideoGrabberInterfaceFactory, ObjectFactoryBase);

  /** Create the a video grabber interface for a given cameraID  */
  static VideoGrabberInterfaceBase::Pointer CreateVideoGrabber( int cameraID );

  /** Register builtin factories **/
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
