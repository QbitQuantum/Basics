void mitk::SurfaceGLMapper2D::PaintCells(mitk::BaseRenderer* renderer, vtkPolyData* contour,
                                       const PlaneGeometry* worldGeometry,
                                       const DisplayGeometry* displayGeometry,
                                       vtkLinearTransform * vtktransform,
                                       vtkLookupTable *lut,
                                       vtkPolyData* original3DObject)
{
  // deprecated settings
  bool usePointData = false;

  bool useCellData = false;
  this->GetDataNode()->GetBoolProperty("deprecated useCellDataForColouring", useCellData, renderer);

  bool scalarVisibility = false;
  this->GetDataNode()->GetBoolProperty("scalar visibility", scalarVisibility, renderer);

  if(scalarVisibility)
  {
    VtkScalarModeProperty* scalarMode;
    if(this->GetDataNode()->GetProperty(scalarMode, "scalar mode", renderer))
    {
      if( (scalarMode->GetVtkScalarMode() == VTK_SCALAR_MODE_USE_POINT_DATA) ||
        (scalarMode->GetVtkScalarMode() == VTK_SCALAR_MODE_DEFAULT) )
      {
        usePointData = true;
      }
      if(scalarMode->GetVtkScalarMode() == VTK_SCALAR_MODE_USE_CELL_DATA)
      {
        useCellData = true;
      }
    }
    else
    {
      usePointData = true;
    }
  }

  vtkPoints    *vpoints = contour->GetPoints();
  vtkDataArray *vpointscalars = contour->GetPointData()->GetScalars();

  vtkCellArray *vlines  = contour->GetLines();
  vtkDataArray* vcellscalars = contour->GetCellData()->GetScalars();

  Point3D p; Point2D p2d, last;
  int i, j;
  int numberOfLines = vlines->GetNumberOfCells();

  glLineWidth( m_LineWidth );
  glBegin (GL_LINES);

  glColor4fv(m_LineColor);

  double distanceSinceLastNormal(0.0);

  vlines->InitTraversal();
  for(i=0;i<numberOfLines;++i)
  {
    vtkIdType *cell(NULL);
    vtkIdType cellSize(0);
    double vp[3];

    vlines->GetNextCell(cellSize, cell);

    vpoints->GetPoint(cell[0], vp);
    //take transformation via vtktransform into account
    vtktransform->TransformPoint(vp, vp);
    vtk2itk(vp, p);

    //convert 3D point (in mm) to 2D point on slice (also in mm)
    worldGeometry->Map(p, p2d);

    //convert point (until now mm and in world coordinates) to display coordinates (units )
    displayGeometry->WorldToDisplay(p2d, p2d);
    last=p2d;

    for(j=1; j<cellSize; ++j)
    {
      vpoints->GetPoint(cell[j], vp);
      Point3D originalPoint;
      vtk2itk(vp, originalPoint);
      //take transformation via vtktransform into account
      vtktransform->TransformPoint(vp, vp);
      vtk2itk(vp, p);

      //convert 3D point (in mm) to 2D point on slice (also in mm)
      worldGeometry->Map(p, p2d);

      //convert point (until now mm and in world coordinates) to display coordinates (units )
      displayGeometry->WorldToDisplay(p2d, p2d);

      double color[3];
      if (useCellData && vcellscalars != NULL )
      {
        // color each cell according to cell data
        lut->GetColor( vcellscalars->GetComponent(i,0),color);
        glColor3f(color[0],color[1],color[2]);
        glVertex2f(last[0], last[1]);
        glVertex2f(p2d[0], p2d[1]);
      }
      else if (usePointData && vpointscalars != NULL )
      {
        lut->GetColor( vpointscalars->GetComponent(cell[j-1],0),color);
        glColor3f(color[0],color[1],color[2]);
        glVertex2f(last[0], last[1]);
        lut->GetColor( vpointscalars->GetComponent(cell[j],0),color);
        glColor3f(color[0],color[1],color[2]);
        glVertex2f(p2d[0], p2d[1]);
      }
      else
      {
        glVertex2f(last[0], last[1]);
        glVertex2f(p2d[0], p2d[1]);

        // draw normals ?
        if (m_DrawNormals && original3DObject)
        {
          distanceSinceLastNormal += sqrt((p2d[0]-last[0])*(p2d[0]-last[0]) + (p2d[1]-last[1])*(p2d[1]-last[1]));
          if (distanceSinceLastNormal >= 5.0)
          {
            distanceSinceLastNormal = 0.0;

            vtkPointData* pointData = original3DObject->GetPointData();
            if (!pointData) break;

            vtkDataArray* normalsArray = pointData->GetNormals();
            if (!normalsArray) break;

            // find 3D point closest to the currently drawn point
            double distance(0.0);
            vtkIdType closestPointId = m_PointLocator->FindClosestPoint(originalPoint[0], originalPoint[1], originalPoint[2], distance);
            if (closestPointId >= 0)
            {
              // find normal of 3D object at this 3D point
              double* normal = normalsArray->GetTuple3(closestPointId);
              double transformedNormal[3];
              vtktransform->TransformNormal(normal, transformedNormal);

              Vector3D normalITK;
              vtk2itk(transformedNormal, normalITK);
              normalITK.Normalize();

              // calculate a point (point from the cut 3D object) + (normal vector of closest point)
              Point3D tip3D = p + normalITK;

              // map this point into our 2D coordinate system
              Point2D tip2D;
              worldGeometry->Map(tip3D, tip2D);

              displayGeometry->WorldToDisplay(tip2D, tip2D);

              // calculate 2D vector from point to point+normal, normalize it to standard length
              Vector2D tipVectorGLFront = tip2D - p2d;
              tipVectorGLFront.Normalize();
              tipVectorGLFront *= m_FrontNormalLengthInPixels;

              Vector2D tipVectorGLBack = p2d - tip2D;
              tipVectorGLBack.Normalize();
              tipVectorGLBack *= m_BackNormalLengthInPixels;

              Point2D tipPoint2D = p2d + tipVectorGLFront;
              Point2D backTipPoint2D = p2d + tipVectorGLBack;

              // draw normalized mapped normal vector
              glColor4f(m_BackSideColor[0], m_BackSideColor[1], m_BackSideColor[2], m_BackSideColor[3]); // red backside
              glVertex2f(p2d[0], p2d[1]);
              glVertex2f(tipPoint2D[0], tipPoint2D[1]);
              glColor4f(m_FrontSideColor[0], m_FrontSideColor[1], m_FrontSideColor[2], m_FrontSideColor[3]); // green backside
              glVertex2f(p2d[0], p2d[1]);
              glVertex2f(backTipPoint2D[0], backTipPoint2D[1]);
              glColor4fv(m_LineColor); // back to line color
            }
          }
        }
      }
      last=p2d;
    }
  }

  glEnd();
  glLineWidth(1.0);
}