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
#ifndef __itkEpiphanVideoGrabberInterfaceFactory_h
#define __itkEpiphanVideoGrabberInterfaceFactory_h

#include "itkObjectFactoryBase.h"
#include "itkVideoIOBase.h"

namespace itk
{
/** \class EpiphanVideoGrabberInterfaceFactory
 * \brief Create instances of EpiphanVideoGrabberInterface objects using an object factory.
 *
 * \ingroup Video-Grabber-Epiphan
 */
class ITK_EXPORT EpiphanVideoGrabberInterfaceFactory: public ObjectFactoryBase
{
public:
  /** Standard class typedefs. */
  typedef EpiphanVideoGrabberInterfaceFactory     Self;
  typedef ObjectFactoryBase          Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Class methods used to interface with the registered factories. */
  virtual const char * GetITKSourceVersion(void) const;

  virtual const char * GetDescription(void) const;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(EpiphanVideoGrabberInterfaceFactory, ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  {
    EpiphanVideoGrabberInterfaceFactory::Pointer epiphanFactory = EpiphanVideoGrabberInterfaceFactory::New();

    ObjectFactoryBase::RegisterFactoryInternal(epiphanFactory);
  }

protected:
  EpiphanVideoGrabberInterfaceFactory();
  ~EpiphanVideoGrabberInterfaceFactory();
private:
  EpiphanVideoGrabberInterfaceFactory(const Self &); //purposely not implemented
  void operator=(const Self &);    //purposely not implemented
};
} // end namespace itk

#endif
