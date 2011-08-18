set(DOCUMENTATION "VideoGrabber base library")

itk_module(Video-Grabber-Base
 DEPENDS
   Video-Core-Common
   Video-Core-OpenCV
   Video-Filters-Common
   Video-IO-Base
   Video-IO-OpenCV
   ITK-TestKernel
   
   DESCRIPTION
     "${DOCUMENTATION}"
)


