set(Video-Grabber-Epiphan_SRC
itkEpiphanVideoGrabberInterface.cxx
itkEpiphanVideoGrabberInterfaceFactory.cxx
)

add_library(Video-Grabber-Epiphan ${Video-Grabber-Epiphan_SRC})
target_link_libraries(Video-Grabber-Epiphan ${Video-Grabber-Epiphan_LIBRARIES})
#itk_module_target(Video-Grabber-Epiphan)

