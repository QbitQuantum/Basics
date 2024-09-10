void mitk::RegionGrowingTool::StartRegionGrowing(itk::Image<TPixel, imageDimension>* inputImage, itk::Index<imageDimension> seedIndex, std::array<ScalarType, 2> thresholds, mitk::Image::Pointer& outputImage)
{
    MITK_DEBUG << "Starting region growing at index " << seedIndex << " with lower threshold " << thresholds[0] << " and upper threshold " << thresholds[1];

    typedef itk::Image<TPixel, imageDimension> InputImageType;
    typedef itk::Image<DefaultSegmentationDataType, imageDimension> OutputImageType;

    typedef itk::ConnectedThresholdImageFilter<InputImageType, OutputImageType> RegionGrowingFilterType;
    typename RegionGrowingFilterType::Pointer regionGrower = RegionGrowingFilterType::New();

    // perform region growing in desired segmented region
    regionGrower->SetInput(inputImage);
    regionGrower->AddSeed(seedIndex);

    regionGrower->SetLower(thresholds[0]);
    regionGrower->SetUpper(thresholds[1]);

    try
    {
        regionGrower->Update();
    }
    catch(...)
    {
        return; // Should we do something?
    }

    typename OutputImageType::Pointer resultImage = regionGrower->GetOutput();

    // Smooth result: Every pixel is replaced by the majority of the neighborhood
    typedef itk::NeighborhoodIterator<OutputImageType> NeighborhoodIteratorType;
    typedef itk::ImageRegionIterator<OutputImageType> ImageIteratorType;

    typename NeighborhoodIteratorType::RadiusType radius;
    radius.Fill(2); // for now, maybe make this something the user can adjust in the preferences?

    NeighborhoodIteratorType neighborhoodIterator(radius, resultImage, resultImage->GetRequestedRegion());
    ImageIteratorType imageIterator(resultImage, resultImage->GetRequestedRegion());

    for (neighborhoodIterator.GoToBegin(), imageIterator.GoToBegin(); !neighborhoodIterator.IsAtEnd(); ++neighborhoodIterator, ++imageIterator)
    {
        DefaultSegmentationDataType voteYes(0);
        DefaultSegmentationDataType voteNo(0);

        for (unsigned int i = 0; i < neighborhoodIterator.Size(); ++i)
        {
            if (neighborhoodIterator.GetPixel(i) > 0)
            {
                voteYes += 1;
            }
            else
            {
                voteNo += 1;
            }
        }

        if (voteYes > voteNo)
        {
            imageIterator.Set(1);
        }
        else
        {
            imageIterator.Set(0);
        }
    }

    if (resultImage.IsNull())
    {
        MITK_DEBUG << "Region growing result is empty.";
    }

    // Can potentially have multiple regions, use connected component image filter to label disjunct regions
    typedef itk::ConnectedComponentImageFilter<OutputImageType, OutputImageType> ConnectedComponentImageFilterType;
    typename ConnectedComponentImageFilterType::Pointer connectedComponentFilter = ConnectedComponentImageFilterType::New();
    connectedComponentFilter->SetInput(resultImage);
    connectedComponentFilter->Update();
    typename OutputImageType::Pointer resultImageCC = connectedComponentFilter->GetOutput();
    m_ConnectedComponentValue = resultImageCC->GetPixel(seedIndex);

    outputImage = mitk::GrabItkImageMemory(resultImageCC);

}