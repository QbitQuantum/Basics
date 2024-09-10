bool 
AirspaceCircle::inside(const GeoPoint &loc) const
{
  return (loc.distance(m_center) <= m_radius);
}