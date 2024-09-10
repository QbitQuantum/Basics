void StrokeMask::
Write(const std::string& filename,
      const TPixel& strokeValue)
{
  typedef itk::Image<TPixel, 2> ImageType;
  typename ImageType::Pointer image = ImageType::New();

  image->SetRegions(this->GetLargestPossibleRegion());
  image->Allocate();

  itk::ImageRegionConstIteratorWithIndex<StrokeMask>
      maskIterator(this,
                   this->GetLargestPossibleRegion());
  while(!maskIterator.IsAtEnd())
  {
    if(maskIterator.Get() == StrokeMaskPixelTypeEnum::STROKE)
    {
      image->SetPixel(maskIterator.GetIndex(),
                      strokeValue);
    }
    else
    {
      image->SetPixel(maskIterator.GetIndex(), itk::NumericTraits<TPixel>::Zero);
    }

    ++maskIterator;
  }

  typedef  itk::ImageFileWriter<ImageType> WriterType;
  typename WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(filename);
  writer->SetInput(image);
  writer->Update();

}