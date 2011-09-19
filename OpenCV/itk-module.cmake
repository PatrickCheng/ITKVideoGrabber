set(DOCUMENTATION "VideoGrabber OpenCV library")

itk_module(Video-Grabber-OpenCV
 DEPENDS
   Video-Grabber-Base
   Video-Core-Common
   Video-Core-OpenCV
   Video-Filters-Common
   Video-IO-Base
   Video-IO-OpenCV
   Video-Grabber-Base
   TEST_DEPENDS ITK-TestKernel
   
   DESCRIPTION
     "${DOCUMENTATION}"
)
