  /*
   * random a voxel. define plane through this voxel. reslice at the plane. compare the pixel vaues of the voxel
   * in the volume with the pixel value in the resliced image.
   * there are some indice shifting problems which causes the test to fail for oblique planes. seems like the chosen
   * worldcoordinate is not corrresponding to the index in the 2D image. and so the pixel values are not the same as
   * expected.
   */
  static void PixelvalueBasedTest()
  {
    /* setup itk image */
    typedef itk::Image<unsigned short, 3> ImageType;

    typedef itk::ImageRegionConstIterator< ImageType > ImageIterator;

    ImageType::Pointer image = ImageType::New();

    ImageType::IndexType start;
    start[0] = start[1] = start[2] = 0;

    ImageType::SizeType size;
    size[0] = size[1] = size[2] = 32;

    ImageType::RegionType imgRegion;
    imgRegion.SetSize(size);
    imgRegion.SetIndex(start);

    image->SetRegions(imgRegion);
    image->SetSpacing(1.0);
    image->Allocate();


    ImageIterator imageIterator( image, image->GetLargestPossibleRegion() );
    imageIterator.GoToBegin();


    unsigned short pixelValue = 0;

    //fill the image with distinct values
    while ( !imageIterator.IsAtEnd() )
    {
      image->SetPixel(imageIterator.GetIndex(), pixelValue);
      ++imageIterator;
      ++pixelValue;
    }
    /* end setup itk image */



    mitk::Image::Pointer imageInMitk;
    CastToMitkImage(image, imageInMitk);



    /*mitk::ImageWriter::Pointer writer = mitk::ImageWriter::New();
    writer->SetInput(imageInMitk);
    std::string file = "C:\\Users\\schroedt\\Desktop\\cube.nrrd";
    writer->SetFileName(file);
    writer->Update();*/

                PixelvalueBasedTestByPlane(imageInMitk, mitk::PlaneGeometry::Frontal);
                PixelvalueBasedTestByPlane(imageInMitk, mitk::PlaneGeometry::Sagittal);
                PixelvalueBasedTestByPlane(imageInMitk, mitk::PlaneGeometry::Axial);

  }