void SuperPixelSegmentationGUI::slot_IterationComplete(unsigned int numberOfSegments)
{
  std::stringstream ss;
  ss << "Computed " << numberOfSegments << " segments." << std::endl;
  this->statusBar()->showMessage(ss.str().c_str());
  
  typedef itk::Image<itk::RGBPixel<unsigned char>, 2> RGBImageType;
  RGBImageType::Pointer colorImage = RGBImageType::New();
  colorImage->SetRegions(this->LabelImage->GetLargestPossibleRegion());
  colorImage->Allocate();

  unsigned int maxLabel = Helpers::MaxValue<LabelImageType>(this->LabelImage);
  std::vector<RGBImageType::PixelType> segmentColors;
  for(unsigned int labelId = 0; labelId <= maxLabel; ++labelId)
    {
    //std::cout << "Coloring label " << labelId << std::endl;
    float rgb[3] = {0,0,0};
    itk::ImageRegionIterator<LabelImageType> labelIterator(this->LabelImage, this->LabelImage->GetLargestPossibleRegion());
    unsigned int counter = 0;
    while(!labelIterator.IsAtEnd())
      {
      if(labelIterator.Get() == labelId)
        {
        rgb[0] += this->Image->GetPixel(labelIterator.GetIndex())[0];
        rgb[1] += this->Image->GetPixel(labelIterator.GetIndex())[1];
        rgb[2] += this->Image->GetPixel(labelIterator.GetIndex())[2];
        counter++;
        }// end if
      ++labelIterator;
      } // end while
    RGBImageType::PixelType colorPixel;
    colorPixel[0] = rgb[0]/static_cast<float>(counter);
    colorPixel[1] = rgb[1]/static_cast<float>(counter);
    colorPixel[2] = rgb[2]/static_cast<float>(counter);
    segmentColors.push_back(colorPixel);
    } // end for
    
        
  itk::ImageRegionIterator<LabelImageType> colorIterator(this->LabelImage, this->LabelImage->GetLargestPossibleRegion());
  
  while(!colorIterator.IsAtEnd())
    {
    colorImage->SetPixel(colorIterator.GetIndex(), segmentColors[colorIterator.Get()]);

    ++colorIterator;
    } // end while

  QImage qimage = HelpersQt::GetQImageRGB<RGBImageType>(colorImage);
  if(this->LabelImagePixmapItem)
    {
    this->Scene->removeItem(this->LabelImagePixmapItem);
    }
  this->LabelImagePixmapItem = this->Scene->addPixmap(QPixmap::fromImage(qimage));

  Refresh();
}