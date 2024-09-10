void mitk::SetRegionTool::OnMousePressed(StateMachineAction *, InteractionEvent *interactionEvent)
{
  auto *positionEvent = dynamic_cast<mitk::InteractionPositionEvent *>(interactionEvent);
  if (!positionEvent)
    return;

  m_LastEventSender = positionEvent->GetSender();
  m_LastEventSlice = m_LastEventSender->GetSlice();

  // 1. Get the working image
  Image::Pointer workingSlice = FeedbackContourTool::GetAffectedWorkingSlice(positionEvent);
  if (workingSlice.IsNull())
    return; // can't do anything without the segmentation

  // if click was outside the image, don't continue
  const BaseGeometry *sliceGeometry = workingSlice->GetGeometry();
  itk::Index<3> projectedPointIn2D;
  sliceGeometry->WorldToIndex(positionEvent->GetPositionInWorld(), projectedPointIn2D);
  if (!sliceGeometry->IsIndexInside(projectedPointIn2D))
  {
    MITK_ERROR << "point apparently not inside segmentation slice" << std::endl;
    return; // can't use that as a seed point
  }

  typedef itk::Image<DefaultSegmentationDataType, 2> InputImageType;
  typedef InputImageType::IndexType IndexType;
  typedef itk::ConnectedThresholdImageFilter<InputImageType, InputImageType> RegionGrowingFilterType;
  RegionGrowingFilterType::Pointer regionGrower = RegionGrowingFilterType::New();

  // convert world coordinates to image indices
  IndexType seedIndex;
  sliceGeometry->WorldToIndex(positionEvent->GetPositionInWorld(), seedIndex);

  // perform region growing in desired segmented region
  InputImageType::Pointer itkImage = InputImageType::New();
  CastToItkImage(workingSlice, itkImage);
  regionGrower->SetInput(itkImage);
  regionGrower->AddSeed(seedIndex);

  InputImageType::PixelType bound = itkImage->GetPixel(seedIndex);

  regionGrower->SetLower(bound);
  regionGrower->SetUpper(bound);
  regionGrower->SetReplaceValue(1);

  itk::BinaryFillholeImageFilter<InputImageType>::Pointer fillHolesFilter =
    itk::BinaryFillholeImageFilter<InputImageType>::New();

  fillHolesFilter->SetInput(regionGrower->GetOutput());
  fillHolesFilter->SetForegroundValue(1);

  // Store result and preview
  mitk::Image::Pointer resultImage = mitk::GrabItkImageMemory(fillHolesFilter->GetOutput());
  resultImage->SetGeometry(workingSlice->GetGeometry());
  // Get the current working color
  DataNode *workingNode(m_ToolManager->GetWorkingData(0));
  if (!workingNode)
    return;

  mitk::ImageToContourModelFilter::Pointer contourextractor = mitk::ImageToContourModelFilter::New();
  contourextractor->SetInput(resultImage);
  contourextractor->Update();

  mitk::ContourModel::Pointer awesomeContour = contourextractor->GetOutput();
  FeedbackContourTool::SetFeedbackContour(awesomeContour);
  FeedbackContourTool::SetFeedbackContourVisible(true);
  mitk::RenderingManager::GetInstance()->RequestUpdate(positionEvent->GetSender()->GetRenderWindow());
}