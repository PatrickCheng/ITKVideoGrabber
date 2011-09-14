
find_package ( OpenCV REQUIRED )

# VideoGrabberOpenCVExample1

add_executable(VideoGrabberOpenCVExample1 
  VideoGrabberOpenCVExample1.cxx)
target_link_libraries(VideoGrabberOpenCVExample1
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# VideoGrabberOpenCVExample2

add_executable(VideoGrabberOpenCVExample2 
  VideoGrabberOpenCVExample2.cxx)
target_link_libraries(VideoGrabberOpenCVExample2
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# VideoGrabberOpenCVExample3

add_executable(VideoGrabberOpenCVExample3
  VideoGrabberOpenCVExample3.cxx)
target_link_libraries(VideoGrabberOpenCVExample3
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

