double AnnoRect::compRelDist( const AnnoRect& other ) const
{
  double dWidth  = m_x2 - m_x1;
  double dHeight = m_y2 - m_y1;
  double xdist   = (double)(m_x1 + m_x2 - other.x1() - other.x2()) / dWidth;
  double ydist   = (double)(m_y1 + m_y2 - other.y1() - other.y2()) / dHeight;
  return sqrt(xdist*xdist + ydist*ydist);
}