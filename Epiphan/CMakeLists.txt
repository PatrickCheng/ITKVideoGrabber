project(Video-Grabber-Epiphan)

find_package ( Epiphan REQUIRED )

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

set(Video-Grabber-Epiphan_LIBRARIES Video-Grabber-Epiphan)
itk_module_impl()
