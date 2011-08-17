#include <iostream>
#include <fstream>

#include "itkOpenCVVideoGrabber.h"
#include "itkImportImageFilter.h"
#include "itkRGBPixel.h"
#include "itkImageFileWriter.h"


// ITK typedefs
typedef itk::RGBPixel<char> PixelType;
typedef itk::ImportImageFilter<PixelType, 2> ImportFilterType;
typedef itk::Image<PixelType, 2> ImageType;
typedef itk::ImageFileWriter<ImageType> WriterType;


//
// Utility function to get an ITK image from an void* buffer
//
ImageType::Pointer itkImageFromBuffer( itk::OpenCVVideoGrabber::Pointer opencvGrabber, void* buffer, size_t bufferSize )
{
  // Set up for incoming image
  ImageType::RegionType region;
  ImageType::SizeType size;
  ImageType::IndexType start;
  size[0] = opencvGrabber->GetDimensions(0);
  size[1] = opencvGrabber->GetDimensions(1);
  start.Fill(0);
  region.SetIndex(start);
  region.SetSize(size);
  ImageType::PointType origin;
  ImageType::SpacingType space;
  origin.Fill(0.0);
  space.Fill(1.0);  // May need fixing

  // Use itkImportImageFilter to create an ITK image
  ImportFilterType::Pointer importFilter = ImportFilterType::New();
  importFilter->SetRegion(region);
  importFilter->SetOrigin(origin);
  importFilter->SetSpacing(space);
  importFilter->SetImportPointer(reinterpret_cast<PixelType*>(buffer), bufferSize, false);
  importFilter->Update();
  ImageType::Pointer frame = importFilter->GetOutput();

  return frame;
}



//
// Utility function for comparing output of Read buffer to OpenCV image
//
// Note: opencvGrabber should already have called ReadImageInformation
//
bool readCorrectly( itk::OpenCVVideoGrabber::Pointer opencvGrabber, CvCapture* capture, unsigned long frameNumber )
{
  bool ret = true;

  // Check meta data
  for (unsigned int i = 0; i < ImageType::ImageDimension; ++i)
    {
    if (opencvGrabber->GetSpacing(i) != 1.0)
      {
      std::cerr << "Frame Spacing not set correctly" << std::endl;
      ret = false;
      }
    if (opencvGrabber->GetOrigin(i) != 0.0)
      {
      std::cerr << "Frame Origin not set correctly" << std::endl;
      ret = false;
      }
    if (opencvGrabber->GetDirection(i) != opencvGrabber->GetDefaultDirection(i))
      {
      std::cerr << "Frame Direction not set correctly" << std::endl;
      ret = false;
      }
    }

  // Set up the buffer for the frame data
  size_t bufferSize = opencvGrabber->GetImageSizeInBytes();
  PixelType buffer[bufferSize];

  // Read the frame data
  opencvGrabber->Read(static_cast<void*>(buffer));

  // Open the frame directly with OpenCV
  IplImage* cvFrameBGR = cvQueryFrame(capture);
  IplImage* cvFrameRGB = cvCreateImage(
    cvSize(opencvGrabber->GetDimensions(0), opencvGrabber->GetDimensions(1)),
    IPL_DEPTH_8U, opencvGrabber->GetNumberOfComponents() );
  cvCvtColor(cvFrameBGR, cvFrameRGB, CV_BGR2RGB);

  // Make sure buffers are same sized
  if (cvFrameRGB->imageSize != (int)bufferSize)
    {
    std::cerr << "Frame buffer sizes don't match. Got: " << bufferSize << ", Expected: "
              << cvFrameRGB->imageSize << std::endl;
    ret = false;
    }

  // Compare buffer contents
  if (memcmp(reinterpret_cast<void*>(buffer), reinterpret_cast<void*>(cvFrameRGB->imageData), bufferSize))
    {
    std::cerr << "Frame buffers don't match for frame " << frameNumber << std::endl;
    ret = false;
    }

  // Return
  cvReleaseImage(&cvFrameRGB);
  return ret;
}


