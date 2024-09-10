//-----------------------------------------------------------------------------
Point TriangleCell::cell_normal(const Cell& cell) const
{
  // Get mesh geometry
  const MeshGeometry& geometry = cell.mesh().geometry();

  // Cell_normal only defined for gdim = 2, 3:
  const std::size_t gdim = geometry.dim();
  if (gdim > 3)
  {
    dolfin_error("TriangleCell.cpp",
                 "compute cell normal",
                 "Illegal geometric dimension (%d)", gdim);
  }

  // Get the three vertices as points
  const unsigned int* vertices = cell.entities(0);
  const Point p0 = geometry.point(vertices[0]);
  const Point p1 = geometry.point(vertices[1]);
  const Point p2 = geometry.point(vertices[2]);

  // Defined cell normal via cross product of first two edges:
  const Point v01 = p1 - p0;
  const Point v02 = p2 - p0;
  Point n = v01.cross(v02);

  // Normalize
  n /= n.norm();

  return n;
}