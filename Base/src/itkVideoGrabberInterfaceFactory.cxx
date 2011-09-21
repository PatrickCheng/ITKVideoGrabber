/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkVideoGrabberInterfaceFactory.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#include "itkVideoGrabberInterfaceFactory.h"
#include "itkMutexLock.h"
#include "itkMutexLockHolder.h"

#ifdef VIDEO_GRABBER_USE_OpenCV
#include "itkOpenCVVideoGrabberInterfaceFactory.h"
#endif

#ifdef VIDEO_GRABBER_USE_Epiphan
#include "itkEpiphanGrabberInterfaceFactory.h"
#endif

namespace itk
{

VideoGrabberInterfaceBase::Pointer VideoGrabberInterfaceFactory::CreateVideoGrabber( int cameraID )
{
  RegisterBuiltInFactories();

  std::list< VideoGrabberInterfaceBase::Pointer > possibleVideoGrabber;
  std::list< LightObject::Pointer > allobjects =
    ObjectFactoryBase::CreateAllInstance("itkVideoGrabberInterfaceBase");

  for ( std::list< LightObject::Pointer >::iterator i = allobjects.begin();
        i != allobjects.end() ; ++i )
    {
      VideoGrabberInterfaceBase* io = dynamic_cast< VideoGrabberInterfaceBase* >( i->GetPointer() );
      if (io)
        {
        possibleVideoGrabber.push_back(io);
        }
      else
        {
        std::cerr << "Error VideoGrabber factory did not return a VideoGrabberInterfaceBase: "
                  << (*i)->GetNameOfClass() << std::endl;
        }
    }

  for ( std::list< VideoGrabberInterfaceBase::Pointer >::iterator j = possibleVideoGrabber.begin();
        j != possibleVideoGrabber.end() ; ++j )
    {
    
      if ((*j)->CanReadGrabber(cameraID))
        {
        return *j;
        }
    }

  // Didn't find a usable VideoGrabberInterface
  return 0;

}

void VideoGrabberInterfaceFactory::RegisterBuiltInFactories()
{
  static bool firstTime = true;

  static SimpleMutexLock mutex;

    {
    // This helper class makes sure the Mutex is unlocked
    // in the event an exception is thrown.
    MutexLockHolder< SimpleMutexLock > mutexHolder(mutex);
    if ( firstTime )
      {
#ifdef VIDEO_GRABBER_USE_OpenCV
      ObjectFactoryBase::RegisterFactory( OpenCVVideoGrabberInterfaceFactory::New() );
#endif

#ifdef VIDEO_GRABBER_USE_Epiphan
      ObjectFactoryBase::RegisterFactory( EpiphanVideoGrabberInterfaceFactory::New() );
#endif
      firstTime = false;
      }
    }
}

} // end namespace itk
