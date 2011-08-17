/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkVideoIOFactory.cxx
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

#include "itkVideoGrabberFactory.h"
#include "itkMutexLock.h"
#include "itkMutexLockHolder.h"

#ifdef ITK_VIDEO_USE_OPENCV
#include "itkOpenCVVideoGrabberFactory.h"
#endif

#ifdef ITK_VIDEO_USE_EPIPHAN
#include "itkEpiphanGrabberFactory.h"
#endif

namespace itk
{
VideoGrabberBase::Pointer VideoGrabberFactory::CreateVideoGrabber( IOModeType mode, const char* arg )
{
  RegisterBuiltInFactories();

  std::list< VideoGrabberBase::Pointer > possibleVideoGrabber;
  std::list< LightObject::Pointer > allobjects =
    ObjectFactoryBase::CreateAllInstance("itkVideoGrabberBase");

  for ( std::list< LightObject::Pointer >::iterator i = allobjects.begin();
        i != allobjects.end() ; ++i )
    {

    VideoGrabberBase* io = dynamic_cast< VideoGrabberBase* >( i->GetPointer() );
    if (io)
      {
      possibleVideoGrabber.push_back(io);
      }
    else
      {
      std::cerr << "Error VideoGrabber factory did not return a VideoGrabberBase: "
                << (*i)->GetNameOfClass() << std::endl;
      }
    }

  for ( std::list< VideoGrabberBase::Pointer >::iterator j = possibleVideoGrabber.begin();
        j != possibleVideoGrabber.end() ; ++j )
    {
    
    // Check file readability if reading from file
    if (mode == ReadFileMode)
      {
      if ((*j)->CanReadFile(arg))
        {
        return *j;
        }
      }

    // Check camera readability if reading from camera
    else if (mode == ReadCameraMode)
      {
      if ((*j)->CanReadCamera(atoi(arg)))
        {
        return *j;
        }
      }

    // Check file writability if writing
    else if (mode == WriteMode)
      {
      if ((*j)->CanWriteFile(arg))
        {
        return *j;
        }
      }
    
    }

  // Didn't find a usable VideoGrabber
  return 0;

}

void VideoGrabberFactory::RegisterBuiltInFactories()
{
  static bool firstTime = true;

  static SimpleMutexLock mutex;

    {
    // This helper class makes sure the Mutex is unlocked
    // in the event an exception is thrown.
    MutexLockHolder< SimpleMutexLock > mutexHolder(mutex);
    if ( firstTime )
      {
#ifdef ITK_VIDEO_USE_OPENCV
      ObjectFactoryBase::RegisterFactory( OpenCVVideoGrabberFactory::New() );
#endif

#ifdef ITK_VIDEO_USE_Epiphan
      ObjectFactoryBase::RegisterFactory( EpiphanVideoGrabberFactory::New() );
#endif
      
      firstTime = false;
      }
    }
}

} // end namespace itk
