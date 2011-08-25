
find_package ( OpenCV REQUIRED )

# OpenCVVideoGrabberExample1

add_executable(OpenCVVideoGrabberExample1 
  OpenCVVideoGrabberExample1.cxx)
target_link_libraries(OpenCVVideoGrabberExample1
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample2

add_executable(OpenCVVideoGrabberExample2 
  OpenCVVideoGrabberExample2.cxx)
target_link_libraries(OpenCVVideoGrabberExample2
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample3

add_executable(OpenCVVideoGrabberExample3
  OpenCVVideoGrabberExample3.cxx)
target_link_libraries(OpenCVVideoGrabberExample3
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample4

add_executable(OpenCVVideoGrabberExample4
  OpenCVVideoGrabberExample4.cxx)
target_link_libraries(OpenCVVideoGrabberExample4
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample5

add_executable(OpenCVVideoGrabberExample5
  OpenCVVideoGrabberExample5.cxx)
target_link_libraries(OpenCVVideoGrabberExample5
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample6

add_executable(OpenCVVideoGrabberExample6
  OpenCVVideoGrabberExample6.cxx)
target_link_libraries(OpenCVVideoGrabberExample6
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample7

add_executable(OpenCVVideoGrabberExample7
  OpenCVVideoGrabberExample7.cxx)
target_link_libraries(OpenCVVideoGrabberExample7
  ${Video-Grabber_LIBRARIES} ${OpenCV_LIBS})
