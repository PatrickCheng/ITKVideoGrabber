# OpenCVVideoGrabberExample1
add_executable(OpenCVVideoGrabberExample1 
  OpenCVVideoGrabberExample1.cxx )
target_link_libraries(OpenCVVideoGrabberExample1
  ${ITK_LIBRARIES} ${Video-Grabber-OpenCV_LIBRARIES})

