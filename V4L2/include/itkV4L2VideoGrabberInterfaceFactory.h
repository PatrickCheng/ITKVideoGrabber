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
#ifndef __itkV4L2VideoGrabberInterfaceFactory_h
#define __itkV4L2VideoGrabberInterfaceFactory_h

#include "itkObjectFactoryBase.h"
#include "itkVideoIOBase.h"

namespace itk
{
/** \class V4L2VideoGrabberInterfaceFactory
 * \brief Create instances of V4L2VideoGrabberInterface objects using an object factory.
 *
 * \ingroup Video-Grabber-V4L2
 */
class ITK_EXPORT V4L2VideoGrabberInterfaceFactory: public ObjectFactoryBase
{
public:
  /** Standard class typedefs. */
  typedef V4L2VideoGrabberInterfaceFactory     Self;
  typedef ObjectFactoryBase          Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Class methods used to interface with the registered factories. */
  virtual const char * GetITKSourceVersion(void) const;

  virtual const char * GetDescription(void) const;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(V4L2VideoGrabberInterfaceFactory, ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  {
    V4L2VideoGrabberInterfaceFactory::Pointer FileListFactory = V4L2VideoGrabberFactory::New();

    ObjectFactoryBase::RegisterFactoryInternal(FileListFactory);
  }

protected:
  V4L2VideoGrabberInterfaceFactory();
  ~V4L2VideoGrabberInterfaceFactory();

private:
  V4L2VideoGrabberInterfaceFactory(const Self &); //purposely not implemented
  void operator=(const Self &);    //purposely not implemented

};

} // end namespace itk

#endif
