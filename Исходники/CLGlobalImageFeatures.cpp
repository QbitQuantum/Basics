static void
ExtractSlicesFromImages(mitk::Image::Pointer image, mitk::Image::Pointer mask,
                        mitk::Image::Pointer maskNoNaN, mitk::Image::Pointer morphMask,
                        int direction,
                        std::vector<mitk::Image::Pointer> &imageVector,
                        std::vector<mitk::Image::Pointer> &maskVector,
                        std::vector<mitk::Image::Pointer> &maskNoNaNVector,
                        std::vector<mitk::Image::Pointer> &morphMaskVector)
{
  typedef itk::Image< double, 2 >                 FloatImage2DType;
  typedef itk::Image< unsigned short, 2 >          MaskImage2DType;

  FloatImageType::Pointer itkFloat = FloatImageType::New();
  MaskImageType::Pointer itkMask = MaskImageType::New();
  MaskImageType::Pointer itkMaskNoNaN = MaskImageType::New();
  MaskImageType::Pointer itkMorphMask = MaskImageType::New();
  mitk::CastToItkImage(mask, itkMask);
  mitk::CastToItkImage(maskNoNaN, itkMaskNoNaN);
  mitk::CastToItkImage(image, itkFloat);
  mitk::CastToItkImage(morphMask, itkMorphMask);

  int idxA, idxB, idxC;
  switch (direction)
  {
  case 0:
    idxA = 1; idxB = 2; idxC = 0;
    break;
  case 1:
    idxA = 0; idxB = 2; idxC = 1;
    break;
  case 2:
    idxA = 0; idxB = 1; idxC = 2;
    break;
  default:
    idxA = 1; idxB = 2; idxC = 0;
    break;
  }

  auto imageSize = image->GetLargestPossibleRegion().GetSize();
  FloatImageType::IndexType index3D;
  FloatImage2DType::IndexType index2D;
  FloatImage2DType::SpacingType spacing2D;
  spacing2D[0] = itkFloat->GetSpacing()[idxA];
  spacing2D[1] = itkFloat->GetSpacing()[idxB];

  for (unsigned int i = 0; i < imageSize[idxC]; ++i)
  {
    FloatImage2DType::RegionType region;
    FloatImage2DType::IndexType start;
    FloatImage2DType::SizeType size;
    start[0] = 0; start[1] = 0;
    size[0] = imageSize[idxA];
    size[1] = imageSize[idxB];
    region.SetIndex(start);
    region.SetSize(size);

    FloatImage2DType::Pointer image2D = FloatImage2DType::New();
    image2D->SetRegions(region);
    image2D->Allocate();

    MaskImage2DType::Pointer mask2D = MaskImage2DType::New();
    mask2D->SetRegions(region);
    mask2D->Allocate();

    MaskImage2DType::Pointer masnNoNaN2D = MaskImage2DType::New();
    masnNoNaN2D->SetRegions(region);
    masnNoNaN2D->Allocate();

    MaskImage2DType::Pointer morph2D = MaskImage2DType::New();
    morph2D->SetRegions(region);
    morph2D->Allocate();


    unsigned long voxelsInMask = 0;

    for (unsigned int a = 0; a < imageSize[idxA]; ++a)
    {
      for (unsigned int b = 0; b < imageSize[idxB]; ++b)
      {
        index3D[idxA] = a;
        index3D[idxB] = b;
        index3D[idxC] = i;
        index2D[0] = a;
        index2D[1] = b;
        image2D->SetPixel(index2D, itkFloat->GetPixel(index3D));
        mask2D->SetPixel(index2D, itkMask->GetPixel(index3D));
        masnNoNaN2D->SetPixel(index2D, itkMaskNoNaN->GetPixel(index3D));
        morph2D->SetPixel(index2D, itkMorphMask->GetPixel(index3D));
        voxelsInMask += (itkMask->GetPixel(index3D) > 0) ? 1 : 0;

      }
    }

    image2D->SetSpacing(spacing2D);
    mask2D->SetSpacing(spacing2D);
    masnNoNaN2D->SetSpacing(spacing2D);
    morph2D->SetSpacing(spacing2D);

    mitk::Image::Pointer tmpFloatImage = mitk::Image::New();
    tmpFloatImage->InitializeByItk(image2D.GetPointer());
    mitk::GrabItkImageMemory(image2D, tmpFloatImage);

    mitk::Image::Pointer tmpMaskImage = mitk::Image::New();
    tmpMaskImage->InitializeByItk(mask2D.GetPointer());
    mitk::GrabItkImageMemory(mask2D, tmpMaskImage);

    mitk::Image::Pointer tmpMaskNoNaNImage = mitk::Image::New();
    tmpMaskNoNaNImage->InitializeByItk(masnNoNaN2D.GetPointer());
    mitk::GrabItkImageMemory(masnNoNaN2D, tmpMaskNoNaNImage);

    mitk::Image::Pointer tmpMorphMaskImage = mitk::Image::New();
    tmpMorphMaskImage->InitializeByItk(morph2D.GetPointer());
    mitk::GrabItkImageMemory(morph2D, tmpMorphMaskImage);

    if (voxelsInMask > 0)
    {
      imageVector.push_back(tmpFloatImage);
      maskVector.push_back(tmpMaskImage);
      maskNoNaNVector.push_back(tmpMaskNoNaNImage);
      morphMaskVector.push_back(tmpMorphMaskImage);
    }
  }
}