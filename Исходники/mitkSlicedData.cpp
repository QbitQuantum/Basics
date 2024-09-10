void mitk::SlicedData::SetGeometry(BaseGeometry *aGeometry3D)
{
  if (aGeometry3D != nullptr)
  {
    ProportionalTimeGeometry::Pointer timeGeometry = ProportionalTimeGeometry::New();
    SlicedGeometry3D::Pointer slicedGeometry = dynamic_cast<SlicedGeometry3D *>(aGeometry3D);
    if (slicedGeometry.IsNull())
    {
      PlaneGeometry *geometry2d = dynamic_cast<PlaneGeometry *>(aGeometry3D);
      if (geometry2d != nullptr && dynamic_cast<mitk::AbstractTransformGeometry *>(aGeometry3D) == nullptr)
      {
        if ((GetSlicedGeometry()->GetPlaneGeometry(0) == geometry2d) && (GetSlicedGeometry()->GetSlices() == 1))
          return;
        slicedGeometry = SlicedGeometry3D::New();
        slicedGeometry->InitializeEvenlySpaced(geometry2d, 1);
      }
      else
      {
        slicedGeometry = SlicedGeometry3D::New();
        PlaneGeometry::Pointer planeGeometry = PlaneGeometry::New();
        planeGeometry->InitializeStandardPlane(aGeometry3D);
        slicedGeometry->InitializeEvenlySpaced(planeGeometry, (unsigned int)(aGeometry3D->GetExtent(2)));
      }
    }
    assert(slicedGeometry.IsNotNull());

    timeGeometry->Initialize(slicedGeometry, 1);
    Superclass::SetTimeGeometry(timeGeometry);
  }
  else
  {
    if (GetGeometry() == nullptr)
      return;
    Superclass::SetGeometry(nullptr);
  }
}