void
MenuManager::transition(Menu* from, Menu* to)
{
  if (!from && !to)
  {
    return;
  }
  else
  {
    Rectf from_rect;
    if (from)
    {
      from_rect = menu2rect(*from);
    }
    else
    {
      from_rect = Rectf(to->get_center_pos(), Sizef(0, 0));
    }

    Rectf to_rect;
    if (to)
    {
      to_rect = menu2rect(*to);
    }
    else
    {
      to_rect = Rectf(from->get_center_pos(), Sizef(0, 0));
    }

    m_transition->start(from_rect, to_rect);
  }
}