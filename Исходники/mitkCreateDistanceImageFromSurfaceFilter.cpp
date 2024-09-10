void mitk::CreateDistanceImageFromSurfaceFilter::CreateDistanceImage()
{
  DistanceImageType::Pointer distanceImg = DistanceImageType::New();

  // Determine the bounds of the input points in index- and world-coordinates
  DistanceImageType::PointType minPointInWorldCoordinates, maxPointInWorldCoordinates;
  DistanceImageType::IndexType minPointInIndexCoordinates, maxPointInIndexCoordinates;

  DetermineBounds( minPointInWorldCoordinates, maxPointInWorldCoordinates,
                   minPointInIndexCoordinates, maxPointInIndexCoordinates );


  // Calculate the extent of the region that contains all given points in MM.
  // To do this, we take the difference between the maximal and minimal
  // index-coordinates (must not be less than 1) and multiply it with the
  // spacing of the reference-image.
  Vector3D extentMM;
  for (unsigned int dim = 0; dim < 3; ++dim)
  {
    extentMM[dim] = (int)
      (
                    (std::max( std::abs(maxPointInIndexCoordinates[dim] - minPointInIndexCoordinates[dim]),
                              (DistanceImageType::IndexType::IndexValueType) 1
                            ) + 1.0) // (max-index - min-index)+1 because the pixels between index 3 and 5 cover 2+1=3 pixels (pixel 3,4, and 5)
                    * m_ReferenceImage->GetSpacing()[dim]
      ) + 1; // (int) ((...) + 1) -> we round up to the next BIGGER int value
  }

  /*
  * Now create an empty distance image. The create image will always have the same sizeOfRegion, independent from
  * the original image (e.g. always consists of 500000 pixels) and will have an isotropic spacing.
  * The spacing is calculated like the following:
  * The image's volume = 500000 Pixels = extentX*spacing*extentY*spacing*extentZ*spacing
  * So the spacing is: spacing = ( 500000 / extentX*extentY*extentZ )^(1/3)
  */
  double basis = (extentMM[0]*extentMM[1]*extentMM[2]) / m_DistanceImageVolume;
  double exponent = 1.0/3.0;
  double distImgSpacing = pow(basis, exponent);
  int tempSpacing = (distImgSpacing+0.05)*10;
  m_DistanceImageSpacing = (double)tempSpacing/10.0;

  // calculate the number of pixels of the distance image for each direction
  unsigned int numberOfXPixel = extentMM[0] / m_DistanceImageSpacing;
  unsigned int numberOfYPixel = extentMM[1] / m_DistanceImageSpacing;
  unsigned int numberOfZPixel = extentMM[2] / m_DistanceImageSpacing;

  // We increase the sizeOfRegion by 4 as we decrease the origin by 2 later.
  // This expansion of the region is necessary to achieve a complete
  // interpolation.
  DistanceImageType::SizeType sizeOfRegion;
  sizeOfRegion[0] = numberOfXPixel + 4;
  sizeOfRegion[1] = numberOfYPixel + 4;
  sizeOfRegion[2] = numberOfZPixel + 4;

  // The region starts at index 0,0,0
  DistanceImageType::IndexType initialOriginAsIndex;
  initialOriginAsIndex.Fill(0);

  DistanceImageType::PointType originAsWorld = minPointInWorldCoordinates;

  DistanceImageType::RegionType lpRegion;
  lpRegion.SetSize(sizeOfRegion);
  lpRegion.SetIndex(initialOriginAsIndex);

  // We initialize the itk::Image with
  //  * origin and direction to have it correctly placed and rotated in the world
  //  * the largest possible region to set the extent to be calculated
  //  * the isotropic spacing that we have calculated above
  distanceImg->SetOrigin( originAsWorld );
  distanceImg->SetDirection( m_ReferenceImage->GetDirection() );
  distanceImg->SetRegions( lpRegion );
  distanceImg->SetSpacing( m_DistanceImageSpacing );
  distanceImg->Allocate();

  //First of all the image is initialized with the value 10 for each pixel
  distanceImg->FillBuffer(10);

  // Now we move the origin of the distanceImage 2 index-Coordinates
  // in all directions
  DistanceImageType::IndexType originAsIndex;
  distanceImg->TransformPhysicalPointToIndex( originAsWorld, originAsIndex );
  originAsIndex[0] -= 2;
  originAsIndex[1] -= 2;
  originAsIndex[2] -= 2;
  distanceImg->TransformIndexToPhysicalPoint( originAsIndex, originAsWorld );
  distanceImg->SetOrigin( originAsWorld );

  /*
  * Now we must calculate the distance for each pixel. But instead of calculating the distance value
  * for all of the image's pixels we proceed similar to the region growing algorithm:
  *
  * 1. Take the first pixel from the narrowband_point_list and calculate the distance for each neighbor (6er)
  * 2. If the current index's distance value is below a certain threshold push it into the list
  * 3. Next iteration take the next index from the list and originAsIndex with 1. again
  *
  * This is done until the narrowband_point_list is empty.
  */
  std::queue<DistanceImageType::IndexType> narrowbandPoints;
  PointType currentPoint = m_Centers.at(0);
  double distance = this->CalculateDistanceValue(currentPoint);

  // create itk::Point from vnl_vector
  DistanceImageType::PointType currentPointAsPoint;
  currentPointAsPoint[0] = currentPoint[0];
  currentPointAsPoint[1] = currentPoint[1];
  currentPointAsPoint[2] = currentPoint[2];

  // Transform the input point in world-coordinates to index-coordinates
  DistanceImageType::IndexType currentIndex;
  distanceImg->TransformPhysicalPointToIndex( currentPointAsPoint, currentIndex );

  assert( lpRegion.IsInside(currentIndex) ); // we are quite certain this should hold

  narrowbandPoints.push(currentIndex);
  distanceImg->SetPixel(currentIndex, distance);

  NeighborhoodImageIterator::RadiusType radius;
  radius.Fill(1);
  NeighborhoodImageIterator nIt(radius, distanceImg, distanceImg->GetLargestPossibleRegion());
  unsigned int relativeNbIdx[] = {4, 10, 12, 14, 16, 22};

  bool isInBounds = false;
  while ( !narrowbandPoints.empty() )
  {

    nIt.SetLocation(narrowbandPoints.front());
    narrowbandPoints.pop();

    unsigned int* relativeNb = &relativeNbIdx[0];
    for (int i = 0; i < 6; i++)
    {
      nIt.GetPixel(*relativeNb, isInBounds);
      if( isInBounds && nIt.GetPixel(*relativeNb) == 10)
      {
        currentIndex = nIt.GetIndex(*relativeNb);

        // Transform the currently checked point from index-coordinates to
        // world-coordinates
        distanceImg->TransformIndexToPhysicalPoint( currentIndex, currentPointAsPoint );

        // create a vnl_vector
        currentPoint[0] = currentPointAsPoint[0];
        currentPoint[1] = currentPointAsPoint[1];
        currentPoint[2] = currentPointAsPoint[2];

        // and check the distance
        distance = this->CalculateDistanceValue(currentPoint);
        if ( abs(distance) <= m_DistanceImageSpacing )
        {
          nIt.SetPixel(*relativeNb, distance);
          narrowbandPoints.push(currentIndex);
        }
      }
      relativeNb++;
    }
  }

  // Fist we set the border slices of the image to value 1000 so that we can perform a
  // region growing afterwards starting from the middle of the image

  DistanceImageType::SizeType reqSize;

  reqSize[0] = distanceImg->GetLargestPossibleRegion().GetSize()[0];
  reqSize[1] = distanceImg->GetLargestPossibleRegion().GetSize()[1];
  reqSize[2] = 1;

  DistanceImageType::IndexType reqStart;
  reqStart[0] = 0;
  reqStart[1] = 0;
  reqStart[2] = 0;

  DistanceImageType::RegionType reqRegion;

  reqRegion.SetSize(reqSize);
  reqRegion.SetIndex(reqStart);

  this->FillImageRegion(reqRegion, 1000, distanceImg);

  reqStart[0] = 0;
  reqStart[1] = 0;
  reqStart[2] = distanceImg->GetLargestPossibleRegion().GetSize()[2]-1;

  reqRegion.SetIndex(reqStart);

  this->FillImageRegion(reqRegion, 1000, distanceImg);

  reqSize[0] = 1;
  reqSize[1] = distanceImg->GetLargestPossibleRegion().GetSize()[1];
  reqSize[2] = distanceImg->GetLargestPossibleRegion().GetSize()[2];;

  reqStart[0] = 0;
  reqStart[1] = 0;
  reqStart[2] = 0;

  reqRegion.SetSize(reqSize);
  reqRegion.SetIndex(reqStart);

  this->FillImageRegion(reqRegion, 1000, distanceImg);

  reqStart[0] = distanceImg->GetLargestPossibleRegion().GetSize()[0]-1;
  reqStart[1] = 0;
  reqStart[2] = 0;

  reqRegion.SetIndex(reqStart);

  this->FillImageRegion(reqRegion, 1000, distanceImg);

  reqSize[0] = distanceImg->GetLargestPossibleRegion().GetSize()[0];
  reqSize[1] = 1;
  reqSize[2] = distanceImg->GetLargestPossibleRegion().GetSize()[2];;

  reqStart[0] = 0;
  reqStart[1] = 0;
  reqStart[2] = 0;

  reqRegion.SetSize(reqSize);
  reqRegion.SetIndex(reqStart);

  this->FillImageRegion(reqRegion, 1000, distanceImg);

  reqStart[0] = 0;
  reqStart[1] = distanceImg->GetLargestPossibleRegion().GetSize()[1]-1;
  reqStart[2] = 0;

  reqRegion.SetIndex(reqStart);

  this->FillImageRegion(reqRegion, 1000, distanceImg);

  // Now we make some kind of region growing from the middle of the image to set all
  // inner pixels to -10. In this way we assure to extract a valid surface
  NeighborhoodImageIterator nIt2(radius, distanceImg, distanceImg->GetLargestPossibleRegion());

  currentIndex[0] = distanceImg->GetLargestPossibleRegion().GetSize()[0]*0.5;
  currentIndex[1] = distanceImg->GetLargestPossibleRegion().GetSize()[1]*0.5;
  currentIndex[2] = distanceImg->GetLargestPossibleRegion().GetSize()[2]*0.5;

  narrowbandPoints.push(currentIndex);
  distanceImg->SetPixel(currentIndex, -10);

  while ( !narrowbandPoints.empty() )
  {

    nIt2.SetLocation(narrowbandPoints.front());
    narrowbandPoints.pop();

    for (int i = 0; i < 6; i++)
    {
      if( nIt2.GetPixel(relativeNbIdx[i]) == 10)
      {
          currentIndex = nIt2.GetIndex(relativeNbIdx[i]);
          nIt2.SetPixel(relativeNbIdx[i], -10);
          narrowbandPoints.push(currentIndex);
      }
    }
  }

  Image::Pointer resultImage = this->GetOutput();

  // Cast the created distance-Image from itk::Image to the mitk::Image
  // that is our output.
  CastToMitkImage(distanceImg, resultImage);
}