bool CGUIListContainer::OnAction(const CAction &action)
{
  switch (action.GetID())
  {
  case ACTION_PAGE_UP:
    {
      if (GetOffset() == 0)
      { // already on the first page, so move to the first item
        SetCursor(0);
      }
      else
      { // scroll up to the previous page
        Scroll( -m_itemsPerPage);
      }
      return true;
    }
    break;
  case ACTION_PAGE_DOWN:
    {
      if (GetOffset() == (int)m_items.size() - m_itemsPerPage || (int)m_items.size() < m_itemsPerPage)
      { // already at the last page, so move to the last item.
        SetCursor(m_items.size() - GetOffset() - 1);
      }
      else
      { // scroll down to the next page
        Scroll(m_itemsPerPage);
      }
      return true;
    }
    break;
    // smooth scrolling (for analog controls)
  case ACTION_SCROLL_UP:
    {
      m_analogScrollCount += action.GetAmount() * action.GetAmount();
      bool handled = false;
      while (m_analogScrollCount > 0.4)
      {
        handled = true;
        m_analogScrollCount -= 0.4f;
        if (GetOffset() > 0 && GetCursor() <= m_itemsPerPage / 2)
        {
          Scroll(-1);
        }
        else if (GetCursor() > 0)
        {
          SetCursor(GetCursor() - 1);
        }
      }
      return handled;
    }
    break;
  case ACTION_SCROLL_DOWN:
    {
      m_analogScrollCount += action.GetAmount() * action.GetAmount();
      bool handled = false;
      while (m_analogScrollCount > 0.4)
      {
        handled = true;
        m_analogScrollCount -= 0.4f;
        if (GetOffset() + m_itemsPerPage < (int)m_items.size() && GetCursor() >= m_itemsPerPage / 2)
        {
          Scroll(1);
        }
        else if (GetCursor() < m_itemsPerPage - 1 && GetOffset() + GetCursor() < (int)m_items.size() - 1)
        {
          SetCursor(GetCursor() + 1);
        }
      }
      return handled;
    }
    break;
  }
  return CGUIBaseContainer::OnAction(action);
}