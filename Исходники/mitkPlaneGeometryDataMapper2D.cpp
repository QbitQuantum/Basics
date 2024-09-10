void mitk::PlaneGeometryDataMapper2D::CreateVtkCrosshair(mitk::BaseRenderer *renderer)
{
  bool visible = true;
  LocalStorage* ls = m_LSH.GetLocalStorage(renderer);
  ls->m_CrosshairActor->SetVisibility(0);
  ls->m_ArrowActor->SetVisibility(0);
  ls->m_CrosshairHelperLineActor->SetVisibility(0);

  GetDataNode()->GetVisibility(visible, renderer, "visible");

  if(!visible)
  {
    return;
  }

  PlaneGeometryData::Pointer input = const_cast< PlaneGeometryData * >(this->GetInput());
  mitk::DataNode* geometryDataNode = renderer->GetCurrentWorldPlaneGeometryNode();
  const PlaneGeometryData* rendererWorldPlaneGeometryData = dynamic_cast< PlaneGeometryData * >(geometryDataNode->GetData());

  // intersecting with ourself?
  if ( input.IsNull() || input.GetPointer() == rendererWorldPlaneGeometryData)
  {
    return; //nothing to do in this case
  }

  const PlaneGeometry *inputPlaneGeometry = dynamic_cast< const PlaneGeometry * >( input->GetPlaneGeometry() );

  const PlaneGeometry* worldPlaneGeometry = dynamic_cast< const PlaneGeometry* >(
        rendererWorldPlaneGeometryData->GetPlaneGeometry() );

  if ( worldPlaneGeometry && dynamic_cast<const AbstractTransformGeometry*>(worldPlaneGeometry)==NULL
       && inputPlaneGeometry && dynamic_cast<const AbstractTransformGeometry*>(input->GetPlaneGeometry() )==NULL
       && inputPlaneGeometry->GetReferenceGeometry() )
  {
    const BaseGeometry *referenceGeometry = inputPlaneGeometry->GetReferenceGeometry();

    // calculate intersection of the plane data with the border of the
    // world geometry rectangle
    Point3D point1, point2;

    Line3D crossLine;

    // Calculate the intersection line of the input plane with the world plane
    if ( worldPlaneGeometry->IntersectionLine( inputPlaneGeometry, crossLine ) )
    {
      Point3D boundingBoxMin, boundingBoxMax;
      boundingBoxMin = referenceGeometry->GetCornerPoint(0);
      boundingBoxMax = referenceGeometry->GetCornerPoint(7);

      Point3D indexLinePoint;
      Vector3D indexLineDirection;

      referenceGeometry->WorldToIndex(crossLine.GetPoint(),indexLinePoint);
      referenceGeometry->WorldToIndex(crossLine.GetDirection(),indexLineDirection);

      referenceGeometry->WorldToIndex(boundingBoxMin,boundingBoxMin);
      referenceGeometry->WorldToIndex(boundingBoxMax,boundingBoxMax);

      // Then, clip this line with the (transformed) bounding box of the
      // reference geometry.
      Line3D::BoxLineIntersection(
            boundingBoxMin[0], boundingBoxMin[1], boundingBoxMin[2],
          boundingBoxMax[0], boundingBoxMax[1], boundingBoxMax[2],
          indexLinePoint, indexLineDirection,
          point1, point2 );

      referenceGeometry->IndexToWorld(point1,point1);
      referenceGeometry->IndexToWorld(point2,point2);
      crossLine.SetPoints(point1,point2);

      vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
      vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
      vtkSmartPointer<vtkPolyData> linesPolyData = vtkSmartPointer<vtkPolyData>::New();


      // Now iterate through all other lines displayed in this window and
      // calculate the positions of intersection with the line to be
      // rendered; these positions will be stored in lineParams to form a
      // gap afterwards.
      NodesVectorType::iterator otherPlanesIt = m_OtherPlaneGeometries.begin();
      NodesVectorType::iterator otherPlanesEnd = m_OtherPlaneGeometries.end();

      std::vector<Point3D> intersections;

      intersections.push_back(point1);

      otherPlanesIt = m_OtherPlaneGeometries.begin();
      int gapsize = 32;
      this->GetDataNode()->GetPropertyValue( "Crosshair.Gap Size",gapsize, NULL );


      ScalarType lineLength = point1.EuclideanDistanceTo(point2);
      DisplayGeometry *displayGeometry = renderer->GetDisplayGeometry();

      ScalarType gapinmm = gapsize * displayGeometry->GetScaleFactorMMPerDisplayUnit();

      float gapSizeParam = gapinmm / lineLength;

      while ( otherPlanesIt != otherPlanesEnd )
      {
        PlaneGeometry *otherPlane = static_cast< PlaneGeometry * >(
              static_cast< PlaneGeometryData * >((*otherPlanesIt)->GetData() )->GetPlaneGeometry() );

        if (otherPlane != inputPlaneGeometry && otherPlane != worldPlaneGeometry)
        {
          Point3D planeIntersection;
          otherPlane->IntersectionPoint(crossLine,planeIntersection);
          ScalarType sectionLength = point1.EuclideanDistanceTo(planeIntersection);
          ScalarType lineValue = sectionLength/lineLength;
          if(lineValue-gapSizeParam > 0.0)
            intersections.push_back(crossLine.GetPoint(lineValue-gapSizeParam));
          else intersections.pop_back();
          if(lineValue+gapSizeParam < 1.0)
            intersections.push_back(crossLine.GetPoint(lineValue+gapSizeParam));
        }
        ++otherPlanesIt;
      }
      if(intersections.size()%2 == 1)
        intersections.push_back(point2);

      if(intersections.empty())
      {
        this->DrawLine(point1,point2,lines,points);
      }
      else
        for(unsigned int i = 0 ; i< intersections.size()-1 ; i+=2)
        {
          this->DrawLine(intersections[i],intersections[i+1],lines,points);
        }

      // Add the points to the dataset
      linesPolyData->SetPoints(points);
      // Add the lines to the dataset
      linesPolyData->SetLines(lines);

      Vector3D orthogonalVector;
      orthogonalVector = inputPlaneGeometry->GetNormal();
      worldPlaneGeometry->Project(orthogonalVector,orthogonalVector);
      orthogonalVector.Normalize();

      // Visualize
      ls->m_Mapper->SetInputData(linesPolyData);
      ls->m_CrosshairActor->SetMapper(ls->m_Mapper);

      // Determine if we should draw the area covered by the thick slicing, default is false.
      // This will also show the area of slices that do not have thick slice mode enabled
      bool showAreaOfThickSlicing = false;
      GetDataNode()->GetBoolProperty( "reslice.thickslices.showarea", showAreaOfThickSlicing );

      // determine the pixelSpacing in that direction
      double thickSliceDistance = SlicedGeometry3D::CalculateSpacing( referenceGeometry->GetSpacing(), orthogonalVector );

      IntProperty *intProperty=0;
      if( GetDataNode()->GetProperty( intProperty, "reslice.thickslices.num" ) && intProperty )
        thickSliceDistance *= intProperty->GetValue()+0.5;
      else
        showAreaOfThickSlicing = false;

      // not the nicest place to do it, but we have the width of the visible bloc in MM here
      // so we store it in this fancy property
      GetDataNode()->SetFloatProperty( "reslice.thickslices.sizeinmm", thickSliceDistance*2 );

      ls->m_CrosshairActor->SetVisibility(1);

      vtkSmartPointer<vtkPolyData> arrowPolyData = vtkSmartPointer<vtkPolyData>::New();
      ls->m_Arrowmapper->SetInputData(arrowPolyData);
      if(this->m_RenderOrientationArrows)
      {
        ScalarType triangleSizeMM = 7.0 * displayGeometry->GetScaleFactorMMPerDisplayUnit();

        vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();
        vtkSmartPointer<vtkPoints> triPoints = vtkSmartPointer<vtkPoints>::New();

        DrawOrientationArrow(triangles,triPoints,triangleSizeMM,orthogonalVector,point1,point2);
        DrawOrientationArrow(triangles,triPoints,triangleSizeMM,orthogonalVector,point2,point1);
        arrowPolyData->SetPoints(triPoints);
        arrowPolyData->SetPolys(triangles);
        ls->m_ArrowActor->SetVisibility(1);
      }

      // Visualize
      vtkSmartPointer<vtkPolyData> helperlinesPolyData = vtkSmartPointer<vtkPolyData>::New();
      ls->m_HelperLinesmapper->SetInputData(helperlinesPolyData);
      if ( showAreaOfThickSlicing )
      {
        vtkSmartPointer<vtkCellArray> helperlines = vtkSmartPointer<vtkCellArray>::New();
        // vectorToHelperLine defines how to reach the helperLine from the mainLine
        // got the right direction, so we multiply the width
        Vector3D vecToHelperLine = orthogonalVector * thickSliceDistance;

        this->DrawLine(point1 - vecToHelperLine, point2 - vecToHelperLine,helperlines,points);
        this->DrawLine(point1 + vecToHelperLine, point2 + vecToHelperLine,helperlines,points);

        // Add the points to the dataset
        helperlinesPolyData->SetPoints(points);

        // Add the lines to the dataset
        helperlinesPolyData->SetLines(helperlines);

        ls->m_CrosshairActor->GetProperty()->SetLineStipplePattern(0xf0f0);
        ls->m_CrosshairActor->GetProperty()->SetLineStippleRepeatFactor(1);
        ls->m_CrosshairHelperLineActor->SetVisibility(1);
      }
    }
  }
}