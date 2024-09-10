bool Range::operator==(const Range &o) const
{
  return m_min == o.min() && m_max == o.max();
}