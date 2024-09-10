bool TestIsClosedLoop()
{
  std::cout << "TestIsClosedLoop()" << std::endl;

  // Open loop
  {
  typedef itk::Image<unsigned char, 2> ImageType;
  ImageType::Pointer image = ImageType::New();

  itk::Index<2> corner = {{0,0}};
  itk::Size<2> size = {{100,100}};
  itk::ImageRegion<2> region(corner, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  for(itk::Index<2>::IndexValueType i = 20; i < 30; ++i)
  {
    itk::Index<2> pixel = {{i, 50}};
    image->SetPixel(pixel, 255);
  }

  itk::Index<2> start = {{25, 50}};

  bool isClosedLoop = ITKHelpers::IsClosedLoop(image.GetPointer(), start);

  std::cout << "Is closed loop? " << isClosedLoop << std::endl;
  }

  // Closed loop
  {
  typedef itk::Image<unsigned char, 2> ImageType;
  ImageType::Pointer image = ImageType::New();

  itk::Index<2> corner = {{0,0}};
  itk::Size<2> size = {{100,100}};
  itk::ImageRegion<2> region(corner, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  itk::Index<2> corner0 = {{10,10}};
  itk::Index<2> corner1 = {{30,30}};
  ITKHelpers::DrawRectangle(image.GetPointer(), 255,
                            corner0, corner1);

  itk::Index<2> start = {{10, 10}};

  bool isClosedLoop = ITKHelpers::IsClosedLoop(image.GetPointer(), start);

  std::cout << "Is closed loop? " << isClosedLoop << std::endl;
  }

  return true;
}