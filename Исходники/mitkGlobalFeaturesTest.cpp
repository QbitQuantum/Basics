  void setUp(void)
  {
    // Load Image Data
    m_Image = dynamic_cast<mitk::Image*>(mitk::IOUtil::Load(GetTestDataFilePath("Pic3D.nrrd"))[0].GetPointer());
    mitk::CastToItkImage(m_Image,m_ItkImage);

    // Create a single mask with only one pixel within the regions
    mitk::Image::Pointer mask1 = dynamic_cast<mitk::Image*>(mitk::IOUtil::Load(GetTestDataFilePath("Pic3D.nrrd"))[0].GetPointer());
    mitk::CastToItkImage(mask1,m_ItkMask);
    m_ItkMask->FillBuffer(0);
    MaskType::IndexType index;
    index[0]=88;index[1]=81;index[2]=13;
    m_ItkMask->SetPixel(index, 1);
    MITK_INFO << "Pixel Value: "<<m_ItkImage->GetPixel(index);
    mitk::CastToMitkImage(m_ItkMask, m_Mask);

    // Create a mask with a covered region
    mitk::Image::Pointer lmask1 = dynamic_cast<mitk::Image*>(mitk::IOUtil::Load(GetTestDataFilePath("Pic3D.nrrd"))[0].GetPointer());
    mitk::CastToItkImage(lmask1,m_ItkMask1);
    m_ItkMask1->FillBuffer(0);
    int range=2;
    for (int x = 88-range;x < 88+range+1;++x)
    {
      for (int y=81-range;y<81+range+1;++y)
      {
        for (int z=13-range;z<13+range+1;++z)
        {
          index[0] = x;
          index[1] = y;
          index[2] = z;
          //MITK_INFO << "Pixel: " <<m_ItkImage->GetPixel(index);
          m_ItkMask1->SetPixel(index, 1);
        }
      }
    }
    mitk::CastToMitkImage(m_ItkMask1, m_Mask1);

    m_GradientImage=GenerateGradientWithDimXImage<unsigned char>(5,5,5);
    m_GradientMask = GenerateMaskImage<unsigned char>(5,5,5);
  }