//
// Utility function to compare two videos frame by frame
//
bool videosMatch(char* file1, char* file2)
{
  itk::OpenCVVideoGrabber::Pointer io1 = itk::OpenCVVideoGrabber::New();
  itk::OpenCVVideoGrabber::Pointer io2 = itk::OpenCVVideoGrabber::New();

  io1->SetFileName(file1);
  io2->SetFileName(file2);

  // Make sure files can be read
  if (!io1->CanReadFile(file1) || !io2->CanReadFile(file2))
    {
    std::cerr << "Cannot read specified files" << std::endl;
    return false;
    }

  // Read in the file information for both
  io1->ReadImageInformation();
  io2->ReadImageInformation();

  // Make sure image info matches
  double e = 0.0001;
  if (io1->GetFrameTotal() != io2->GetFrameTotal() ||
      io1->GetDimensions(0) != io2->GetDimensions(0) ||
      io1->GetDimensions(1) != io2->GetDimensions(1) ||
      io1->GetFpS() + e < io2->GetFpS() ||
      io1->GetFpS() - e > io2->GetFpS() ||
      io1->GetNumberOfComponents() != io2->GetNumberOfComponents())
    {

    std::cerr << "Frame information doesn't match" << std::endl;
    std::cerr << "  FrameTotal: " << io1->GetFrameTotal() << ", " << io2->GetFrameTotal() << std::endl;
    std::cerr << "  Width: " << io1->GetDimensions(0) << ", " << io2->GetDimensions(0)
      << std::endl;
    std::cerr << "  Height: " << io1->GetDimensions(1) << ", " << io2->GetDimensions(1)
      << std::endl;
    std::cerr << "  FpS: " << io1->GetFpS() << ", " << io2->GetFpS() << std::endl;
    std::cerr << "  NChannels: " << io1->GetNumberOfComponents() << ", " << io2->GetNumberOfComponents() << std::endl;
    
    return false;
    }

  // Loop through each frame and compare the buffer for exact match
  size_t bufferSize = io1->GetImageSizeInBytes();
  PixelType buffer1[bufferSize];
  PixelType buffer2[bufferSize];
  for (unsigned int i = 0; i < io1->GetFrameTotal(); ++i)
    {
    io1->Read(reinterpret_cast<void*>(buffer1));
    io2->Read(reinterpret_cast<void*>(buffer2));
    if (memcmp(reinterpret_cast<void*>(buffer1), reinterpret_cast<void*>(buffer2), bufferSize))
      {
      std::cerr << "Frame buffers don't match for frame " << i << std::endl;
      return false;
      }
    }

  // Close the readers
  io1->FinishReadingOrWriting();
  io2->FinishReadingOrWriting();

  // return result
  return true;
}




///////////////////////////////////////////////////////////////////////////////
// This tests all of the functionality of the OpenCVVideoGrabber
//
// Usage: [Video Input] [Non-Video Input] [Video Output] [Width] [Height]
//            [Num Frames] [FpS]

