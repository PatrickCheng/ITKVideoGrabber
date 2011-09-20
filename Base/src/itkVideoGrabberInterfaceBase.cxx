/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkVideoGrabberInterfaceBase.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined( _MSC_VER )
#pragma warning ( disable : 4786 )
#endif

#include "itkVideoGrabberInterfaceBase.h"

namespace itk
{

void VideoGrabberInterfaceBase::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
}

void VideoGrabberInterfaceBase::SetDimensions(unsigned int i, unsigned int dim)
{
  if ( i >= m_Dimensions.size() )
    {
    itkWarningMacro( "Index: " << i
                               << " is out of bounds, expected maximum is "
                               << m_Dimensions.size() );
    itkExceptionMacro( "Index: " << i
                                 << " is out of bounds, expected maximum is "
                                 << m_Dimensions.size() );
    }
  this->Modified();
  m_Dimensions[i] = dim;
}

void VideoGrabberInterfaceBase::SetOrigin(unsigned int i, double origin)
{
  if ( i >= m_Origin.size() )
    {
    itkWarningMacro( "Index: " << i
                               << " is out of bounds, expected maximum is "
                               << m_Origin.size() );
    itkExceptionMacro( "Index: " << i
                                 << " is out of bounds, expected maximum is "
                                 << m_Origin.size() );
    }
  this->Modified();
  m_Origin[i] = origin;
}

void VideoGrabberInterfaceBase::SetSpacing(unsigned int i, double spacing)
{
  if ( i >= m_Spacing.size() )
    {
    itkWarningMacro( "Index: " << i
                               << " is out of bounds, expected maximum is "
                               << m_Spacing.size() );
    itkExceptionMacro( "Index: " << i
                                 << " is out of bounds, expected maximum is "
                                 << m_Spacing.size() );
    }
  this->Modified();
  m_Spacing[i] = spacing;
}

void VideoGrabberInterfaceBase::SetDirection(unsigned int i, std::vector< double > & direction)
{
  if ( i >= m_Direction.size() )
    {
    itkWarningMacro( "Index: " << i
                               << " is out of bounds, expected maximum is "
                               << m_Direction.size() );
    itkExceptionMacro( "Index: " << i
                                 << " is out of bounds, expected maximum is "
                                 << m_Direction.size() );
    }
  this->Modified();
  m_Direction[i] = direction;
}

void VideoGrabberInterfaceBase::SetDirection(unsigned int i, vnl_vector< double > & direction)
{
  if ( i >= m_Direction.size() )
    {
    itkWarningMacro( "Index: " << i
                               << " is out of bounds, expected maximum is "
                               << m_Direction.size() );
    itkExceptionMacro( "Index: " << i
                                 << " is out of bounds, expected maximum is "
                                 << m_Direction.size() );
    }
  this->Modified();
  std::vector< double > v;
  v.resize( m_Direction.size() );
  for ( unsigned int j = 0; j < v.size(); j++ )
    {
    v[j] = direction[j];
    }
  m_Direction[i] = v;
}

/** Return the default directions. */
std::vector< double >
VideoGrabberInterfaceBase::GetDefaultDirection(unsigned int k) const
{
  std::vector< double > axis;
  axis.resize( this->GetNumberOfDimensions() );

  // Fill up with the equivalent of a line from an Identity matrix
  for ( unsigned int r = 0; r < axis.size(); r++ )
    {
    axis[r] = 0.0;
    }

  axis[k] = 1.0;

  return axis;
}

// Calculates the image size in bytes
VideoGrabberInterfaceBase::SizeType
VideoGrabberInterfaceBase
::GetImageSizeInBytes() const
{
  return ( this->GetImageSizeInComponents() * this->GetComponentSize() );
}

// Calculates the image size in pixels
VideoGrabberInterfaceBase::SizeType
VideoGrabberInterfaceBase
::GetImageSizeInPixels() const
{
  unsigned int i;
  SizeType numPixels = 1;

  for ( i = 0; i < m_NumberOfDimensions; i++ )
    {
    numPixels *= m_Dimensions[i];
    }

  return numPixels;
}

unsigned int VideoGrabberInterfaceBase::GetComponentSize() const
{
  switch ( m_ComponentType )
    {
    case UCHAR:
      return sizeof( unsigned char );
    case CHAR:
      return sizeof( char );
    case USHORT:
      return sizeof( unsigned short );
    case SHORT:
      return sizeof( short );
    case UINT:
      return sizeof( unsigned int );
    case INT:
      return sizeof( int );
    case ULONG:
      return sizeof( unsigned long );
    case LONG:
      return sizeof( long );
    case FLOAT:
      return sizeof( float );
    case DOUBLE:
      return sizeof( double );
    case UNKNOWNCOMPONENTTYPE:
    default:
      itkExceptionMacro ("Unknown component type: " << m_ComponentType);
    }

  return 0;
}


}; //namespace itk end
