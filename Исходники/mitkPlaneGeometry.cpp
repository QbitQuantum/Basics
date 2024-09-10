  void
  PlaneGeometry::SetMatrixByVectors( const VnlVector &rightVector,
                                     const VnlVector &downVector, ScalarType thickness /* = 1.0 */ )
  {
    VnlVector normal = vnl_cross_3d(rightVector, downVector);
    normal.normalize();
    normal *= thickness;
    // Crossproduct vnl_cross_3d is always righthanded, but that is okay here
    // because in this method we create a new IndexToWorldTransform and
    // a negative thickness could still make it lefthanded.

    AffineTransform3D::Pointer transform = AffineTransform3D::New();
    Matrix3D matrix;
    matrix.GetVnlMatrix().set_column(0, rightVector);
    matrix.GetVnlMatrix().set_column(1, downVector);
    matrix.GetVnlMatrix().set_column(2, normal);
    transform->SetMatrix(matrix);
    transform->SetOffset(this->GetIndexToWorldTransform()->GetOffset());
    SetIndexToWorldTransform(transform);
  }