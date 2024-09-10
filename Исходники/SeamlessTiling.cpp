int main(int argc, char* argv[])
{
  // Verify arguments
  if(argc < 5)
  {
    std::cout << "Usage: PatchImage repeatX repeatY outputImage" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse arguments
  std::string patchImageFilename = argv[1];

  std::stringstream ssRepeatX;
  ssRepeatX << argv[2];
  unsigned int repeatX = 0;
  ssRepeatX >> repeatX;

  std::stringstream ssRepeatY;
  ssRepeatY << argv[3];
  unsigned int repeatY = 0;
  ssRepeatY >> repeatY;

  std::string outputFilename = argv[4];

  // Output arguments
  std::cout << "Patch image: " << patchImageFilename << std::endl
            << "Repeat X: " << repeatX << std::endl
            << "Repeat Y: " << repeatY << std::endl
            << "Output image: " << outputFilename << std::endl;

  //typedef itk::VectorImage<float, 2> ImageType;
  typedef itk::Image<itk::CovariantVector<float, 3>, 2> ImageType;

  // Read patch image
  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer patchImageReader = ImageReaderType::New();
  patchImageReader->SetFileName(patchImageFilename);
  patchImageReader->Update();

  Mask::Pointer mask = Mask::New();
  itk::ImageRegion<2> patchRegion = patchImageReader->GetOutput()->GetLargestPossibleRegion();
  mask->SetRegions(patchRegion);
  mask->Allocate();

  itk::Index<2> holeCorner = {{1,1}};
  itk::Size<2> holeSize = patchRegion.GetSize();
  holeSize[0] -= 2; // Missing one row on the top, and one row on the bottom
  holeSize[1] -= 2; // Missing one column on the left, and one column on the right
  itk::ImageRegion<2> holeRegion(holeCorner, holeSize);
  mask->SetValid(patchRegion);
  mask->SetHole(holeRegion);


  ImageType::Pointer seamlessPatch = ImageType::New();
  ITKHelpers::DeepCopy(patchImageReader->GetOutput(), seamlessPatch.GetPointer());

  // Enforce periodic boundary conditions
  // Top and bottom
  for(int i = 0; i < static_cast<int>(patchRegion.GetSize()[1]); ++i)
  {
      itk::Index<2> topPixelIndex = {{0, i}};
      itk::Index<2> bottomPixelIndex = {{static_cast<int>(patchRegion.GetSize()[0])-1, i}};
      ImageType::PixelType topPixelValue = seamlessPatch->GetPixel(topPixelIndex);
      ImageType::PixelType bottomPixelValue = seamlessPatch->GetPixel(bottomPixelIndex);
      ImageType::PixelType averageValue = (topPixelValue + bottomPixelValue)/2.0f;
      seamlessPatch->SetPixel(topPixelIndex, averageValue);
      seamlessPatch->SetPixel(bottomPixelIndex, averageValue);
  }

  // Left and right
  for(int i = 0; i < static_cast<int>(patchRegion.GetSize()[0]); ++i)
  {
      itk::Index<2> leftPixelIndex = {{i, 0}};
      itk::Index<2> rightPixelIndex = {{i, static_cast<int>(patchRegion.GetSize()[1])-1}};
      ImageType::PixelType leftPixelValue = seamlessPatch->GetPixel(leftPixelIndex);
      ImageType::PixelType rightPixelValue = seamlessPatch->GetPixel(rightPixelIndex);
      ImageType::PixelType averageValue = (leftPixelValue + rightPixelValue)/2.0f;
      seamlessPatch->SetPixel(leftPixelIndex, averageValue);
      seamlessPatch->SetPixel(rightPixelIndex, averageValue);
  }

  typedef PoissonEditingParent::GuidanceFieldType GuidanceFieldType;

  std::vector<GuidanceFieldType::Pointer> guidanceFields = PoissonEditingParent::ComputeGuidanceField(patchImageReader->GetOutput());

  ImageType::Pointer output = ImageType::New();

  FillImage(seamlessPatch.GetPointer(), mask.GetPointer(),
            guidanceFields, output.GetPointer(),
            patchRegion, seamlessPatch.GetPointer());


  // Write output
  ITKHelpers::WriteRGBImage(output.GetPointer(), outputFilename);

  // Original tiled
  ImageType::Pointer originalTiled = ImageType::New();
  TilePatch(patchImageReader->GetOutput(), repeatX, repeatY, originalTiled.GetPointer());
  ITKHelpers::WriteRGBImage(originalTiled.GetPointer(), "original_tiled.png");

  // Seamless tiled
  ImageType::Pointer seamlessTiled = ImageType::New();
  TilePatch(output.GetPointer(), repeatX, repeatY, seamlessTiled.GetPointer());
  ITKHelpers::WriteRGBImage(seamlessTiled.GetPointer(), "seamless_tiled.png");

  return EXIT_SUCCESS;
}