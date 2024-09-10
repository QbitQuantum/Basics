void
TimerBox::update_time_bars(TransparentDamageControl &ctrl)
{
  TRACE_ENTER("TimerBox::update_time_bars");
  if (enabled)
    {
      int x = 0, y = 0;
      int bar_w, bar_h;
      int icon_width, icon_height;

      TRACE_MSG("1");
      slot_to_time_bar[0]->get_size(bar_w, bar_h);
      break_to_icon[0]->get_size(icon_width, icon_height);
      TRACE_MSG("2");
      int icon_bar_w = icon_width + 2 * PADDING_X + bar_w;
      int max_columns = __max(1, width / icon_bar_w);
      int max_rows = __max(1, (height + PADDING_Y) / (__max(icon_height, bar_h) + PADDING_Y));
      int rows = __max(1, __min(max_rows, (filled_slots + max_columns - 1) / max_columns));
      int columns = (filled_slots + rows -1) / rows;
      TRACE_MSG("3");
      
      int box_h = rows * __max(icon_height, bar_h) + (rows - 1) * PADDING_Y;
      y = __max(0, (height - box_h)/2);

      int icon_dy = 0;
      int bar_dy = 0;

      TRACE_MSG("4");
      if (bar_h > icon_height)
        {
          icon_dy = (bar_h - icon_height + 1) / 2;
        }
      else
        {
          bar_dy = (icon_height - bar_h + 1) / 2;
        }
         
      TRACE_MSG("5");
       
      int current_column = 0;
      for (int i = 0; i < BREAK_ID_SIZEOF; i++)
        {
          BreakId bid = slot_to_break[i];
          TRACE_MSG("6");

          if (bid != BREAK_ID_NONE)
            {
              TRACE_MSG("7");
              TimeBar *bar = get_time_bar(bid);

              ctrl.ShowWindow(break_to_icon[bid]->get_handle(), x, y + icon_dy);
              ctrl.ShowWindow(bar->get_handle(), x+icon_width+PADDING_X, y + bar_dy);
              bar->update();
              x += icon_bar_w + 2 * PADDING_X;
              current_column++;
              if (current_column >= columns)
                {
                  current_column = 0;
                  x = 0;
                  y += __max(icon_height, bar_h) + PADDING_Y;
                }
            }
        }
    }
  
  TRACE_MSG("8");
  for (int h = 0; h < BREAK_ID_SIZEOF; h++)
    {
      if ((! enabled) || (! break_visible[h]))
        {
          ctrl.HideWindow(break_to_icon[h]->get_handle());
        }
    }
  TRACE_MSG("9");
  for (int j = enabled ? filled_slots : 0; j < BREAK_ID_SIZEOF; j++)
    {
      ctrl.HideWindow(slot_to_time_bar[j]->get_handle());
    }
  TRACE_EXIT();
}