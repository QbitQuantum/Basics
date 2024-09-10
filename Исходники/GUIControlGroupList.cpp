float CGUIControlGroupList::GetWidth() const
{
  if (m_orientation == HORIZONTAL)
    return CLAMP(m_totalSize, m_minSize, m_width);
  return CGUIControlGroup::GetWidth();
}