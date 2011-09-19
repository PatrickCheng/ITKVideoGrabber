
find_package ( OpenCV REQUIRED )

link_directories(${OpenCV_DIR}/3rdparty/lib/Debug)
link_directories(${OpenCV_DIR}/3rdparty/lib/Release)
link_directories(${OpenCV_LIB_DIR}/Debug)
link_directories(${OpenCV_LIB_DIR}/Release)

# VideoGrabberOpenCVExample1

add_executable(VideoGrabberOpenCVExample1 
  VideoGrabberOpenCVExample1.cxx)
target_link_libraries(VideoGrabberOpenCVExample1
  ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

# VideoGrabberOpenCVExample2

add_executable(VideoGrabberOpenCVExample2 
  VideoGrabberOpenCVExample2.cxx)
target_link_libraries(VideoGrabberOpenCVExample2
  ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

# VideoGrabberOpenCVExample3

add_executable(VideoGrabberOpenCVExample3
  VideoGrabberOpenCVExample3.cxx)
target_link_libraries(VideoGrabberOpenCVExample3
  ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

