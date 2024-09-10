void
TabDisplay::OnPaint(Canvas &canvas)
{
  canvas.Clear(COLOR_BLACK);
  canvas.Select(*look.button.font);

  const unsigned CaptionStyle = DT_CENTER | DT_NOCLIP
      | DT_WORDBREAK;

  const bool is_focused = !HasCursorKeys() || HasFocus();
  for (unsigned i = 0; i < buttons.size(); i++) {
    const TabButton &button = *buttons[i];

    const bool is_down = dragging && i == down_index && !drag_off_button;
    const bool is_selected = i == tab_bar.GetCurrentPage();

    canvas.SetTextColor(look.list.GetTextColor(is_selected, is_focused,
                                               is_down));
    canvas.SetBackgroundColor(look.list.GetBackgroundColor(is_selected,
                                                           is_focused,
                                                           is_down));

    const PixelRect &rc = GetButtonSize(i);
    PaintButton(canvas, CaptionStyle, button.caption, rc, button.bitmap,
                is_down, is_selected);
  }
}