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
#include "itkLinux1394VideoGrabberInterfaceFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkLinux1394VideoGrabberInterface.h"
#include "itkVersion.h"

namespace itk
{
Linux1394VideoGrabberInterfaceFactory::Linux1394VideoGrabberInterfaceFactory()
{
  this->RegisterOverride( "itkVideoGrabberInterfaceBase",
                          "itkLinux1394VideoGrabberInterface",
                          "Linux1394 VideoGrabber",
                          1,
                          CreateObjectFunction< Linux1394VideoGrabberInterface >::New() );
}

Linux1394VideoGrabberInterfaceFactory::~Linux1394VideoGrabberInterfaceFactory()
{}

const char *
Linux1394VideoGrabberInterfaceFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char *
Linux1394VideoGrabberInterfaceFactory::GetDescription() const
{
  return "Linux1394 VideoGrabberInterface Factory, allows the acquisition of video into the Insight Toolkit";
}

// Undocumented API used to register during static initialization.
// DO NOT CALL DIRECTLY.

static bool Linux1394VideoGrabberInterfaceFactoryHasBeenRegistered;

void Linux1394VideoGrabberInterfaceFactoryRegister__Private(void)
{
  if( ! Linux1394VideoGrabberInterfaceFactoryHasBeenRegistered )
    {
    Linux1394VideoGrabberInterfaceFactoryHasBeenRegistered = true;
    Linux1394VideoGrabberInterfaceFactory::RegisterOneFactory();
    }
}

} // end namespace itk
