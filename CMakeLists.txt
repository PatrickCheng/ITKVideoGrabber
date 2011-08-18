project(ITKVideoGrabber)

set(Video-Grabber_LIBRARIES 
     Video-Core-Common
     Video-Core-OpenCV
     Video-Filters-Common
     Video-IO-Base
     Video-IO-OpenCV
     ITK-TestKernel
   )
   
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${OpenCV_LIB_DIR})
# Link to all possible lib dirs, OpenCV 2.3 cmake build has issue on windows
link_directories(${OpenCV_DIR}/3rdparty/lib/Debug)
link_directories(${OpenCV_DIR}/3rdparty/lib/Release)
link_directories(${OpenCV_LIB_DIR}/Debug)
link_directories(${OpenCV_LIB_DIR}/Release)


itk_module_impl()

add_subdirectory(Base)
add_subdirectory(OpenCV)
add_subdirectory(Example)



