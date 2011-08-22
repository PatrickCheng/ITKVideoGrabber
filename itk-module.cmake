set(DOCUMENTATION "Video capturing using frame grabber.")

itk_module(Video-Grabber
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

