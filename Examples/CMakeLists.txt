
find_package ( OpenCV REQUIRED )

# OpenCVVideoGrabberExample1

add_executable(OpenCVVideoGrabberExample1 
  OpenCVVideoGrabberExample1.cxx)
target_link_libraries(OpenCVVideoGrabberExample1
  ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample2

add_executable(OpenCVVideoGrabberExample2 
  OpenCVVideoGrabberExample2.cxx)
target_link_libraries(OpenCVVideoGrabberExample2
  ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample3

add_executable(OpenCVVideoGrabberExample3 
  OpenCVVideoGrabberExample3.cxx)
target_link_libraries(OpenCVVideoGrabberExample3
  ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample4

add_executable(OpenCVVideoGrabberExample4
  OpenCVVideoGrabberExample4.cxx)
target_link_libraries(OpenCVVideoGrabberExample4
  ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

# OpenCVVideoGrabberExample5

add_executable(OpenCVVideoGrabberExample5
  OpenCVVideoGrabberExample5.cxx)
target_link_libraries(OpenCVVideoGrabberExample5
  ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})
