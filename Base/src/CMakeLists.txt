set(Video-Grabber-Base_SRC
itkVideoGrabberBase.cxx
itkVideoGrabberFactory.cxx
)

add_library(Video-Grabber-Base ${Video-Grabber-Base_SRC})

target_link_libraries(Video-Grabber-Base ${Video-Grabber_LIBRARIES} )
   
#itk_module_target(Video-Grabber-Base)
