bool Aabb::hasCollision(const Aabb& other) const
{
  bool result = false;

  if (intersects(other) == false) return result;

  Vector2f overlapMin(std::max(m_min.x, other.m_min.x), std::max(m_min.y, other.m_min.y));
  Vector2f overlapMax(std::min(m_max.x, other.m_max.x), std::min(m_max.y, other.m_max.y));

  if (contains(other)) result = true;

  return result;
}