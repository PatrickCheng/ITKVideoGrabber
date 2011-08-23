
itk_module_test()

set(ITKVideoGrabberTests
    OpenCVVideoGrabberTest1.cxx
    OpenCVVideoGrabberTest2.cxx
    OpenCVVideoGrabberTest3.cxx
    OpenCVVideoGrabberTest4.cxx
    OpenCVVideoGrabberTest5.cxx
    OpenCVVideoGrabberTest6.cxx
)

find_package ( OpenCV REQUIRED )
set(ITKVideoGrabber-Test_LIBRARIES ${ITKVideoGrabber_LIBRARIES} ${OpenCV_LIBS})

CreateTestDriver(ITKVideoGrabber "${ITKVideoGrabber-Test_LIBRARIES}" "${ITKVideoGrabberTests}")

itk_add_test( NAME OpenCVVideoGrabberTest1
  COMMAND ITKVideoGrabberTestDriver OpenCVVideoGrabberTest1 )
itk_add_test( NAME OpenCVVideoGrabberTest2
  COMMAND ITKVideoGrabberTestDriver OpenCVVideoGrabberTest2 )
itk_add_test( NAME OpenCVVideoGrabberTest3
  COMMAND ITKVideoGrabberTestDriver OpenCVVideoGrabberTest3 )
itk_add_test( NAME OpenCVVideoGrabberTest4
  COMMAND ITKVideoGrabberTestDriver OpenCVVideoGrabberTest4 )
itk_add_test( NAME OpenCVVideoGrabberTest5
  COMMAND ITKVideoGrabberTestDriver OpenCVVideoGrabberTest5 )
itk_add_test( NAME itkVideoGrabberTest6
  COMMAND ITKVideoGrabberTestDriver OpenCVVideoGrabberTest6 )
