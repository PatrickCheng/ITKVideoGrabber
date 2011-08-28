set(Video-Grabber-OpenCV_SRC
itkOpenCVVideoGrabberInterface.cxx
itkOpenCVVideoGrabberInterfaceFactory.cxx
)

add_library(Video-Grabber-OpenCV ${Video-Grabber-OpenCV_SRC})
target_link_libraries(Video-Grabber-OpenCV ${Video-Grabber-OpenCV_LIBRARIES})

#itk_module_target(Video-Grabber-OpenCV)
