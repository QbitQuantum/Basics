bool SolidComposite::BoxIntersects(const BoundingBox& b) const
{
  if (!b.Intersects(m_bsphere))
  {
    return false;
  }

  const int size = m_children.size();
  for (int i = 0; i < size; i++)
  {
    const SolidComponent* pc = m_children[i].GetPtr();
    if (pc->BoxIntersects(b))
    {
      return true;
    }
  }
  return false;
}