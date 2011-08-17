#include <iostream>
#include <sstream>

#include "itkVideoGrabber.h"
#include "itkVideoFileWriter.h"
#include "itkRGBPixel.h"
#include "itkRecursiveGaussianImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkOpenCVVideoGrabberFactory.h"

//DEBUG
#include "itkImageFileWriter.h"

int itkVideoGrabberTest ( int argc, char *argv[] )
{
  // Check parameters
  if (argc != 3)
    {
    std::cerr << "Usage: [Video Input] [Image Output]" << std::endl;
    return EXIT_FAILURE;
    }

  // Instantiate a new grabber
  typedef itk::RGBPixel<unsigned char>                PixelType;
  const unsigned int NumberOfDimensions =             2;
  typedef itk::Image< PixelType, NumberOfDimensions > FrameType;
  typedef itk::VideoStream< FrameType >               VideoType;
  typedef itk::VideoGrabber< VideoType >              GrabberType;
  typedef itk::VideoFileWriter< VideoType >           VideoWriterType;

  GrabberType::Pointer grabber = GrabberType::New();
  grabber->SetDeviceNumber( 0 );

  // I'm still not sure how to handle this right, but for now, just manually
  // register an OpenCVVideoGrabberFactory
  itk::ObjectFactoryBase::RegisterFactory( itk::OpenCVVideoGrabberFactory::New() );

  // Set up the writer
  VideoWriterType::Pointer writer = VideoWriterType::New();
  writer->SetInput(grabber->GetOutput());
  writer->SetFileName(argv[2]);

  // Call Update on the writer to process the entire video
  writer->Update();

  return EXIT_SUCCESS;
}
