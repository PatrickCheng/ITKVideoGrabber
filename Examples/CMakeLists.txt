
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

# VideoGrabberOpenCVExample4

add_executable(VideoGrabberOpenCVExample4
  VideoGrabberOpenCVExample4.cxx)
target_link_libraries(VideoGrabberOpenCVExample4
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# VideoGrabberOpenCVExample5

add_executable(VideoGrabberOpenCVExample5
  VideoGrabberOpenCVExample5.cxx)
target_link_libraries(VideoGrabberOpenCVExample5
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# VideoGrabberOpenCVExample6

add_executable(VideoGrabberOpenCVExample6
  VideoGrabberOpenCVExample6.cxx)
target_link_libraries(VideoGrabberOpenCVExample6
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# VideoGrabberOpenCVExample7

add_executable(VideoGrabberOpenCVExample7
  VideoGrabberOpenCVExample7.cxx)
target_link_libraries(VideoGrabberOpenCVExample7
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})
