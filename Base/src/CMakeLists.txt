set(Video-Grabber-Base_SRC
itkVideoGrabberInterfaceBase.cxx
itkVideoGrabberInterfaceFactory.cxx
)

add_library(Video-Grabber-Base ${Video-Grabber-Base_SRC})

target_link_libraries(Video-Grabber-Base ${ITK-Common_LIBRARIES} ${ITK-IO-Base} ${TEST_DEPENDS_LIBRARIES} ${ITK-TestKernel_LIBRARIES})
   
#itk_module_target(Video-Grabber-Base)

