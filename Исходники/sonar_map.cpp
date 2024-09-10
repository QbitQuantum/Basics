bool SonarMap::convertToCell(const double m_x, const double m_y, int &c_x, int &c_y) const
{
  c_x = lround(m_x / resolution_);
  c_y = lround(m_y / resolution_);
  return (map_.isInX(c_x) && map_.isInY(c_y));
}