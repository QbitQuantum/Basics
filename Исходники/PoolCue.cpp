bool PoolCue::SetContactPos(float x, float y)
{
  float oldx = m_x;
  float oldy = m_y;
  m_x = x;
  m_y = y;
  if (Intersects())
  {
    m_x = oldx;
    m_y = oldy;
    return false;
  }
  return true;
}