set(Video-Grabber_SRC
itkVideoGrabberBase.cxx
itkOpenCVVideoGrabber.cxx
)

add_library(Video-Grabber ${Video-Grabber_SRC})
target_link_libraries(Video-Grabber ${Video-IO-OpenCV_LIBRARIES} ${TEST_DEPENDS_LIBRARIES} ${ITK-TestKernel_LIBRARIES})
itk_module_target(Video-Grabber)
