static std::vector<itk::Index<2> > FindSeedPoints(const mitk::CorrectorAlgorithm::TSegData &segment, itk::Image< ipMITKSegmentationTYPE, 2 >::Pointer pic, int fillColor)
{
  typedef itk::Image< ipMITKSegmentationTYPE, 2 > ItkImageType;
  typedef itk::Image< ipMITKSegmentationTYPE, 2 >::Pointer ItkImagePointerType;

  int colorMode = (pic->GetPixel(segment.points[0]) == fillColor);
  std::vector<itk::Index<2> > seedPoints;

  try
  {
    itk::Index<2> firstPoint = GetFirstPoint(segment,  pic, fillColor);
    seedPoints.push_back(firstPoint);
  }
  catch (mitk::Exception e)
  {
    return seedPoints;
  }

  if (segment.points.size() < 4)
    return seedPoints;

  std::vector< itk::Index<2> >::const_iterator indexIterator;
  std::vector< itk::Index<2> >::const_iterator indexEnd;

  indexIterator = segment.points.begin();
  indexEnd = segment.points.end();

  ItkImagePointerType listOfPoints = CloneImage(pic);
  listOfPoints->FillBuffer(0);
  listOfPoints->SetPixel(seedPoints[0],1);
  for (; indexIterator != indexEnd; ++indexIterator)
  {
    listOfPoints->SetPixel(*indexIterator, 2);
  }
  indexIterator = segment.points.begin();
  indexIterator++;
  indexIterator++;
  indexEnd--;
  indexEnd--;
  for (; indexIterator != indexEnd; ++indexIterator)
  {
    bool pointFound = true;
    while (pointFound)
    {
      pointFound = false;
      itk::Index<2> index;
      itk::Index<2> index2;
      for (int xOffset = -1 ; xOffset < 2; ++xOffset)
      {
        for (int yOffset = -1 ; yOffset < 2; ++yOffset)
        {
          index[0] = (*indexIterator)[0] - xOffset;
          index[1] = (*indexIterator)[1] - yOffset;
          index2 = index;

          if (listOfPoints->GetPixel(index2) > 0)
            continue;

          index[0]--;
          if (listOfPoints->GetPixel(index) == 1)
          {
            pointFound = true;
            seedPoints.push_back(index2);
            listOfPoints->SetPixel(index2,1);
            continue;
          }
          index[0]=index[0] + 2;
          if (listOfPoints->GetPixel(index) == 1)
          {
            pointFound = true;
            seedPoints.push_back(index2);
            listOfPoints->SetPixel(index2,1);
            continue;
          }
          index[0]--;
          index[1]--;
          if (listOfPoints->GetPixel(index) == 1)
          {
            pointFound = true;
            seedPoints.push_back(index2);
            listOfPoints->SetPixel(index2,1);
            continue;
          }
          index[1]=index[1] + 2;
          if (listOfPoints->GetPixel(index) == 1)
          {
            pointFound = true;
            seedPoints.push_back(index2);
            listOfPoints->SetPixel(index2,1);
            continue;
          }
        }
      }
    }
  }
  return seedPoints;
}