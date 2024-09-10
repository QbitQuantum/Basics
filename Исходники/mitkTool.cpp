mitk::DataNode::Pointer mitk::Tool::CreateEmptySegmentationNode( Image* original, const std::string& organName, const mitk::Color& color )
{
  // we NEED a reference image for size etc.
  if (!original) return NULL;

  // actually create a new empty segmentation
  PixelType pixelType(mitk::MakeScalarPixelType<DefaultSegmentationDataType>() );
  Image::Pointer segmentation = Image::New();

  if (original->GetDimension() == 2)
  {
    const unsigned int dimensions[] = { original->GetDimension(0), original->GetDimension(1), 1 };
    segmentation->Initialize(pixelType, 3, dimensions);
  }
  else
  {
    segmentation->Initialize(pixelType, original->GetDimension(), original->GetDimensions());
  }

  unsigned int byteSize = sizeof(DefaultSegmentationDataType);
  for (unsigned int dim = 0; dim < segmentation->GetDimension(); ++dim)
  {
    byteSize *= segmentation->GetDimension(dim);
  }
  memset( segmentation->GetData(), 0, byteSize );

  if (original->GetTimeSlicedGeometry() )
  {
    AffineGeometryFrame3D::Pointer originalGeometryAGF = original->GetTimeSlicedGeometry()->Clone();
    TimeSlicedGeometry::Pointer originalGeometry = dynamic_cast<TimeSlicedGeometry*>( originalGeometryAGF.GetPointer() );
    segmentation->SetGeometry( originalGeometry );
  }
  else
  {
    Tool::ErrorMessage("Original image does not have a 'Time sliced geometry'! Cannot create a segmentation.");
    return NULL;
  }

  return CreateSegmentationNode( segmentation, organName, color );
}