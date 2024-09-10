  //
  // CellOnFringe
  //
  // Is the given map cell on the fringe of the given footprint
  //
  Bool CellOnFringe(const Point<S32> &min, const Point<S32> &max, const Point<S32> &pos)
  {
    // Get fringe bounds
    Point<S32> fMin(min - 1);
    Point<S32> fMax(max + 1);

    return 
    (
      (((pos.x == fMin.x) || (pos.x == fMax.x)) && ((pos.z >= fMin.z && pos.z <= fMax.z)))

      ||

      (((pos.z == fMin.z) || (pos.z == fMax.z)) && ((pos.x >= fMin.x && pos.x <= fMax.x)))
    );    
  }