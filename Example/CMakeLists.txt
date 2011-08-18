# OpenCVVideoGrabberExample1
add_executable(OpenCVVideoGrabberExample1 
  OpenCVVideoGrabberExample1.cxx )
target_link_libraries(OpenCVVideoGrabberExample1
  ${ITK_LIBRARIES} ${OpenCV_LIBS})

