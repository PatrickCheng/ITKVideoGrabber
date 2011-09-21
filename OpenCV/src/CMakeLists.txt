set(Video-Grabber-OpenCV_SRC
itkOpenCVVideoGrabberInterface.cxx
itkOpenCVVideoGrabberInterfaceFactory.cxx
)

add_library(Video-Grabber-OpenCV ${Video-Grabber-OpenCV_SRC})
target_link_libraries(Video-Grabber-OpenCV ${Video-Grabber-OpenCV_LIBRARIES})
target_link_libraries(Video-Grabber-OpenCV ${ITK-Common_LIBRARIES} ${ITK-IO-Base} Video-Grabber-Base ${TEST_DEPENDS_LIBRARIES} ${ITK-TestKernel_LIBRARIES})
#itk_module_target(Video-Grabber-OpenCV)


