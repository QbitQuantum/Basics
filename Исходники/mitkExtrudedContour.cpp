void mitk::ExtrudedContour::BuildGeometry()
{
  if(m_Contour.IsNull())
    return;

//  Initialize(1);

  Vector3D nullvector; nullvector.Fill(0.0);
  float xProj[3];
  unsigned int i;
  unsigned int numPts = 20; //m_Contour->GetNumberOfPoints();
  mitk::Contour::PathPointer path = m_Contour->GetContourPath();
  mitk::Contour::PathType::InputType cstart = path->StartOfInput();
  mitk::Contour::PathType::InputType cend   = path->EndOfInput();
  mitk::Contour::PathType::InputType cstep  = (cend-cstart)/numPts;
  mitk::Contour::PathType::InputType ccur;

  // Part I: guarantee/calculate legal vectors

  m_Vector.Normalize();
  itk2vtk(m_Vector, m_Normal);
  // check m_Vector
  if(mitk::Equal(m_Vector, nullvector) || m_AutomaticVectorGeneration)
  {
    if ( m_AutomaticVectorGeneration == false)
      itkWarningMacro("Extrusion vector is 0 ("<< m_Vector << "); trying to use normal of polygon");

    vtkPoints *loopPoints = vtkPoints::New();
    //mitk::Contour::PointsContainerIterator pointsIt = m_Contour->GetPoints()->Begin();
    double vtkpoint[3];

    unsigned int i=0;
    for(i=0, ccur=cstart; i<numPts; ++i, ccur+=cstep)
    {
      itk2vtk(path->Evaluate(ccur), vtkpoint);
      loopPoints->InsertNextPoint(vtkpoint);
    }

    // Make sure points define a loop with a m_Normal
    vtkPolygon::ComputeNormal(loopPoints, m_Normal);
    loopPoints->Delete();

    vtk2itk(m_Normal, m_Vector);
    if(mitk::Equal(m_Vector, nullvector))
    {
      itkExceptionMacro("Cannot calculate normal of polygon");
    }
  }
  // check m_RightVector
  if((mitk::Equal(m_RightVector, nullvector)) || (mitk::Equal(m_RightVector*m_Vector, 0.0)==false))
  {
    if(mitk::Equal(m_RightVector, nullvector))
    {
      itkDebugMacro("Right vector is 0. Calculating.");
    }
    else
    {
      itkWarningMacro("Right vector ("<<m_RightVector<<") not perpendicular to extrusion vector "<<m_Vector<<": "<<m_RightVector*m_Vector);
    }
    // calculate a legal m_RightVector
    if( mitk::Equal( m_Vector[1], 0.0f ) == false )
    {
      FillVector3D( m_RightVector, 1.0f, -m_Vector[0]/m_Vector[1], 0.0f );
      m_RightVector.Normalize();
    }
    else
    {
      FillVector3D( m_RightVector, 0.0f, 1.0f, 0.0f );
    }
  }

  // calculate down-vector
  VnlVector rightDV = m_RightVector.GetVnlVector(); rightDV.normalize(); vnl2vtk(rightDV, m_Right);
  VnlVector downDV  = vnl_cross_3d( m_Vector.GetVnlVector(), rightDV ); downDV.normalize();  vnl2vtk(downDV,  m_Down);

  // Part II: calculate plane as base for extrusion, project the contour
  // on this plane and store as polygon for IsInside test and BoundingBox calculation

  // initialize m_ProjectionPlane, yet with origin at 0
  m_ProjectionPlane->InitializeStandardPlane(rightDV, downDV);

  // create vtkPolygon from contour and simultaneously determine 2D bounds of
  // contour projected on m_ProjectionPlane
  //mitk::Contour::PointsContainerIterator pointsIt = m_Contour->GetPoints()->Begin();
  m_Polygon->Points->Reset();
  m_Polygon->Points->SetNumberOfPoints(numPts);
  m_Polygon->PointIds->Reset();
  m_Polygon->PointIds->SetNumberOfIds(numPts);
  mitk::Point2D pt2d;
  mitk::Point3D pt3d;
  mitk::Point2D min, max;
  min.Fill(ScalarTypeNumericTraits::max());
  max.Fill(ScalarTypeNumericTraits::min());
  xProj[2]=0.0;
  for(i=0, ccur=cstart; i<numPts; ++i, ccur+=cstep)
  {
    pt3d.CastFrom(path->Evaluate(ccur));
    m_ProjectionPlane->Map(pt3d, pt2d);
    xProj[0]=pt2d[0];
    if(pt2d[0]<min[0]) min[0]=pt2d[0];
    if(pt2d[0]>max[0]) max[0]=pt2d[0];
    xProj[1]=pt2d[1];
    if(pt2d[1]<min[1]) min[1]=pt2d[1];
    if(pt2d[1]>max[1]) max[1]=pt2d[1];
    m_Polygon->Points->SetPoint(i, xProj);
    m_Polygon->PointIds->SetId(i, i);
  }
  // shift parametric origin to (0,0)
  for(i=0; i<numPts; ++i)
  {
    double * pt = this->m_Polygon->Points->GetPoint(i);

    pt[0]-=min[0]; pt[1]-=min[1];
    itkDebugMacro( << i << ": (" << pt[0] << "," << pt[1] << "," << pt[2] << ")" );
  }
  this->m_Polygon->GetBounds(m_ProjectedContourBounds);
  //m_ProjectedContourBounds[4]=-1.0; m_ProjectedContourBounds[5]=1.0;

  // calculate origin (except translation along the normal) and bounds
  // of m_ProjectionPlane:
  //  origin is composed of the minimum x-/y-coordinates of the polygon,
  //  bounds from the extent of the polygon, both after projecting on the plane
  mitk::Point3D origin;
  m_ProjectionPlane->Map(min, origin);
  ScalarType bounds[6]={0, max[0]-min[0], 0, max[1]-min[1], 0, 1};
  m_ProjectionPlane->SetBounds(bounds);
  m_ProjectionPlane->SetOrigin(origin);

  // Part III: initialize geometry
  if(m_ClippingGeometry.IsNotNull())
  {
    ScalarType min_dist=ScalarTypeNumericTraits::max(), max_dist=ScalarTypeNumericTraits::min(), dist;
    unsigned char i;
    for(i=0; i<8; ++i)
    {
      dist = m_ProjectionPlane->SignedDistance( m_ClippingGeometry->GetCornerPoint(i) );
      if(dist<min_dist) min_dist=dist;
      if(dist>max_dist) max_dist=dist;
    }
    //incorporate translation along the normal into origin
    origin = origin+m_Vector*min_dist;
    m_ProjectionPlane->SetOrigin(origin);
    bounds[5]=max_dist-min_dist;
  }
  else
    bounds[5]=20;

  itk2vtk(origin, m_Origin);

  mitk::Geometry3D::Pointer g3d = GetGeometry( 0 );
  assert( g3d.IsNotNull() );
  g3d->SetBounds(bounds);
  g3d->SetIndexToWorldTransform(m_ProjectionPlane->GetIndexToWorldTransform());
  g3d->TransferItkToVtkTransform();

  ProportionalTimeGeometry::Pointer timeGeometry = ProportionalTimeGeometry::New();
  timeGeometry->Initialize(g3d,1);
  SetTimeGeometry(timeGeometry);

}