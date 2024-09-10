int CGUIPanelContainer::GetCurrentColumn() const
{
  return GetCursor() % m_itemsPerRow;
}