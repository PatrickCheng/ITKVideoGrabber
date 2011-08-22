# OpenCVVideoGrabberExample1
find_package ( OpenCV REQUIRED )

add_executable(OpenCVVideoGrabberExample1 
  OpenCVVideoGrabberExample1.cxx
  itkVideoGrabberCommandLineProgressReporter.cxx)
target_link_libraries(OpenCVVideoGrabberExample1
  ${ITK_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample2

add_executable(OpenCVVideoGrabberExample2 
  OpenCVVideoGrabberExample2.cxx 
  itkVideoGrabberCommandLineProgressReporter.cxx)
target_link_libraries(OpenCVVideoGrabberExample2
  ${ITK_LIBRARIES} ${OpenCV_LIBS})
