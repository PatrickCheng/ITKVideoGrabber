#include <iostream>
#include <sstream>

#include "itkVideoGrabberFactory.h"
#include "itkEpiphanVideoGrabberFactory.h"

///////////////////////////////////////////////////////////////////////////////
// This tests all of the functionality of the EpiphanVideoGrabber
//
// Usage: [Video Input] [Non-Video Input] [Video Output] [Width] [Height]
//            [Num Frames] [FpS]

int test_EpiphanVideoGrabberFactory ( char* input, char* output, unsigned long cameraNumber )
{

  int ret = EXIT_SUCCESS;

  //////
  // Register the EpiphanVideoGrabberFactory.
  //
  // There's something strange going on here that makes the factories not be
  // registered by default because of the order in which the includes happen.
  // The real strangeness seems to be in ITK's system with the modularized
  // framework since none of the factories get reigstered by default.
  itk::ObjectFactoryBase::RegisterFactory( itk::EpiphanVideoGrabberFactory::New() );


  //////
  // Create the VideoGrabberBase for reading from a file
  //////
  std::cout << "Trying to create IO for reading from file..." << std::endl;
  itk::VideoGrabberBase::Pointer ioReadFile = itk::VideoGrabberFactory::CreateVideoGrabber(
                                    itk::VideoGrabberFactory::ReadFileMode, input);
  if (!ioReadFile)
    {
    std::cerr << "Did not create valid VideoGrabber for reading from file " << std::endl;
    ret = EXIT_FAILURE;
    }

  //////
  // Create the VideoGrabberBase for writing to a file
  //////
  std::cout << "Trying to create IO for writing to file..." << std::endl;
  itk::VideoGrabberBase::Pointer ioWrite = itk::VideoGrabberFactory::CreateVideoGrabber(
                                       itk::VideoGrabberFactory::WriteMode, output);
  if (!ioWrite)
    {
    std::cerr << "Did not create valid VideoGrabber for writing " << std::endl;
    ret = EXIT_FAILURE;
    }



  std::cout<<"Done !"<<std::endl;
  return ret;
}

int itkEpiphanVideoGrabberFactoryTest ( int argc, char *argv[] )
{
  if (argc != 4)
    {
    std::cerr << "Usage: [Video Input] [Video Output] [Webcam Number]" << std::endl;
    return EXIT_FAILURE;
    }

  return test_EpiphanVideoGrabberFactory(argv[1], argv[2], atoi(argv[3]));
}

