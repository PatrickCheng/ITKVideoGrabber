set(DOCUMENTATION "VideoGrabber Epiphan library")

itk_module(Video-Grabber-Epiphan
 DEPENDS
   Video-Grabber-Base
   Video-Core-Common
   Video-Core-OpenCV
   Video-Filters-Common
   Video-IO-Base
   Video-IO-OpenCV
   ITK-TestKernel
   Video-Grabber-Base
   
   DESCRIPTION
     "${DOCUMENTATION}"
)

