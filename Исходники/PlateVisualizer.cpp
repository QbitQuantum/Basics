  void values(FieldContainer<double> &values, BasisCachePtr basisCache)
  {
    FieldContainer<double> points  = basisCache->getPhysicalCubaturePoints();
    FieldContainer<double> normals = basisCache->getSideNormals();
    int numCells = points.dimension(0);
    int numPoints = points.dimension(1);

    FieldContainer<double> Tv(numCells,numPoints);
    FieldContainer<double> u1v(numCells,numPoints);;
    _u1->values(u1v,basisCache);
    _T->values(Tv,basisCache);

    bool isSubsonic = false;
    double min_y = YTOP;
    double max_y = 0.0;
    values.initialize(0.0);
    for (int cellIndex=0; cellIndex<numCells; cellIndex++)
    {
      for (int ptIndex=0; ptIndex<numPoints; ptIndex++)
      {
        double x = points(cellIndex,ptIndex,0);
        double y = points(cellIndex,ptIndex,1);

        double T = Tv(cellIndex,ptIndex);
        double un = u1v(cellIndex,ptIndex); // WARNING: ASSUMES NORMAL AT OUTFLOW = (1,0)
        double c = sqrt(_gamma * (_gamma-1.0) * _cv * T);

        bool outflowMatch = ((abs(x-2.0) < _tol) && (y > 0.0) && (y < YTOP));
        bool subsonicMatch = (un < c) && (un > 0.0);
        if (subsonicMatch && outflowMatch)
        {
          values(cellIndex,ptIndex) = 1.0;
          isSubsonic = true;
          min_y = min(y,min_y);
          max_y = max(y,max_y);
          //	  cout << "y = " << y << endl;
        }
      }
    }
    if (isSubsonic)
    {
      //      cout << "subsonic in interval y =(" << min_y << "," << max_y << ")" << endl;
    }
  }