//-----------------------------------------------------------------------------
bool DirichletBC::on_facet(const double* coordinates, const Facet& facet) const
{
  // Check if the coordinates are on the same line as the line segment
  if (facet.dim() == 1)
  {
    // Create points
    Point p(coordinates[0], coordinates[1]);
    const Point v0 = Vertex(facet.mesh(), facet.entities(0)[0]).point();
    const Point v1 = Vertex(facet.mesh(), facet.entities(0)[1]).point();

    // Create vectors
    const Point v01 = v1 - v0;
    const Point vp0 = v0 - p;
    const Point vp1 = v1 - p;

    // Check if the length of the sum of the two line segments vp0 and
    // vp1 is equal to the total length of the facet
    if ( std::abs(v01.norm() - vp0.norm() - vp1.norm()) < DOLFIN_EPS )
      return true;
    else
      return false;
  }
  // Check if the coordinates are in the same plane as the triangular
  // facet
  else if (facet.dim() == 2)
  {
    // Create points
    const Point p(coordinates[0], coordinates[1], coordinates[2]);
    const Point v0 = Vertex(facet.mesh(), facet.entities(0)[0]).point();
    const Point v1 = Vertex(facet.mesh(), facet.entities(0)[1]).point();
    const Point v2 = Vertex(facet.mesh(), facet.entities(0)[2]).point();

    // Create vectors
    const Point v01 = v1 - v0;
    const Point v02 = v2 - v0;
    const Point vp0 = v0 - p;
    const Point vp1 = v1 - p;
    const Point vp2 = v2 - p;

    // Check if the sum of the area of the sub triangles is equal to
    // the total area of the facet
    if (std::abs(v01.cross(v02).norm() - vp0.cross(vp1).norm()
                 - vp1.cross(vp2).norm() - vp2.cross(vp0).norm()) < DOLFIN_EPS)
    {
      return true;
    }
    else
      return false;
  }

  dolfin_error("DirichletBC.cpp",
               "determine if given point is on facet",
               "Not implemented for given facet dimension");

  return false;
}