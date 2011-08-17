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
#include "itkOpenCVVideoGrabberFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkOpenCVVideoGrabber.h"
#include "itkVersion.h"

namespace itk
{
OpenCVVideoGrabberFactory::OpenCVVideoGrabberFactory()
{
  this->RegisterOverride( "itkVideoGrabberBase",
                          "itkOpenCVVideoGrabber",
                          "OpenCV Video IO",
                          1,
                          CreateObjectFunction< OpenCVVideoGrabber >::New() );
}

OpenCVVideoGrabberFactory::~OpenCVVideoGrabberFactory()
{}

const char *
OpenCVVideoGrabberFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char *
OpenCVVideoGrabberFactory::GetDescription() const
{
  return "OpenCV VideoGrabber Factory, allows the loading of AVI videos into Insight";
}

// Undocumented API used to register during static initialization.
// DO NOT CALL DIRECTLY.

static bool OpenCVVideoGrabberFactoryHasBeenRegistered;

void OpenCVVideoGrabberFactoryRegister__Private(void)
{
  if( ! OpenCVVideoGrabberFactoryHasBeenRegistered )
    {
    OpenCVVideoGrabberFactoryHasBeenRegistered = true;
    OpenCVVideoGrabberFactory::RegisterOneFactory();
    }
}

} // end namespace itk
