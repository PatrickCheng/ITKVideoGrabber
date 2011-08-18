project(ITKVideoGrabber)

set(Video-Grabber_LIBRARIES 
     Video-Core-Common
     Video-Core-OpenCV
     Video-Filters-Common
     Video-IO-Base
     Video-IO-OpenCV
     ITK-TestKernel
   )

itk_module_impl()


add_subdirectory(Base)
add_subdirectory(OpenCV)



