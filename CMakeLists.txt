project(VideoGrabber)
itk_module_impl()

OPTION(USE_OpenCV "Build OpenCV interface to frame grabbers." ON)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Cmake")


#-----------------------------------------------------------------------------
# Platform checks
IF(MSVC)
    OPTION(USE_Epiphan "Build Epiphan interface to frame grabbers." OFF)
ENDIF(MSVC)
IF(UNIX)
  IF(APPLE)
    OPTION(USE_QuickTime "Build QuickTime interface to frame grabbers." ON)
  ELSE(APPLE)
    OPTION(USE_Epiphan "Build Epiphan interface to frame grabbers." OFF)
  ENDIF(APPLE)
ENDIF(UNIX)

set(ITKVideoGrabber_LIBRARIES 
   ITK-Common
   Video-Grabber-Base
   )

add_subdirectory(Base)

IF (USE_OpenCV)
    find_package ( OpenCV REQUIRED )
    include_directories( ${OpenCV_INCLUDE_DIRS} )

    set(ITKVideoGrabber_LIBRARIES 
        ${ITKVideoGrabber_LIBRARIES}        
        Video-Grabber-OpenCV
        ${OpenCV_LIBS}    
    )

    add_subdirectory(OpenCV)
ENDIF (USE_OpenCV)

IF (USE_Epiphan)
    find_package ( Epiphan REQUIRED )
    include_directories( ${Epiphan_INCLUDE_DIRS} )

    set(ITKVideoGrabber_LIBRARIES 
        ${ITKVideoGrabber_LIBRARIES}
        ${Epiphan_LIBS}    
    )

    add_subdirectory(Epiphan)
ENDIF (USE_Epiphan)

IF (USE_QuickTime)

    FIND_PACKAGE ( QuickTime REQUIRED )
     # This module defines
      # QUICKTIME_LIBRARY
      # QUICKTIME_FOUND, if false, do not try to link to gdal
      # QUICKTIME_INCLUDE_DIR, where to find the headers
      #
      # $QUICKTIME_DIR is an environment variable that would
      # correspond to the ./configure --prefix=$QUICKTIME_DIR

      IF (QUICKTIME_FOUND)
        include_directories( ${QUICKTIME_INCLUDE_DIR} )
        SET(ITKVideoGrabber_LIBRARIES 
            ${ITKVideoGrabber_LIBRARIES}
            ${QUICKTIME_LIBRARY}    
        )
        add_subdirectory(QuickTime)
      ELSE (QUICKTIME_FOUND)
        MESSAGE( FATAL_ERROR "This package requires QuickTime installed. One of these components is missing. Please verify configuration")
      ENDIF (QUICKTIME_FOUND)

ENDIF(USE_QuickTime)

#add_subdirectory(Examples)


