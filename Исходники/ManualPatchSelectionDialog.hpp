void ManualPatchSelectionDialog<TImage>::slot_UpdateResult(const itk::ImageRegion<2>& sourceRegion,
                                                           const itk::ImageRegion<2>& targetRegion)
{
  assert(sourceRegion.GetSize() == targetRegion.GetSize());

  if(!this->Image->GetLargestPossibleRegion().IsInside(sourceRegion))
  {
    std::cerr << "Source region is outside the image!" << std::endl;
    return;
  }
  
  QImage qimage(sourceRegion.GetSize()[0], sourceRegion.GetSize()[1], QImage::Format_RGB888);

  if(MaskImage->CountHolePixels(sourceRegion) > 0)
  {
    //std::cerr << "The source patch must not have any hole pixels!" << std::endl;
    //btnAccept->setVisible(false);
    qimage.fill(Qt::green);
  }
  else
  {
    typename TImage::Pointer tempImage = TImage::New();
    ITKHelpers::ConvertTo3Channel(this->Image, tempImage.GetPointer());
    if(this->Image->GetNumberOfComponentsPerPixel() != 3)
      {
      ITKHelpers::ScaleAllChannelsTo255(tempImage.GetPointer());
      }

    itk::ImageRegionIterator<TImage> sourceIterator(tempImage, sourceRegion);
    itk::ImageRegionIterator<TImage> targetIterator(tempImage, targetRegion);
    itk::ImageRegionIterator<Mask> maskIterator(MaskImage, targetRegion);

    typename TImage::Pointer resultPatch = TImage::New();
    resultPatch->SetNumberOfComponentsPerPixel(Image->GetNumberOfComponentsPerPixel());
    itk::ImageRegion<2> resultPatchRegion;
    resultPatchRegion.SetSize(sourceRegion.GetSize());
    resultPatch->SetRegions(resultPatchRegion);
    resultPatch->Allocate();

    while(!maskIterator.IsAtEnd())
      {
      ITKHelpers::FloatVectorImageType::PixelType pixel;

      if(MaskImage->IsHole(maskIterator.GetIndex()))
        {
        pixel = sourceIterator.Get();
        }
      else
        {
        pixel = targetIterator.Get();
        }

      itk::Offset<2> offset = sourceIterator.GetIndex() - sourceRegion.GetIndex();
      itk::Index<2> offsetIndex;
      offsetIndex[0] = offset[0];
      offsetIndex[1] = offset[1];
      resultPatch->SetPixel(offsetIndex, pixel);

      ++sourceIterator;
      ++targetIterator;
      ++maskIterator;
      } // end iterator loop

    qimage = ITKQtHelpers::GetQImageColor(resultPatch.GetPointer(), resultPatch->GetLargestPossibleRegion());
  } // end else

  this->ResultPatchScene->clear();
  QGraphicsPixmapItem* item = this->ResultPatchScene->addPixmap(QPixmap::fromImage(qimage));
  gfxResult->fitInView(item);

}