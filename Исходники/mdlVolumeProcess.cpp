bool VolumeProcess::DialateImage(int iterations)
{
	int border = 2;

	ImageType::Pointer tempImg = ImageType::New();
	tempImg->SetRegions( m_outputImage->GetLargestPossibleRegion() );
	tempImg->Allocate();
	tempImg->FillBuffer(0);

	ImageType::RegionType fullRegion = m_outputImage->GetBufferedRegion();
	ImageType::RegionType borderRegion;
	borderRegion.SetIndex(0, fullRegion.GetIndex(0)+border);
	borderRegion.SetIndex(1, fullRegion.GetIndex(1)+border);
	borderRegion.SetIndex(2, fullRegion.GetIndex(2)+border);
	borderRegion.SetSize(0, fullRegion.GetSize(0)-(2*border));
	borderRegion.SetSize(1, fullRegion.GetSize(1)-(2*border));
	borderRegion.SetSize(2, fullRegion.GetSize(2)-(2*border));
	itk::ImageRegionIteratorWithIndex< ImageType > itr( m_outputImage, borderRegion );
	while(iterations > 0)
	{
		for(itr.GoToBegin(); !itr.IsAtEnd(); ++itr)
		{
			double blockMax = itr.Get();
			for(int k=-1; k<=1; k++)
			{
				for(int j=-1; j<=1; j++)
				{
					for(int i=-1; i<=1; i++)
					{
						ImageType::IndexType index = itr.GetIndex();
						index[0] += i;
						index[1] += j;
						index[2] += k;
						ImageType::PixelType pix = m_outputImage->GetPixel(index);
						if((double)pix > blockMax) 
						{
							blockMax = (double)pix;
						}
					}
				}
			}
			// Keep the peak of the original intensity
			if (blockMax == itr.Get() && blockMax != 0)
            {
				blockMax = blockMax + 1;
            }
			tempImg->SetPixel(itr.GetIndex(), blockMax);
		}

		//Copy temp img back to image for next dialation
		itk::ImageRegionIterator< ImageType > itr1( tempImg, tempImg->GetLargestPossibleRegion() );
		itk::ImageRegionIterator< ImageType > itr2( m_outputImage, m_outputImage->GetLargestPossibleRegion() );
		for(itr1.GoToBegin(), itr2.GoToBegin() ; !itr1.IsAtEnd(); ++itr1, ++itr2)
		{
			itr2.Set( itr1.Get() );
		}

		iterations--;
	}
	
	if(debug)
		std::cerr << "Dialation Done" << std::endl;
	return true;
}