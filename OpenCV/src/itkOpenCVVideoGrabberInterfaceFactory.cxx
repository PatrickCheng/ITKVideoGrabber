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
#include "itkOpenCVVideoGrabberInterfaceFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkOpenCVVideoGrabberInterface.h"
#include "itkVersion.h"

namespace itk
{
OpenCVVideoGrabberInterfaceFactory::OpenCVVideoGrabberInterfaceFactory()
{
  this->RegisterOverride( "itkVideoGrabberInterfaceBase",
                          "itkOpenCVVideoGrabberInterface",
                          "OpenCV VideoGrabber",
                          1,
                          CreateObjectFunction< OpenCVVideoGrabberInterface >::New() );
}

OpenCVVideoGrabberInterfaceFactory::~OpenCVVideoGrabberInterfaceFactory()
{}

const char *
OpenCVVideoGrabberInterfaceFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char *
OpenCVVideoGrabberInterfaceFactory::GetDescription() const
{
  return "OpenCV VideoGrabberInterface Factory, allows the acquisition of video into the Insight Toolkit";
}

// Undocumented API used to register during static initialization.
// DO NOT CALL DIRECTLY.

static bool OpenCVVideoGrabberInterfaceFactoryHasBeenRegistered;

void OpenCVVideoGrabberInterfaceFactoryRegister__Private(void)
{
  if( ! OpenCVVideoGrabberInterfaceFactoryHasBeenRegistered )
    {
    OpenCVVideoGrabberInterfaceFactoryHasBeenRegistered = true;
    OpenCVVideoGrabberInterfaceFactory::RegisterOneFactory();
    }
}

} // end namespace itk
