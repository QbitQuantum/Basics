void mitk::PlanarFigureVtkMapper3D::GenerateDataForRenderer(BaseRenderer* renderer)
{
  typedef PlanarFigure::PolyLineType PolyLine;

  DataNode* node = this->GetDataNode();

  if (node == NULL)
    return;

  PlanarFigure* planarFigure = dynamic_cast<PlanarFigure*>(node->GetData());

  if (planarFigure == NULL || !planarFigure->IsPlaced())
    return;

  LocalStorage* localStorage = m_LocalStorageHandler.GetLocalStorage(renderer);
  unsigned long mTime = planarFigure->GetMTime();

  if (mTime > localStorage->m_LastMTime)
  {
    localStorage->m_LastMTime = mTime;

    const PlaneGeometry* planeGeometry = dynamic_cast<const PlaneGeometry*>(planarFigure->GetPlaneGeometry());
    const AbstractTransformGeometry* abstractTransformGeometry = dynamic_cast<const AbstractTransformGeometry*>(planarFigure->GetPlaneGeometry());

    if (planeGeometry == NULL && abstractTransformGeometry == NULL)
      return;

    size_t numPolyLines = planarFigure->GetPolyLinesSize();

    if (numPolyLines == 0)
      return;

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    vtkIdType baseIndex = 0;

    for (size_t i = 0; i < numPolyLines; ++i)
    {
      PolyLine polyLine = planarFigure->GetPolyLine(i);
      vtkIdType numPoints = polyLine.size();

      if (numPoints < 2)
        continue;

      PolyLine::const_iterator polyLineEnd = polyLine.end();

      for (PolyLine::const_iterator polyLineIt = polyLine.begin(); polyLineIt != polyLineEnd; ++polyLineIt)
      {
        Point3D point;
        planeGeometry->Map(*polyLineIt, point);
        points->InsertNextPoint(point.GetDataPointer());
      }

      vtkSmartPointer<vtkPolyLine> line = vtkSmartPointer<vtkPolyLine>::New();

      vtkIdList* pointIds = line->GetPointIds();

      if (planarFigure->IsClosed() && numPoints > 2)
      {
        pointIds->SetNumberOfIds(numPoints + 1);
        pointIds->SetId(numPoints, baseIndex);
      }
      else
      {
        pointIds->SetNumberOfIds(numPoints);
      }

      for (vtkIdType j = 0; j < numPoints; ++j)
        pointIds->SetId(j, baseIndex + j);

      cells->InsertNextCell(line);

      baseIndex += points->GetNumberOfPoints();
    }

    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetLines(cells);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    localStorage->m_Actor->SetMapper(mapper);
  }

  this->ApplyColorAndOpacityProperties(renderer, localStorage->m_Actor);
  this->ApplyPlanarFigureProperties(renderer, localStorage->m_Actor);
}