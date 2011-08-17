set(Video-Grabber-Epiphan_SRC
itkEpiphanVideoGrabber.cxx
itkEpiphanVideoGrabberFactory.cxx
)

add_library(Video-Grabber-Epiphan ${Video-Grabber-Epiphan_SRC})
target_link_libraries(Video-Grabber-Epiphan ${ITK-Common_LIBRARIES} ${ITK-IO-Base} Video-IO-Base ${TEST_DEPENDS_LIBRARIES} ${ITK-TestKernel_LIBRARIES})
itk_module_target(Video-Grabber-Epiphan)