int test_OpenCVVideoGrabber ( char* input, char* nonVideoInput, char* output, char* cameraOutput,
                         unsigned int inWidth, unsigned int inHeight, unsigned long inNumFrames,
                         double inFpS )
{

  int ret = EXIT_SUCCESS;

  // Create the VideoGrabber
  itk::OpenCVVideoGrabber::Pointer opencvGrabber = itk::OpenCVVideoGrabber::New();


  //////
  // CanReadFile
  //////
  std::cout << "OpenCVVideoGrabber::CanReadFile..." << std::endl;

  // Test CanReadFile on good file
  if (!opencvGrabber->CanReadFile(input))
    {
    std::cerr << "Could not read " << input << std::endl;
    ret = EXIT_FAILURE;
    }

  // Test CanReadFile on non-existant file
  std::string nonExistantFile = "Bad/Path/To/Nothing";
  if (opencvGrabber->CanReadFile(nonExistantFile.c_str()))
    {
    std::cerr << "Should have failed to open \"" << nonExistantFile << "\"" << std::endl;
    ret = EXIT_FAILURE; 
    }

  // Test CanReadFile on non-video file
  if (opencvGrabber->CanReadFile(nonVideoInput))
    {
    std::cerr << "Should have failed to open \"" << nonVideoInput << "\"" << std::endl;
    ret = EXIT_FAILURE; 
    }



  //////
  // ReadImageInformation
  //////
  std::cout << "OpenCVVideoGrabber::ReadImageInformation..." << std::endl;

  opencvGrabber->SetFileName(input);
  opencvGrabber->ReadImageInformation();
  bool infoSet = true;
  std::stringstream paramMessage;
  if (opencvGrabber->GetDimensions(0) != inWidth)
    {
    infoSet = false;
    paramMessage << "Width mismatch: (expected) " << inWidth << " != (got) "
      << opencvGrabber->GetDimensions(0) << std::endl;
    }
  if (opencvGrabber->GetDimensions(1) != inHeight)
    {
    infoSet = false;
    paramMessage << "Height mismatch: (expected) " << inHeight << " != (got) "
      << opencvGrabber->GetDimensions(1) << std::endl;
    }
  double epsilon = 0.0001;
  if (opencvGrabber->GetFpS() < inFpS - epsilon || opencvGrabber->GetFpS() > inFpS + epsilon)
    {
    infoSet = false;
    paramMessage << "FpS mismatch: (expected) " << inFpS << " != (got) " << opencvGrabber->GetFpS()
      << std::endl;
    }
  if (opencvGrabber->GetFrameTotal() != inNumFrames)
    {
    infoSet = false;
    paramMessage << "FrameTotal mismatch: (expected) " << inNumFrames << " != (got) "
      << opencvGrabber->GetFrameTotal() << std::endl;
    }

  if (!infoSet)
    {
    std::cerr << paramMessage.str();
    ret = EXIT_FAILURE;
    }


  //////
  // Read
  //////
  std::cout << "OpenCVVideoGrabber::Read..." << std::endl;
  std::cout << "Comparing all " << opencvGrabber->GetFrameTotal() << " frames" << std::endl;

  // Set up OpenCV capture
  CvCapture* capture = cvCaptureFromFile( opencvGrabber->GetFileName() );

  // Loop through all frames
  for (unsigned long i = 0; i < opencvGrabber->GetFrameTotal(); ++i)
    {
    if (!readCorrectly(opencvGrabber, capture, i))
      {
      std::cerr << "Failed to read frame " << i << " correctly" << std::endl;
      ret = EXIT_FAILURE;
      break;
      }
    }

  // Release capture
  cvReleaseCapture(&capture);


  //////
  // SetNextFrameToRead
  //////
  std::cout << "OpenCVVideoGrabber::SetNextFrameToRead" << std::endl;

  // Set up the buffer for the frame data so Read can be called
  size_t bufferSize = opencvGrabber->GetImageSizeInBytes();
  PixelType buffer[bufferSize];


  // try seeking to an I-Frame
  unsigned long seekFrame = opencvGrabber->GetIFrameInterval();
  if (!opencvGrabber->SetNextFrameToRead(seekFrame))
    {
    std::cerr << "Failed to seek to second I-Frame..." << std::endl;
    ret = EXIT_FAILURE;
    }

  // Read the frame data which updates the current frame correctly
  opencvGrabber->Read(static_cast<void*>(buffer));

  if (opencvGrabber->GetCurrentFrame() != seekFrame)
    {
    std::cerr << "Seek to I-Frame didn't end up in the right place" << std::endl;
    ret = EXIT_FAILURE;
    }


  // If there are I-Frame intervals, check behavior
  if (opencvGrabber->GetIFrameInterval() > 1)
    {

    // try seeking in-between I-Frames
    seekFrame = opencvGrabber->GetIFrameInterval()/2;
    if (!opencvGrabber->SetNextFrameToRead(seekFrame))
      {
      std::cerr << "Failed to seek between I-Frames" << std::endl;
      ret = EXIT_FAILURE;
      }
    opencvGrabber->Read(static_cast<void*>(buffer));
    if (opencvGrabber->GetCurrentFrame() != opencvGrabber->GetIFrameInterval())
      {
      std::cerr << "Seek between I-Frames didn't end up in the right place" << std::endl;
      ret = EXIT_FAILURE;
      }

    // try seeking past last I-Frame
    seekFrame = opencvGrabber->GetLastIFrame() + 1;
    if (opencvGrabber->SetNextFrameToRead(seekFrame))
      {
      std::cerr << "Did no fail when seeking past the last I-Frame" << std::endl;
      ret = EXIT_FAILURE;
      }

    }

  // Save the current parameters
  double fps = opencvGrabber->GetFpS();
  unsigned int width = opencvGrabber->GetDimensions(0);
  unsigned int height = opencvGrabber->GetDimensions(1);
  const char* fourCC = "MP42";
  unsigned int nChannels = opencvGrabber->GetNumberOfComponents();

  // Reset the VideoGrabber
  opencvGrabber->FinishReadingOrWriting();


  //////
  // Test reading from camera -- If webcam 0 can be opened, it will, otherwise this will be skipped
  //////

  // Check to see if camera is available
  if (opencvGrabber->CanReadCamera( 0 ))
    {

    std::cout << "OpenCVVideoGrabber::Read (from camera)..." << std::endl;

    // Set the reader to use the camera
    opencvGrabber->SetReadFromCamera();

    // Get information from the camera
    try
      {
      opencvGrabber->ReadImageInformation();
      }
    catch (itk::ExceptionObject e)
      {
      std::cerr << "Could not read information from the camera" << std::endl;
      ret = EXIT_FAILURE;
      }

    // set up buffer for camera
    size_t camBufferSize = opencvGrabber->GetImageSizeInBytes();
    PixelType camBuffer[camBufferSize];

    // Read from the camera
    try
      {
      opencvGrabber->Read(reinterpret_cast<void*>(camBuffer));
      }
    catch (itk::ExceptionObject e)
      {
      std::cerr << "Could not read from the camera" << std::endl;
      ret = EXIT_FAILURE;
      }

    // Get an ITK image from the camera's frame
    ImageType::Pointer cameraFrame = itkImageFromBuffer(opencvGrabber, camBuffer, camBufferSize);

    // Write out the ITK image -- DEBUG
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(cameraOutput);
    writer->SetInput(cameraFrame);
    writer->Update();

    // Overwirte the file right away so we're not saving pictures of the tester!
    std::ofstream fs;
    fs.open(cameraOutput);
    fs << "EMPTY... deleted picture from webcam\n";
    fs.close();

    // Finish reading
    opencvGrabber->FinishReadingOrWriting();

    }


  /////////////////////////////////////////////////////////////////////////////
  // Test Writing
  //


  //////
  // SetWriterParameters
  //////
  std::cout << "OpenCVVIdeoIO::SetWriterParameters..." << std::endl;

  // Reset the saved parameters
  std::vector<unsigned int> size;
  size.push_back(width);
  size.push_back(height);
  opencvGrabber->SetWriterParameters(fps, size, fourCC, nChannels, itk::ImageIOBase::UCHAR);

  // Make sure they set correctly
  if (opencvGrabber->GetFpS() != fps || opencvGrabber->GetDimensions(0) != width ||
      opencvGrabber->GetDimensions(1) != height || opencvGrabber->GetNumberOfComponents() != nChannels)
    {
    std::cerr << "Didn't set writer parmeters correctly" << std::endl;
    ret = EXIT_FAILURE;
    }

  //////
  // CanWriteFile
  //////
  std::cout << "OpenCVVideoGrabber::CanWriteFile..." << std::endl;

  // Test CanWriteFile on good filename
  if (!opencvGrabber->CanWriteFile(output))
    {
    std::cerr << "CanWriteFile didn't return true correctly" << std::endl;
    ret = EXIT_FAILURE;
    }

  // Test CanWriteFile on bad filename
  if (opencvGrabber->CanWriteFile("asdfasdfasdf"))
    {
    std::cerr << "CanWriteFile should have failed for bad filename" << std::endl;
    ret = EXIT_FAILURE;
    }


  //////
  // Write
  //////
  std::cout << "OpenCVVIdeoIO::Write..." << std::endl;

  // Set output filename
  opencvGrabber->SetFileName( output );

  // Set up a second VideoGrabber to read while we're writing
  itk::OpenCVVideoGrabber::Pointer opencvGrabber2 = itk::OpenCVVideoGrabber::New();
  opencvGrabber2->SetFileName( input );
  opencvGrabber2->ReadImageInformation();

  // Loop through all frames to read with opencvGrabber2 and write with opencvGrabber
  for (unsigned int i = 0; i < inNumFrames; ++i)
    {

    // Set up a buffer to read to
    size_t bufferSize = opencvGrabber2->GetImageSizeInBytes();
    PixelType buffer[bufferSize];

    // Read into the buffer
    opencvGrabber2->Read(static_cast<void*>(buffer));

    // Write out the frame from the buffer
    opencvGrabber->Write(static_cast<void*>(buffer));

    }

  // Finish writing
  opencvGrabber2->FinishReadingOrWriting();
  opencvGrabber->FinishReadingOrWriting();


  //DEBUG -- Don't do this for now, need a better comparison method
  // Compare input and output videos to make sure they are identical
  //if (!videosMatch(input, output))
  //  {
  //  std::cerr << "Written video does not match input video" << std::endl;
  //  ret = EXIT_FAILURE;
  //  }


  //DEBUG
  //std::cout << "PIM1 = " << CV_FOURCC('P','I','M','1') << std::endl;
  //std::cout << "MJPG = " << CV_FOURCC('M','J','P','G') << std::endl;
  //std::cout << "MP42 = " << CV_FOURCC('M', 'P', '4', '2') << std::endl;
  //std::cout << "DIV3 = " << CV_FOURCC('D', 'I', 'V', '3') << std::endl;
  //std::cout << "DIVX = " << CV_FOURCC('D', 'I', 'V', 'X') << std::endl;
  //std::cout << "U263 = " << CV_FOURCC('U', '2', '6', '3') << std::endl;
  //std::cout << "I263 = " << CV_FOURCC('I', '2', '6', '3') << std::endl;
  //std::cout << "FLV1 = " << CV_FOURCC('F', 'L', 'V', '1') << std::endl;



  std::cout<<"Done !"<<std::endl;
  return ret;
}

int itkOpenCVVideoGrabberTest ( int argc, char *argv[] )
{
  if (argc != 9)
    {
    std::cerr << "Usage: [Video Input] [Non-Video Input] [Video Output] [Webcam Output] "
      "[Width] [Height] [Num Frames] [FpS]" << std::endl;
    return EXIT_FAILURE;
    }

  return test_OpenCVVideoGrabber(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]),
                            atoi(argv[7]), atof(argv[8]));
}

