itk_module_test()
set(Video-Grabber-BaseTests
  itkVideoGrabberTest.cxx
)
CreateTestDriver(Video-Grabber-Base  "${Video-Grabber-Base-Test_LIBRARIES}" "${Video-Grabber-BaseTests}")

# VideoFileRederWriterTest:
add_video_test(NAME VideoGrabberTest
               COMMAND Video-Grabber-BaseTestDriver itkVideoFileReaderWriterTest
               # Input
               "MIDAS{frame0.jpg.md5},MIDAS{frame1.jpg.md5},MIDAS{frame2.jpg.md5},MIDAS{frame3.jpg.md5},MIDAS{frame4.jpg.md5}"
               # Output
               "${ITK_TEST_OUTPUT_DIR}/frame0.png,${ITK_TEST_OUTPUT_DIR}/frame1.png,${ITK_TEST_OUTPUT_DIR}/frame2.png,${ITK_TEST_OUTPUT_DIR}/frame3.png,${ITK_TEST_OUTPUT_DIR}/frame4.png"
               )
