project(Video-Grabber-Linux1394)

find_package ( Linux1394 REQUIRED )

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

set(Video-Grabber-Linux1394_LIBRARIES Video-Grabber-Linux1394)
itk_module_impl()
