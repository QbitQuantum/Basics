void CGUIBaseContainer::Render()
{
  if (!m_layout || !m_focusedLayout) return;

  int offset = (int)floorf(m_scroller.GetValue() / m_layout->Size(m_orientation));

  int cacheBefore, cacheAfter;
  GetCacheOffsets(cacheBefore, cacheAfter);

  if (g_graphicsContext.SetClipRegion(m_posX, m_posY, m_width, m_height))
  {
    CPoint origin = CPoint(m_posX, m_posY) + m_renderOffset;
    float pos = (m_orientation == VERTICAL) ? origin.y : origin.x;
    float end = (m_orientation == VERTICAL) ? m_posY + m_height : m_posX + m_width;

    // we offset our draw position to take into account scrolling and whether or not our focused
    // item is offscreen "above" the list.
    float drawOffset = (offset - cacheBefore) * m_layout->Size(m_orientation) - m_scroller.GetValue();
    if (GetOffset() + GetCursor() < offset)
      drawOffset += m_focusedLayout->Size(m_orientation) - m_layout->Size(m_orientation);
    pos += drawOffset;
    end += cacheAfter * m_layout->Size(m_orientation);

    float focusedPos = 0;
    CGUIListItemPtr focusedItem;
    int current = offset - cacheBefore;
    while (pos < end && m_items.size())
    {
      int itemNo = CorrectOffset(current, 0);
      if (itemNo >= (int)m_items.size())
        break;
      bool focused = (current == GetOffset() + GetCursor());
      if (itemNo >= 0)
      {
        CGUIListItemPtr item = m_items[itemNo];
        // render our item
        if (focused)
        {
          focusedPos = pos;
          focusedItem = item;
        }
        else
        {
          if (m_orientation == VERTICAL)
            RenderItem(origin.x, pos, item.get(), false);
          else
            RenderItem(pos, origin.y, item.get(), false);
        }
      }
      // increment our position
      pos += focused ? m_focusedLayout->Size(m_orientation) : m_layout->Size(m_orientation);
      current++;
    }
    // render focused item last so it can overlap other items
    if (focusedItem)
    {
      if (m_orientation == VERTICAL)
        RenderItem(origin.x, focusedPos, focusedItem.get(), true);
      else
        RenderItem(focusedPos, origin.y, focusedItem.get(), true);
    }

    g_graphicsContext.RestoreClipRegion();
  }

  CGUIControl::Render();
}