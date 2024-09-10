inline void
randPSurface (vtkPolyData * polydata, std::vector<double> * cumulativeAreas, double totalArea, Eigen::Vector3f& p, bool calcNormal, Eigen::Vector3f& n, bool calcColor, Eigen::Vector3f& c)
{
  float r = static_cast<float> (uniform_deviate (rand ()) * totalArea);

  std::vector<double>::iterator low = std::lower_bound (cumulativeAreas->begin (), cumulativeAreas->end (), r);
  vtkIdType el = vtkIdType (low - cumulativeAreas->begin ());

  double A[3], B[3], C[3];
  vtkIdType npts = 0;
  vtkIdType *ptIds = NULL;
  polydata->GetCellPoints (el, npts, ptIds);
  polydata->GetPoint (ptIds[0], A);
  polydata->GetPoint (ptIds[1], B);
  polydata->GetPoint (ptIds[2], C);
  if (calcNormal)
  {
    // OBJ: Vertices are stored in a counter-clockwise order by default
    Eigen::Vector3f v1 = Eigen::Vector3f (A[0], A[1], A[2]) - Eigen::Vector3f (C[0], C[1], C[2]);
    Eigen::Vector3f v2 = Eigen::Vector3f (B[0], B[1], B[2]) - Eigen::Vector3f (C[0], C[1], C[2]);
    n = v1.cross (v2);
    n.normalize ();
  }
  float r1 = static_cast<float> (uniform_deviate (rand ()));
  float r2 = static_cast<float> (uniform_deviate (rand ()));
  randomPointTriangle (float (A[0]), float (A[1]), float (A[2]),
                       float (B[0]), float (B[1]), float (B[2]),
                       float (C[0]), float (C[1]), float (C[2]), r1, r2, p);

  if (calcColor)
  {
    vtkUnsignedCharArray *const colors = vtkUnsignedCharArray::SafeDownCast (polydata->GetPointData ()->GetScalars ());
    if (colors && colors->GetNumberOfComponents () == 3)
    {
      double cA[3], cB[3], cC[3];
      colors->GetTuple (ptIds[0], cA);
      colors->GetTuple (ptIds[1], cB);
      colors->GetTuple (ptIds[2], cC);

      randomPointTriangle (float (cA[0]), float (cA[1]), float (cA[2]),
                           float (cB[0]), float (cB[1]), float (cB[2]),
                           float (cC[0]), float (cC[1]), float (cC[2]), r1, r2, c);
    }
    else
    {
      static bool printed_once = false;
      if (!printed_once)
        PCL_WARN ("Mesh has no vertex colors, or vertex colors are not RGB!");
      printed_once = true;
    }
  }
}