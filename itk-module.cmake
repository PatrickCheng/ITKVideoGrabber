set(DOCUMENTATION "Video capturing using frame grabber.")

itk_module(Video-Grabber
 DEPENDS
   ITK-Common
   ITK-ImageFilterBase
   ITK-Thresholding
   ITK-ImageFeature
   ITK-CurvatureFlow
   Video-Core-Common
   Video-Core-OpenCV
   Video-Filters-Common
   Video-IO-Base
   Video-IO-OpenCV
   ITK-TestKernel
   
   DESCRIPTION
     "${DOCUMENTATION}"
)

