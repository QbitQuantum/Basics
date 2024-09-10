//-----------------------------------------------------------------------------
double IntervalCell::volume(const MeshEntity& interval) const
{
  // Check that we get an interval
  if (interval.dim() != 1)
  {
    dolfin_error("IntervalCell.cpp",
                 "compute volume (length) of interval cell",
                 "Illegal mesh entity, not an interval");
  }

  // Get mesh geometry
  const MeshGeometry& geometry = interval.mesh().geometry();

  // Get the coordinates of the two vertices
  const unsigned int* vertices = interval.entities(0);
  const Point x0 = geometry.point(vertices[0]);
  const Point x1 = geometry.point(vertices[1]);

  return x1.distance(x0);
}