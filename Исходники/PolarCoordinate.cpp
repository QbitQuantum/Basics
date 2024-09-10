//_____________________________________________________________________________
CPolarCoordinate::CPolarCoordinate(const CPoint2d& rectangularCoordinate)
{
   m_r     = _hypot(rectangularCoordinate.x,rectangularCoordinate.y);
   m_theta = atan2(rectangularCoordinate.y,rectangularCoordinate.x);
}