project(Video-Grabber)

find_package ( OpenCV REQUIRED )

set(Video-Grabber_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS} )
set(Video-Grabber_LIBRARIES ${OpenCV_LIBS} Video-Core-Common Video-IO-OpenCV Video-Grabber)

itk_module_impl()
