Real Polygon3D::maxDistance(const Plane3D& p) const
{
  Real dmax=0;
  for(size_t i=0;i<vertices.size();i++) {
    Real d = p.distance(vertices[i]);
    if(d > dmax) dmax=d;
  }
  return dmax;
}