static void CreateMask(Mask::Pointer mask)
{
  itk::Size<2> size;
  size.Fill(20);

  itk::Index<2> start;
  start.Fill(0);

  itk::ImageRegion<2> region(start,size);

  mask->SetRegions(region);
  mask->Allocate();
  mask->FillBuffer(mask->GetValidValue());

  itk::ImageRegionIterator<Mask> iterator(mask, mask->GetLargestPossibleRegion());

  while(!iterator.IsAtEnd())
    {
    if(iterator.GetIndex()[0] > 5 && iterator.GetIndex()[0] < 15 &&
       iterator.GetIndex()[1] > 5 && iterator.GetIndex()[1] < 15)
      {
      mask->SetPixel(iterator.GetIndex(), mask->GetHoleValue());
      }

    ++iterator;
    }
}