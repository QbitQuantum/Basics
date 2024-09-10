void mitk::VectorImageMapper2D::Paint( mitk::BaseRenderer * renderer )
{
  //std::cout << "2d vector mapping..." << std::endl;

  bool visible = true;
  GetDataNode()->GetVisibility(visible, renderer, "visible");

  if ( !visible )
    return ;

  mitk::Image::Pointer input = const_cast<mitk::Image*>( this->GetInput() );

  if ( input.IsNull() )
    return ;


  mitk::PlaneGeometry::Pointer worldPlaneGeometry2D = dynamic_cast< mitk::PlaneGeometry*>( const_cast<mitk::Geometry2D*>( renderer->GetCurrentWorldGeometry2D() ) );
  assert( worldPlaneGeometry2D.IsNotNull() );

  vtkImageData* vtkImage = input->GetVtkImageData( this->GetCurrentTimeStep( input, renderer ) );

  //
  // set up the cutter orientation according to the current geometry of
  // the renderers plane
  //
  Point3D point;
  Vector3D normal;
  Geometry2D::ConstPointer worldGeometry = renderer->GetCurrentWorldGeometry2D();
  PlaneGeometry::ConstPointer worldPlaneGeometry = dynamic_cast<const PlaneGeometry*>( worldGeometry.GetPointer() );

  if ( worldPlaneGeometry.IsNotNull() )
  {
    // set up vtkPlane according to worldGeometry
    point = worldPlaneGeometry->GetOrigin();
    normal = worldPlaneGeometry->GetNormal(); normal.Normalize();
    m_Plane->SetTransform( (vtkAbstractTransform*)NULL );
  }
  else
  {
    itkWarningMacro( << "worldPlaneGeometry is NULL!" );
    return ;
  }

  double vp[ 3 ], vp_slice[ 3 ], vnormal[ 3 ];
  vnl2vtk( point.GetVnlVector(), vp );
  vnl2vtk( normal.GetVnlVector(), vnormal );
  //std::cout << "Origin: " << vp[0] <<" "<< vp[1] <<" "<< vp[2] << std::endl;
  //std::cout << "Normal: " << vnormal[0] <<" "<< vnormal[1] <<" "<< vnormal[2] << std::endl;

  //normally, we would need to transform the surface and cut the transformed surface with the cutter.
  //This might be quite slow. Thus, the idea is, to perform an inverse transform of the plane instead.
  //@todo It probably does not work for scaling operations yet:scaling operations have to be
  //dealed with after the cut is performed by scaling the contour.
  vtkLinearTransform * vtktransform = GetDataNode() ->GetVtkTransform();

  vtkTransform* world2vtk = vtkTransform::New();
  world2vtk->Identity();
  world2vtk->Concatenate(vtktransform->GetLinearInverse());
  double myscale[3];
  world2vtk->GetScale(myscale);
  world2vtk->PostMultiply();
  world2vtk->Scale(1/myscale[0],1/myscale[1],1/myscale[2]);
  world2vtk->TransformPoint( vp, vp );
  world2vtk->TransformNormalAtPoint( vp, vnormal, vnormal );
  world2vtk->Delete();

    // vtk works in axis align coords
  // thus the normal also must be axis align, since
  // we do not allow arbitrary cutting through volume
  //
  // vnormal should already be axis align, but in order
  // to get rid of precision effects, we set the two smaller
  // components to zero here
  int dims[3];
  vtkImage->GetDimensions(dims);
  double spac[3];
  vtkImage->GetSpacing(spac);
  vp_slice[0] = vp[0];
  vp_slice[1] = vp[1];
  vp_slice[2] = vp[2];
  if(fabs(vnormal[0]) > fabs(vnormal[1]) && fabs(vnormal[0]) > fabs(vnormal[2]) )
  {
    if(fabs(vp_slice[0]/spac[0]) < 0.4)
      vp_slice[0] = 0.4*spac[0];
    if(fabs(vp_slice[0]/spac[0]) > (dims[0]-1)-0.4)
      vp_slice[0] = ((dims[0]-1)-0.4)*spac[0];
    vnormal[1] = 0;
    vnormal[2] = 0;
  }

  if(fabs(vnormal[1]) > fabs(vnormal[0]) && fabs(vnormal[1]) > fabs(vnormal[2]) )
  {
    if(fabs(vp_slice[1]/spac[1]) < 0.4)
      vp_slice[1] = 0.4*spac[1];
    if(fabs(vp_slice[1]/spac[1]) > (dims[1]-1)-0.4)
      vp_slice[1] = ((dims[1]-1)-0.4)*spac[1];
    vnormal[0] = 0;
    vnormal[2] = 0;
  }

  if(fabs(vnormal[2]) > fabs(vnormal[1]) && fabs(vnormal[2]) > fabs(vnormal[0]) )
  {
    if(fabs(vp_slice[2]/spac[2]) < 0.4)
      vp_slice[2] = 0.4*spac[2];
    if(fabs(vp_slice[2]/spac[2]) > (dims[2]-1)-0.4)
      vp_slice[2] = ((dims[2]-1)-0.4)*spac[2];
    vnormal[0] = 0;
    vnormal[1] = 0;
  }


  m_Plane->SetOrigin( vp_slice );
  m_Plane->SetNormal( vnormal );

  vtkPolyData* cuttedPlane;
  if(!( (dims[0] == 1 && vnormal[0] != 0) ||
        (dims[1] == 1 && vnormal[1] != 0) ||
        (dims[2] == 1 && vnormal[2] != 0) ))
  {
    m_Cutter->SetCutFunction( m_Plane );
    m_Cutter->SetInputData( vtkImage );
    m_Cutter->GenerateCutScalarsOff();//!
    m_Cutter->Update();
    cuttedPlane = m_Cutter->GetOutput();
  }
  else
  {
    // cutting of a 2D-Volume does not work,
    // so we have to build up our own polydata object
    cuttedPlane = vtkPolyData::New();
    vtkPoints* points = vtkPoints::New();
    points->SetNumberOfPoints(vtkImage->GetNumberOfPoints());
    for(int i=0; i<vtkImage->GetNumberOfPoints(); i++)
      points->SetPoint(i, vtkImage->GetPoint(i));
    cuttedPlane->SetPoints(points);
    vtkFloatArray* pointdata = vtkFloatArray::New();
    int comps  = vtkImage->GetPointData()->GetScalars()->GetNumberOfComponents();
    pointdata->SetNumberOfComponents(comps);
    int tuples = vtkImage->GetPointData()->GetScalars()->GetNumberOfTuples();
    pointdata->SetNumberOfTuples(tuples);
    for(int i=0; i<tuples; i++)
      pointdata->SetTuple(i,vtkImage->GetPointData()->GetScalars()->GetTuple(i));
    pointdata->SetName( "vector" );
    cuttedPlane->GetPointData()->AddArray(pointdata);
  }

  if ( cuttedPlane->GetNumberOfPoints() != 0)
  {
    //
    // make sure, that we have point data with more than 1 component (as vectors)
    //
    vtkPointData * pointData = cuttedPlane->GetPointData();
    if ( pointData == NULL )
    {
      itkWarningMacro( << "no point data associated with cutters result!" );
      return ;
    }