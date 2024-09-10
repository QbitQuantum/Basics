void mitk::LiveWireTool2D::FindHighestGradientMagnitudeByITK(itk::Image<TPixel, VImageDimension> *inputImage,
                                                             itk::Index<3> &index,
                                                             itk::Index<3> &returnIndex)
{
  typedef itk::Image<TPixel, VImageDimension> InputImageType;
  typedef typename InputImageType::IndexType IndexType;

  unsigned long xMAX = inputImage->GetLargestPossibleRegion().GetSize()[0];
  unsigned long yMAX = inputImage->GetLargestPossibleRegion().GetSize()[1];

  returnIndex[0] = index[0];
  returnIndex[1] = index[1];
  returnIndex[2] = 0.0;

  double gradientMagnitude = 0.0;
  double maxGradientMagnitude = 0.0;

  /*
    the size and thus the region of 7x7 is only used to calculate the gradient magnitude in that region
    not for searching the maximum value
    */

  // maximum value in each direction for size
  typename InputImageType::SizeType size;
  size[0] = 7;
  size[1] = 7;

  // minimum value in each direction for startRegion
  IndexType startRegion;
  startRegion[0] = index[0] - 3;
  startRegion[1] = index[1] - 3;
  if (startRegion[0] < 0)
    startRegion[0] = 0;
  if (startRegion[1] < 0)
    startRegion[1] = 0;
  if (xMAX - index[0] < 7)
    startRegion[0] = xMAX - 7;
  if (yMAX - index[1] < 7)
    startRegion[1] = yMAX - 7;

  index[0] = startRegion[0] + 3;
  index[1] = startRegion[1] + 3;

  typename InputImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(startRegion);

  typedef typename itk::GradientMagnitudeImageFilter<InputImageType, InputImageType> GradientMagnitudeFilterType;
  typename GradientMagnitudeFilterType::Pointer gradientFilter = GradientMagnitudeFilterType::New();
  gradientFilter->SetInput(inputImage);
  gradientFilter->GetOutput()->SetRequestedRegion(region);

  gradientFilter->Update();
  typename InputImageType::Pointer gradientMagnImage;
  gradientMagnImage = gradientFilter->GetOutput();

  IndexType currentIndex;
  currentIndex[0] = 0;
  currentIndex[1] = 0;

  // search max (approximate) gradient magnitude
  for (int x = -1; x <= 1; ++x)
  {
    currentIndex[0] = index[0] + x;

    for (int y = -1; y <= 1; ++y)
    {
      currentIndex[1] = index[1] + y;

      gradientMagnitude = gradientMagnImage->GetPixel(currentIndex);

      // check for new max
      if (maxGradientMagnitude < gradientMagnitude)
      {
        maxGradientMagnitude = gradientMagnitude;
        returnIndex[0] = currentIndex[0];
        returnIndex[1] = currentIndex[1];
        returnIndex[2] = 0.0;
      } // end if
    }   // end for y

    currentIndex[1] = index[1];
  } // end for x
}