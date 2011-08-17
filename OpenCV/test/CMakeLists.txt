itk_module_test()
set(Video-Grabber-OpenCVTests
  itkOpenCVVideoGrabberTest.cxx
  itkOpenCVVideoGrabberFactoryTest.cxx
)
find_package ( OpenCV REQUIRED )
CreateTestDriver(Video-Grabber-OpenCV  "${Video-Grabber-OpenCV-Test_LIBRARIES}" "${Video-Grabber-OpenCVTests}")

# OpenCVVideoGrabber:
add_video_test(NAME OpenCVVideoGrabberTest
               COMMAND Video-Grabber-OpenCVTestDriver itkOpenCVVideoGrabberTest
               # Video Input:
               MIDAS{inde-circulation.avi.md5}
               # Non-Video Input:
               ${ITKVideo_Data_DIR}/Input/TestParameters.txt
               # Output:
               ${ITK_TEST_OUTPUT_DIR}/OpenCVVideoGrabberTest_Out.avi
               # Webcam Output:
               ${ITK_TEST_OUTPUT_DIR}/OpenCVVideoGrabberTest_CameraOut.mha
               # Width Height NumFrames FpS
               320 240 1396 14.985
               )

# OpenCVVideoGrabberFactory:
add_video_test(NAME OpenCVVideoGrabberFactoryTest
               COMMAND Video-Grabber-OpenCVTestDriver itkOpenCVVideoGrabberFactoryTest
               # Video Input:
               MIDAS{inde-circulation.avi.md5}
               # Output:
               ${ITK_TEST_OUTPUT_DIR}/OpenCVVideoGrabberTest_Out.avi
               # Webcam Number:
               0
               )
