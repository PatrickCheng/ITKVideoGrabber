itk_module_test()

set(ITKVideoGrabberTests
    VideoGrabberOpenCVTest1.cxx
    VideoGrabberOpenCVTest2.cxx
    VideoGrabberOpenCVTest3.cxx
    VideoGrabberOpenCVTest4.cxx
    VideoGrabberOpenCVTest5.cxx
    VideoGrabberOpenCVTest6.cxx
)

find_package ( OpenCV REQUIRED )

link_directories(${OpenCV_DIR}/3rdparty/lib/Debug)
link_directories(${OpenCV_DIR}/3rdparty/lib/Release)
link_directories(${OpenCV_LIB_DIR}/Debug)
link_directories(${OpenCV_LIB_DIR}/Release)

set(ITKVideoGrabber-Test_LIBRARIES ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

CreateTestDriver(ITKVideoGrabber "${ITKVideoGrabber-Test_LIBRARIES}" "${ITKVideoGrabberTests}")

set(TEST_DATA_ROOT "${ITKVideoGrabber_SOURCE_DIR}/Data")
set(TEMP ${ITK_TEST_OUTPUT_DIR})

itk_add_test( NAME VideoGrabberOpenCVTest1
  COMMAND ITKVideoGrabberTestDriver VideoGrabberOpenCVTest1 )
itk_add_test( NAME VideoGrabberOpenCVTest2
  COMMAND ITKVideoGrabberTestDriver VideoGrabberOpenCVTest2 )
itk_add_test( NAME VideoGrabberOpenCVTest3
  COMMAND ITKVideoGrabberTestDriver VideoGrabberOpenCVTest3 )
itk_add_test( NAME VideoGrabberOpenCVTest4
  COMMAND ITKVideoGrabberTestDriver VideoGrabberOpenCVTest4 )
itk_add_test( NAME VideoGrabberOpenCVTest5
  COMMAND ITKVideoGrabberTestDriver VideoGrabberOpenCVTest5 )
itk_add_test( NAME VideoGrabberOpenCVTest6
  COMMAND ITKVideoGrabberTestDriver VideoGrabberOpenCVTest6 )




