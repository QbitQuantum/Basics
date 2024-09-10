void ForegroundBackgroundSegmentMask::
Write(const std::string& filename,
      const ForegroundPixelValueWrapper<TPixel>& foregroundValue,
      const BackgroundPixelValueWrapper<TPixel>& backgroundValue)
{
  typedef itk::Image<TPixel, 2> ImageType;
  typename ImageType::Pointer image = ImageType::New();

  image->SetRegions(this->GetLargestPossibleRegion());
  image->Allocate();

  itk::ImageRegionConstIteratorWithIndex<ForegroundBackgroundSegmentMask>
      maskIterator(this,
                   this->GetLargestPossibleRegion());
  while(!maskIterator.IsAtEnd())
  {
    if(maskIterator.Get() == ForegroundBackgroundSegmentMaskPixelTypeEnum::FOREGROUND)
    {
      image->SetPixel(maskIterator.GetIndex(),
                      foregroundValue.Value);
    }
    else if(maskIterator.Get() == ForegroundBackgroundSegmentMaskPixelTypeEnum::BACKGROUND)
    {
      image->SetPixel(maskIterator.GetIndex(), backgroundValue.Value);
    }

    ++maskIterator;
  }

  typedef  itk::ImageFileWriter<ImageType> WriterType;
  typename WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(filename);
  writer->SetInput(image);
  writer->Update();

}