bool
LineSegment::intersect (const LineSegment & l, Point & intersect_p) const
{
  /**
   * First check for concurance:
   *
   *
   * | x1 y1 z1 1 |
   * | x2 y2 z2 1 | = (x3 - x1) * [(x2-x1) x (x4-x3)] = 0
   * | x3 y3 z3 1 |
   * | x4 y4 z4 1 |
   *
   *
   * Solve:
   *   x = _p0 + (_p1 - _p0)*s
   *   x = l.p0 + (l._p1 - l.p0)*t
   *
   *   where
   *   a = _p1 - _p0
   *   b = l._p1 - l._p0
   *   c = l._p0 - _p0
   *
   *   s = (c x b) * (a x b) / | a x b |^2
   */
  RealVectorValue a = _p1 - _p0;
  RealVectorValue b = l._p1 - l._p0;
  RealVectorValue c = l._p0 - _p0;

  RealVectorValue v = a.cross(b);

  // Check for parallel lines
  if (std::abs(v.norm()) < 1.e-10 && std::abs(c.cross(a).norm()) < 1.e-10)
  {
    // TODO: The lines are co-linear but more work is needed to determine and intersection point
    //       it could be the case that the line segments don't lie on the same line or overlap only
    //       a bit
    return true;
  }

  // Check that the lines are coplanar
  Real concur = c * (a.cross(b));
  if (std::abs(concur) > 1.e-10)
    return false;

  Real s = (c.cross(b) * v) / (v*v);
  Real t = (c.cross(a) * v) / (v*v);

  // if s and t are between 0 and 1 then the Line Segments intersect
  // TODO: We could handle other case of clamping to the end of Line
  //       Segements if we want to here

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
  {
    intersect_p = _p0 + s*a;
    return true;
  }
  return false;

  /**
   * Parameteric Equation of lines
   * _p0 + t(v0) = l._p0 + u(v1)
   *
   * Case 1: Parallel Lines
   *         v0 x v1 == 0
   *
   * Case 1a: Collinear Lines
   *         v0 x v1 == 0
   *         (l._p0 - _p0) x (_p1 - _p0) == 0
   *
   * Case 2: Intersecting Lines
   *         0 <= t <= 1
   *         0 <= u <= 1
   *
   *
   * Case 1: The lines do not intersect
   *         vleft cross vright = non-zero
   *
   * Case 2: The lines are co-linear
   *         vleft cross vright = zero
   *         vleft (Denominator) = zero
   *
   * Case 3: The line intersect at a single point
   *         vleft cross vright = zero
   *         vleft (Denominator) = non-zero
  RealVectorValue v0 = _p1 - _p0;
  RealVectorValue v1 = l._p1 - l._p0;
  RealVectorValue v2 = l._p0 - _p0;

  RealVectorValue vbot = v0.cross(v1);
  RealVectorValue vtop = v2.cross(v1);

  RealVectorValue crossed = vleft.cross(vright);

  // Case 1: No intersection
  if (std::abs(vleft.cross(vright).size()) > 1.e-10)
    return false;

  // Case 2: Co-linear (just return one of the end points)
  if (std::abs(vleft.size()) < 1.e-10)
  {
    intersect_p = _p0;
    return true;
  }

  // Case 3:

  //TODO: We could detect whether the Line Segments actually overlap
  //      instead of whether the Lines are co-linear

  Real a = vright.size()/vleft.size();
  intersect_p = _p0 + a*v0;
  return true;
     */
}