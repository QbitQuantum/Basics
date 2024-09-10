void
  mitk::SlicedGeometry3D::InitializeEvenlySpaced(
  mitk::PlaneGeometry* geometry2D, mitk::ScalarType zSpacing,
  unsigned int slices, bool flipped )
{
  assert( geometry2D != nullptr );
  assert( geometry2D->GetExtent(0) > 0 );
  assert( geometry2D->GetExtent(1) > 0 );

  geometry2D->Register();

  Superclass::Initialize();
  m_Slices = slices;

  BoundingBox::BoundsArrayType bounds = geometry2D->GetBounds();
  bounds[4] = 0;
  bounds[5] = slices;

  // clear and reserve
  PlaneGeometry::Pointer gnull = nullptr;
  m_PlaneGeometries.assign( m_Slices, gnull );

  Vector3D directionVector = geometry2D->GetAxisVector(2);
  directionVector.Normalize();
  directionVector *= zSpacing;

  if ( flipped == false )
  {
    // Normally we should use the following four lines to create a copy of
    // the transform contrained in geometry2D, because it may not be changed
    // by us. But we know that SetSpacing creates a new transform without
    // changing the old (coming from geometry2D), so we can use the fifth
    // line instead. We check this at (**).
    //
    // AffineTransform3D::Pointer transform = AffineTransform3D::New();
    // transform->SetMatrix(geometry2D->GetIndexToWorldTransform()->GetMatrix());
    // transform->SetOffset(geometry2D->GetIndexToWorldTransform()->GetOffset());
    // SetIndexToWorldTransform(transform);

    this->SetIndexToWorldTransform( const_cast< AffineTransform3D * >(
      geometry2D->GetIndexToWorldTransform() ));
  }
  else
  {
    directionVector *= -1.0;
    this->SetIndexToWorldTransform( AffineTransform3D::New());
    this->GetIndexToWorldTransform()->SetMatrix(
      geometry2D->GetIndexToWorldTransform()->GetMatrix() );

    AffineTransform3D::OutputVectorType scaleVector;
    FillVector3D(scaleVector, 1.0, 1.0, -1.0);
    this->GetIndexToWorldTransform()->Scale(scaleVector, true);
    this->GetIndexToWorldTransform()->SetOffset(
      geometry2D->GetIndexToWorldTransform()->GetOffset() );
  }

  mitk::Vector3D spacing;
  FillVector3D( spacing,
    geometry2D->GetExtentInMM(0) / bounds[1],
    geometry2D->GetExtentInMM(1) / bounds[3],
    zSpacing );

  this->SetDirectionVector( directionVector );
  this->SetBounds( bounds );
  this->SetPlaneGeometry( geometry2D, 0 );
  this->SetSpacing( spacing, true);
  this->SetEvenlySpaced();

  //this->SetTimeBounds( geometry2D->GetTimeBounds() );

  assert(this->GetIndexToWorldTransform()
    != geometry2D->GetIndexToWorldTransform()); // (**) see above.

  this->SetFrameOfReferenceID( geometry2D->GetFrameOfReferenceID() );
  this->SetImageGeometry( geometry2D->GetImageGeometry() );

  geometry2D->UnRegister();
}