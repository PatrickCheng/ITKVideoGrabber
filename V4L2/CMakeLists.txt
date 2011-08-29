project(Video-Grabber-V4L2)

find_package ( V4L2 REQUIRED )

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

set(Video-Grabber-V4L2_LIBRARIES Video-Grabber-V4L2)
itk_module_impl()
