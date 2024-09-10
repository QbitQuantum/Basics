void mitk::ExtrudePlanarFigureFilter::GenerateData()
{
  typedef PlanarFigure::PolyLineType PolyLine;
  typedef PolyLine::const_iterator PolyLineConstIter;

  if (m_Length <= 0)
    mitkThrow() << "Length is not positive!";

  if (m_NumberOfSegments == 0)
    mitkThrow() << "Number of segments is zero!";

  if (m_BendAngle != 0 && m_BendDirection[0] == 0 && m_BendDirection[1] == 0)
    mitkThrow() << "Bend direction is zero-length vector!";

  PlanarFigure* input = dynamic_cast<PlanarFigure*>(this->GetPrimaryInput());

  if (input == NULL)
    mitkThrow() << "Primary input is not a planar figure!";

  size_t numPolyLines = input->GetPolyLinesSize();

  if (numPolyLines == 0)
    mitkThrow() << "Primary input does not contain any poly lines!";

  const PlaneGeometry* planeGeometry = dynamic_cast<const PlaneGeometry*>(input->GetPlaneGeometry());

  if (planeGeometry == NULL)
    mitkThrow() << "Could not get plane geometry from primary input!";

  Vector3D planeNormal = planeGeometry->GetNormal();
  planeNormal.Normalize();

  Point2D centerPoint2d = GetCenterPoint(input);

  Point3D centerPoint3d;
  planeGeometry->Map(centerPoint2d, centerPoint3d);

  Vector3D bendDirection3d = m_BendAngle != 0
    ? ::GetBendDirection(planeGeometry, centerPoint2d, m_BendDirection)
    : Vector3D();

  ScalarType radius = m_Length * (360 / m_BendAngle) / (2 * vnl_math::pi);
  Vector3D scaledBendDirection3d = bendDirection3d * radius;

  Vector3D bendAxis = itk::CrossProduct(planeNormal, bendDirection3d);
  bendAxis.Normalize();

  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
  vtkIdType baseIndex = 0;

  for (size_t i = 0; i < numPolyLines; ++i)
  {
    PolyLine polyLine = input->GetPolyLine(i);
    size_t numPoints = polyLine.size();

    if (numPoints < 2)
      mitkThrow() << "Poly line " << i << " of primary input consists of less than two points!";

    std::vector<mitk::Point3D> crossSection;

    PolyLineConstIter polyLineEnd = polyLine.end();

    for (PolyLineConstIter polyLineIter = polyLine.begin(); polyLineIter != polyLineEnd; ++polyLineIter)
    {
      Point3D point;
      planeGeometry->Map(*polyLineIter, point);
      crossSection.push_back(point);
    }

    ScalarType segmentLength = m_Length / m_NumberOfSegments;
    Vector3D translation = planeNormal * segmentLength;

    bool bend = std::abs(m_BendAngle) > mitk::eps;
    bool twist = std::abs(m_TwistAngle) > mitk::eps;

    ScalarType twistAngle = twist
      ? m_TwistAngle / m_NumberOfSegments * vnl_math::pi / 180
      : 0;

    ScalarType bendAngle = bend
      ? m_BendAngle / m_NumberOfSegments * vnl_math::pi / 180
      : 0;

    if (m_FlipDirection)
    {
      translation *= -1;
      bendAngle *= -1;
    }

    for (size_t k = 0; k < numPoints; ++k)
      points->InsertNextPoint(crossSection[k].GetDataPointer());

    for (size_t j = 1; j <= m_NumberOfSegments; ++j)
    {
      mitk::AffineTransform3D::Pointer transform = mitk::AffineTransform3D::New();

      if (bend || twist)
        transform->Translate(centerPoint3d.GetVectorFromOrigin(), true);

      if (bend)
      {
        transform->Translate(scaledBendDirection3d, true);
        transform->Rotate3D(bendAxis, bendAngle * j, true);
        transform->Translate(-scaledBendDirection3d, true);
      }
      else
      {
        transform->Translate(translation * j, true);
      }

      if (twist)
        transform->Rotate3D(planeNormal, twistAngle * j, true);

      if (bend || twist)
        transform->Translate(-centerPoint3d.GetVectorFromOrigin(), true);

      for (size_t k = 0; k < numPoints; ++k)
      {
        mitk::Point3D transformedPoint = transform->TransformPoint(crossSection[k]);
        points->InsertNextPoint(transformedPoint.GetDataPointer());
      }
    }

    for (size_t j = 0; j < m_NumberOfSegments; ++j)
    {
      for (size_t k = 1; k < numPoints; ++k)
      {
        vtkIdType cell[3];
        cell[0] = baseIndex + j * numPoints + (k - 1);
        cell[1] = baseIndex + (j + 1) * numPoints + (k - 1);
        cell[2] = baseIndex + j * numPoints + k;

        cells->InsertNextCell(3, cell);

        cell[0] = cell[1];
        cell[1] = baseIndex + (j + 1) * numPoints + k;

        cells->InsertNextCell(3, cell);
      }

      if (input->IsClosed() && numPoints > 2)
      {
        vtkIdType cell[3];
        cell[0] = baseIndex + j * numPoints + (numPoints - 1);
        cell[1] = baseIndex + (j + 1) * numPoints + (numPoints - 1);
        cell[2] = baseIndex + j * numPoints;

        cells->InsertNextCell(3, cell);

        cell[0] = cell[1];
        cell[1] = baseIndex + (j + 1) * numPoints;

        cells->InsertNextCell(3, cell);
      }
    }

    baseIndex += points->GetNumberOfPoints();
  }

  vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);
  polyData->SetPolys(cells);

  vtkSmartPointer<vtkPolyDataNormals> polyDataNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
  polyDataNormals->SetFlipNormals(m_FlipNormals);
  polyDataNormals->SetInputData(polyData);
  polyDataNormals->SplittingOff();

  polyDataNormals->Update();

  Surface* output = static_cast<Surface*>(this->GetPrimaryOutput());
  output->SetVtkPolyData(polyDataNormals->GetOutput());
}