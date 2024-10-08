void mitk::UnstructuredGridMapper2D::Paint( mitk::BaseRenderer* renderer )
{
  if ( IsVisible( renderer ) == false )
    return ;

  vtkLinearTransform * vtktransform = GetDataNode()->GetVtkTransform();
  vtkLinearTransform * inversetransform = vtktransform->GetLinearInverse();

  Geometry2D::ConstPointer worldGeometry = renderer->GetCurrentWorldGeometry2D();
  PlaneGeometry::ConstPointer worldPlaneGeometry = dynamic_cast<const PlaneGeometry*>( worldGeometry.GetPointer() );

  Point3D point;
  Vector3D normal;

  if(worldPlaneGeometry.IsNotNull())
  {
    // set up vtkPlane according to worldGeometry
    point=worldPlaneGeometry->GetOrigin();
    normal=worldPlaneGeometry->GetNormal(); normal.Normalize();
    m_Plane->SetTransform((vtkAbstractTransform*)NULL);
  }
  else
  {
    //@FIXME: does not work correctly. Does m_Plane->SetTransform really transforms a "plane plane" into a "curved plane"?
    return;
    AbstractTransformGeometry::ConstPointer worldAbstractGeometry = dynamic_cast<const AbstractTransformGeometry*>(renderer->GetCurrentWorldGeometry2D());
    if(worldAbstractGeometry.IsNotNull())
    {
      // set up vtkPlane according to worldGeometry
      point=const_cast<mitk::BoundingBox*>(worldAbstractGeometry->GetParametricBoundingBox())->GetMinimum();
      FillVector3D(normal, 0, 0, 1);
      m_Plane->SetTransform(worldAbstractGeometry->GetVtkAbstractTransform()->GetInverse());
    }
    else
      return;
  }

  vtkFloatingPointType vp[ 3 ], vnormal[ 3 ];

  vnl2vtk(point.Get_vnl_vector(), vp);
  vnl2vtk(normal.Get_vnl_vector(), vnormal);

  //normally, we would need to transform the surface and cut the transformed surface with the cutter.
  //This might be quite slow. Thus, the idea is, to perform an inverse transform of the plane instead.
  //@todo It probably does not work for scaling operations yet:scaling operations have to be
  //dealed with after the cut is performed by scaling the contour.
  inversetransform->TransformPoint( vp, vp );
  inversetransform->TransformNormalAtPoint( vp, vnormal, vnormal );

  m_Plane->SetOrigin( vp );
  m_Plane->SetNormal( vnormal );

  // set data into cutter
  m_Slicer->SetInput( m_VtkPointSet );
  //    m_Cutter->GenerateCutScalarsOff();
  //    m_Cutter->SetSortByToSortByCell();

  // calculate the cut
  m_Slicer->Update();

  // fetch geometry
  mitk::DisplayGeometry::Pointer displayGeometry = renderer->GetDisplayGeometry();
  assert( displayGeometry );
  //  float toGL=displayGeometry->GetSizeInDisplayUnits()[1];

  //apply color and opacity read from the PropertyList
  ApplyProperties( renderer );

  // traverse the cut contour
  vtkPolyData * contour = m_Slicer->GetOutput();

  vtkPoints *vpoints = contour->GetPoints();
  vtkCellArray *vlines = contour->GetLines();
  vtkCellArray *vpolys = contour->GetPolys();
  vtkPointData *vpointdata = contour->GetPointData();
  vtkDataArray* vscalars = vpointdata->GetScalars();

  vtkCellData *vcelldata = contour->GetCellData();
  vtkDataArray* vcellscalars = vcelldata->GetScalars();

  const int numberOfLines = contour->GetNumberOfLines();
  const int numberOfPolys = contour->GetNumberOfPolys();

  const bool useCellData = m_ScalarMode->GetVtkScalarMode() == VTK_SCALAR_MODE_DEFAULT ||
              m_ScalarMode->GetVtkScalarMode() == VTK_SCALAR_MODE_USE_CELL_DATA;
  const bool usePointData = m_ScalarMode->GetVtkScalarMode() == VTK_SCALAR_MODE_USE_POINT_DATA;

  Point3D p;
  Point2D p2d;

  vlines->InitTraversal();
  vpolys->InitTraversal();
  
  mitk::Color outlineColor = m_Color->GetColor();

  glLineWidth((float)m_LineWidth->GetValue());

  for (int i = 0;i < numberOfLines;++i )
  {
    vtkIdType *cell(0);
    vtkIdType cellSize(0);

    vlines->GetNextCell( cellSize, cell );

    float rgba[4] = {outlineColor[0], outlineColor[1], outlineColor[2], 1.0f};
    if (m_ScalarVisibility->GetValue() && vcellscalars)
    {
      if ( useCellData )
      {  // color each cell according to cell data
        double scalar = vcellscalars->GetComponent( i, 0 );
        double rgb[3] = { 1.0f, 1.0f, 1.0f };
        m_ScalarsToColors->GetColor(scalar, rgb);
        rgba[0] = (float)rgb[0];
        rgba[1] = (float)rgb[1];
        rgba[2] = (float)rgb[2];
        rgba[3] = (float)m_ScalarsToOpacity->GetValue(scalar);
      }
      else if ( usePointData )
      {
        double scalar = vscalars->GetComponent( i, 0 );
        double rgb[3] = { 1.0f, 1.0f, 1.0f };
        m_ScalarsToColors->GetColor(scalar, rgb);
        rgba[0] = (float)rgb[0];
        rgba[1] = (float)rgb[1];
        rgba[2] = (float)rgb[2];
        rgba[3] = (float)m_ScalarsToOpacity->GetValue(scalar);
      }
    }
    
    glColor4fv( rgba );
    
    glBegin ( GL_LINE_LOOP );
    for ( int j = 0;j < cellSize;++j )
    {
      vpoints->GetPoint( cell[ j ], vp );
      //take transformation via vtktransform into account
      vtktransform->TransformPoint( vp, vp );

      vtk2itk( vp, p );

      //convert 3D point (in mm) to 2D point on slice (also in mm)
      worldGeometry->Map( p, p2d );

      //convert point (until now mm and in worldcoordinates) to display coordinates (units )
      displayGeometry->WorldToDisplay( p2d, p2d );

      //convert display coordinates ( (0,0) is top-left ) in GL coordinates ( (0,0) is bottom-left )
      //p2d[1]=toGL-p2d[1];

      //add the current vertex to the line
      glVertex2f( p2d[0], p2d[1] );
    }
    glEnd ();

  }
  
  bool polyOutline = m_Outline->GetValue();
  bool scalarVisibility = m_ScalarVisibility->GetValue();

  // only draw polygons if there are cell scalars
  // or the outline property is set to true
  if ((scalarVisibility && vcellscalars) || polyOutline)
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // cache the transformed points
    // a fixed size array is way faster than 'new'
    // slices through 3d cells usually do not generated
    // polygons with more than 6 vertices
    Point2D cachedPoints[10];

    for (int i = 0;i < numberOfPolys;++i )
    {
      vtkIdType *cell(0);
      vtkIdType cellSize(0);

      vpolys->GetNextCell( cellSize, cell );

      float rgba[4] = {1.0f, 1.0f, 1.0f, 0};
      if (scalarVisibility && vcellscalars)
      {
        if ( useCellData )
        {  // color each cell according to cell data
          double scalar = vcellscalars->GetComponent( i, 0 );
          double rgb[3] = { 1.0f, 1.0f, 1.0f };
          m_ScalarsToColors->GetColor(scalar, rgb);
          rgba[0] = (float)rgb[0];
          rgba[1] = (float)rgb[1];
          rgba[2] = (float)rgb[2];
          rgba[3] = (float)m_ScalarsToOpacity->GetValue(scalar);
        }
        else if ( usePointData )
        {
          double scalar = vscalars->GetComponent( i, 0 );
          double rgb[3] = { 1.0f, 1.0f, 1.0f };
          m_ScalarsToColors->GetColor(scalar, rgb);
          rgba[0] = (float)rgb[0];
          rgba[1] = (float)rgb[1];
          rgba[2] = (float)rgb[2];
          rgba[3] = (float)m_ScalarsToOpacity->GetValue(scalar);
        }
      }
      glColor4fv( rgba );

      glBegin( GL_POLYGON );
      for (int j = 0; j < cellSize; ++j)
      {
        vpoints->GetPoint( cell[ j ], vp );
        //take transformation via vtktransform into account
        vtktransform->TransformPoint( vp, vp );

        vtk2itk( vp, p );

        //convert 3D point (in mm) to 2D point on slice (also in mm)
        worldGeometry->Map( p, p2d );

        //convert point (until now mm and in worldcoordinates) to display coordinates (units )
        displayGeometry->WorldToDisplay( p2d, p2d );

        //convert display coordinates ( (0,0) is top-left ) in GL coordinates ( (0,0) is bottom-left )
        //p2d[1]=toGL-p2d[1];

        cachedPoints[j][0] = p2d[0];
        cachedPoints[j][1] = p2d[1];

        //add the current vertex to the line
        glVertex2f( p2d[0], p2d[1] );
      }
      glEnd();

      if (polyOutline)
      {
        glColor4f(outlineColor[0], outlineColor[1], outlineColor[2], 1.0f);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin( GL_POLYGON );
        //glPolygonOffset(1.0, 1.0);
        for (int j = 0; j < cellSize; ++j)
        {
          //add the current vertex to the line
          glVertex2f( cachedPoints[j][0], cachedPoints[j][1] );
        }
        glEnd();
      }
    }
    glDisable(GL_BLEND);
  }
}