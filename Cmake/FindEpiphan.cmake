# - Try to find Epiphan
# This module tries to find an Epiphan implementation on your system.
#
# Once done this will define
#  Epiphan_FOUND        - True if Epiphan found.
#  Epiphan_INCLUDE_DIR  - where to find Epiphan include sub-directory.
#  Epiphan_LIBRARIES    - List of libraries when using Epiphan
#


FIND_PATH(Epiphan_INCLUDE_DIR frmgrab.h)

SET(Epiphan_NAMES frmgrab)
FIND_LIBRARY(Epiphan_LIBRARY NAMES ${Epiphan_NAMES})

IF(Epiphan_FOUND)
  SET( Epiphan_LIBRARIES ${Epiphan_LIBRARY} )
ELSE(Epiphan_FOUND)
  SET( Epiphan_LIBRARIES )
ENDIF(Epiphan_FOUND)

#MARK_AS_ADVANCED( Epiphan_LIBRARY Epiphan_INCLUDE_DIR )

