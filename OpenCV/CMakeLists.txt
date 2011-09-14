project(Video-Grabber-OpenCV)

find_package ( OpenCV REQUIRED )

set(Video-Grabber-OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS} )
set(Video-Grabber-OpenCV_LIBRARIES ${OpenCV_LIBS} Video-Core-Common Video-Grabber-Base Video-Grabber-OpenCV)
itk_module_impl()

add_subdirectory(Examples)
