itk_module_test()
set(Video-Grabber-EpiphanTests
  itkEpiphanVideoGrabberTest.cxx
  itkEpiphanVideoGrabberFactoryTest.cxx
)
CreateTestDriver(Video-Grabber-Epiphan  "${Video-Grabber-Epiphan-Test_LIBRARIES}" "${Video-Grabber-EpiphanTests}")

# EpiphanVideoGrabber:
add_video_test(NAME EpiphanVideoGrabberTest
               COMMAND Video-Grabber-EpiphanTestDriver itkEpiphanVideoGrabberTest
               # Video Input:
               "MIDAS{frame0.jpg.md5},MIDAS{frame1.jpg.md5},MIDAS{frame2.jpg.md5},MIDAS{frame3.jpg.md5},MIDAS{frame4.jpg.md5}"
               # Non-Video Input:
               ${ITKVideo_Data_DIR}/Input/TestParameters.txt
               # Output:
               "${ITK_TEST_OUTPUT_DIR}/frame0.png,${ITK_TEST_OUTPUT_DIR}/frame1.png,${ITK_TEST_OUTPUT_DIR}/frame2.png,${ITK_TEST_OUTPUT_DIR}/frame3.png,${ITK_TEST_OUTPUT_DIR}/frame4.png"
               # Webcam Output:
               ${ITK_TEST_OUTPUT_DIR}/EpiphanVideoGrabberTest_CameraOut.mha
               # Height Width NumFrames FpS
               320 240 5 1
               )

# EpiphanVideoGrabberFactory:
add_video_test(NAME EpiphanVideoGrabberFactoryTest
               COMMAND Video-Grabber-EpiphanTestDriver itkEpiphanVideoGrabberFactoryTest
               # Video Input:
               "MIDAS{frame0.jpg.md5},MIDAS{frame1.jpg.md5},MIDAS{frame2.jpg.md5},MIDAS{frame3.jpg.md5},MIDAS{frame4.jpg.md5}"
               # Output:
               "${ITK_TEST_OUTPUT_DIR}/frame0.png,${ITK_TEST_OUTPUT_DIR}/frame1.png,${ITK_TEST_OUTPUT_DIR}/frame2.png,${ITK_TEST_OUTPUT_DIR}/frame3.png,${ITK_TEST_OUTPUT_DIR}/frame4.png"
               # Webcam Number:
               0
               )
