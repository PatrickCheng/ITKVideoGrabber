find_package(OpenCV REQUIRED)

# Link to all possible lib dirs
link_directories(${OpenCV_DIR}/3rdparty/lib/Debug)
link_directories(${OpenCV_DIR}/3rdparty/lib/Release)
link_directories(${OpenCV_LIB_DIR}/Debug)
link_directories(${OpenCV_LIB_DIR}/Release)

# OpenCVVideoGrabberDemo
add_executable(OpenCVVideoGrabberExample1 
  OpenCVVideoGrabberExample1.cxx )
target_link_libraries(OpenCVVideoGrabberExample1
  ${ITK_LIBRARIES} ${OpenCV_LIBS})

