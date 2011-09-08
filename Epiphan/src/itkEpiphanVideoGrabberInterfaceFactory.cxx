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

#include "itkEpiphanVideoGrabberInterfaceFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkEpiphanVideoGrabberInterface.h"
#include "itkVersion.h"

namespace itk
{

EpiphanVideoGrabberInterfaceFactory::EpiphanVideoGrabberInterfaceFactory()
{
  this->RegisterOverride( "itkVideoGrabberInterfaceBase",
                            "itkEpiphanVideoGrabberInterface",
                            "Epiphan VideoGrabber",
                            1,
                            CreateObjectFunction< EpiphanVideoGrabberInterface >::New() );
}

EpiphanVideoGrabberInterfaceFactory::~EpiphanVideoGrabberInterfaceFactory()
{}

const char *
EpiphanVideoGrabberInterfaceFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char *
EpiphanVideoGrabberInterfaceFactory::GetDescription() const
{
  return "FileList VideoIO Factory, allows the loading of a list of image files as a videos into Insight";
}

// Undocumented API used to register during static initialization.
// DO NOT CALL DIRECTLY.

static bool EpiphanVideoGrabberInterfaceFactoryHasBeenRegistered;

void EpiphanVideoGrabberInterfaceFactoryRegister__Private(void)
{
  if( ! EpiphanVideoGrabberInterfaceFactoryHasBeenRegistered )
    {
      EpiphanVideoGrabberInterfaceFactoryHasBeenRegistered = true;
      EpiphanVideoGrabberInterfaceFactory::RegisterOneFactory();
    }
}

} // end namespace itk
