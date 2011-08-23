project(VideoGrabber)
itk_module_impl()

find_package ( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(ITKVideoGrabber_LIBRARIES 
   ${OpenCV_LIBS}    
   ITK-Common
   ITK-Thresholding
   ITK-ImageFeature
   ITK-CurvatureFlow )

add_subdirectory(Base)
#add_subdirectory(Epiphan)
add_subdirectory(Examples)
add_subdirectory(OpenCV)

