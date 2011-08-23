itk_module_test()

set(ITK-VideoGrabberTests
OpenCVVideoGrabberTest1.cxx
OpenCVVideoGrabberTest2.cxx
OpenCVVideoGrabberTest3.cxx
OpenCVVideoGrabberTest4.cxx
OpenCVVideoGrabberTest5.cxx
OpenCVVideoGrabberTest6.cxx
)

set(ITK_TEST_DRIVER itkTestDriver)

CreateTestDriver(ITK-VideoGrabber "${ITK-VideoGrabber-Test_LIBRARIES}" "${ITK-VideoGrabberTests}")

itk_add_test( NAME OpenCVVideoGrabberTest1
  COMMAND ITK-VideoGrabberTestDriver OpenCVVideoGrabberTest1 )
itk_add_test( NAME OpenCVVideoGrabberTest2
  COMMAND ITK-VideoGrabberTestDriver OpenCVVideoGrabberTest2 )
itk_add_test( NAME OpenCVVideoGrabberTest3
  COMMAND ITK-VideoGrabberTestDriver OpenCVVideoGrabberTest3 )
itk_add_test( NAME OpenCVVideoGrabberTest4
  COMMAND ITK-VideoGrabberTestDriver OpenCVVideoGrabberTest4 )
itk_add_test( NAME OpenCVVideoGrabberTest5
  COMMAND ITK-VideoGrabberTestDriver OpenCVVideoGrabberTest5 )
itk_add_test( NAME itkVideoGrabberTest6
  COMMAND ITK-VideoGrabberTestDriver OpenCVVideoGrabberTest6 )
