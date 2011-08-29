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
#include "itkV4L2VideoGrabberInterfaceFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkV4L2VideoGrabberInterface.h"
#include "itkVersion.h"

namespace itk
{
V4L2VideoGrabberInterfaceFactory::V4L2VideoGrabberInterfaceFactory()
{
  this->RegisterOverride( "itkVideoGrabberInterfaceBase",
                          "itkV4L2VideoGrabberInterface",
                          "V4L2 VideoGrabber",
                          1,
                          CreateObjectFunction< V4L2VideoGrabberInterface >::New() );
}

V4L2VideoGrabberInterfaceFactory::~V4L2VideoGrabberInterfaceFactory()
{}

const char *
V4L2VideoGrabberInterfaceFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char *
V4L2VideoGrabberInterfaceFactory::GetDescription() const
{
  return "V4L2 VideoGrabberInterface Factory, allows the acquisition of video into the Insight Toolkit";
}

// Undocumented API used to register during static initialization.
// DO NOT CALL DIRECTLY.

static bool V4L2VideoGrabberInterfaceFactoryHasBeenRegistered;

void V4L2VideoGrabberInterfaceFactoryRegister__Private(void)
{
  if( ! V4L2VideoGrabberInterfaceFactoryHasBeenRegistered )
    {
    V4L2VideoGrabberInterfaceFactoryHasBeenRegistered = true;
    V4L2VideoGrabberInterfaceFactory::RegisterOneFactory();
    }
}

} // end namespace itk
