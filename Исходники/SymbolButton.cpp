void
WndSymbolButton::on_paint(Canvas &canvas)
{
  /* background and selector */
  canvas.clear(background_brush);

  // Get button RECT and shrink it to make room for the selector/focus
  RECT rc = get_client_rect();

  // Draw button to the background
  canvas.draw_button(rc, is_down());

  // Draw focus rectangle
  if (has_focus()) {
    RECT focus_rc = rc;
    InflateRect(&focus_rc, -3, -3);
    canvas.draw_focus(focus_rc);
  }

  // If button has text on it
  tstring caption = get_text();
  if (caption.empty())
    return;

  // If button is pressed, offset the text for 3D effect
  if (is_down())
    OffsetRect(&rc, 1, 1);

  canvas.null_pen();
  canvas.black_brush();

  const char ch = (char)caption[0];

  // Draw arrow symbols instead of < and >
  if (ch == '<' || ch == '>') {
    int size = min(rc.right - rc.left, rc.bottom - rc.top) / 5;

    static RasterPoint Arrow[4];
    Arrow[0].x = (rc.left + rc.right) / 2 + (ch == '<' ? size : -size);
    Arrow[0].y = (rc.top + rc.bottom) / 2 + size;
    Arrow[1].x = (rc.left + rc.right) / 2 + (ch == '<' ? -size : size);
    Arrow[1].y = (rc.top + rc.bottom) / 2;
    Arrow[2].x = (rc.left + rc.right) / 2 + (ch == '<' ? size : -size);
    Arrow[2].y = (rc.top + rc.bottom) / 2 - size;
    Arrow[3].x = Arrow[0].x;
    Arrow[3].y = Arrow[0].y;

    canvas.polygon(Arrow, 4);
  }

  // Draw arrow symbols instead of v and ^
  if (ch == '^' || ch == 'v') {
    int size = min(rc.right - rc.left, rc.bottom - rc.top) / 5;

    RasterPoint Arrow[3];
    Arrow[0].x = (rc.left + rc.right) / 2 +
                 size;
    Arrow[0].y = (rc.top + rc.bottom) / 2 +
                 (ch == '^' ? size : -size);
    Arrow[1].x = (rc.left + rc.right) / 2;
    Arrow[1].y = (rc.top + rc.bottom) / 2 +
                 (ch == '^' ? -size : size);
    Arrow[2].x = (rc.left + rc.right) / 2 - size;
    Arrow[2].y = (rc.top + rc.bottom) / 2 +
                 (ch == '^' ? size : -size);

    canvas.polygon(Arrow, 3);
  }

  // Draw symbols instead of + and -
  if (ch == '+' || ch == '-') {
    int size = min(rc.right - rc.left, rc.bottom - rc.top) / 5;

    canvas.rectangle((rc.left + rc.right) / 2 - size,
                     (rc.top + rc.bottom) / 2 - size / 3,
                     (rc.left + rc.right) / 2 + size,
                     (rc.top + rc.bottom) / 2 + size / 3);

    if (ch == '+')
      canvas.rectangle((rc.left + rc.right) / 2 - size / 3,
                       (rc.top + rc.bottom) / 2 - size,
                       (rc.left + rc.right) / 2 + size / 3,
                       (rc.top + rc.bottom) / 2 + size);
  }

  // Draw Fly bitmap
  if (caption == _T("Fly")) {
    Bitmap launcher1_bitmap(IDB_LAUNCHER1);
    if (is_down())
      canvas.stretch(launcher1_bitmap);
    else {
      canvas.clear_white();
      canvas.stretch_transparent(launcher1_bitmap, Color::BLUE);
    }
  }

  // Draw Simulator bitmap
  if (caption == _T("Simulator")) {
    Bitmap launcher2_bitmap(IDB_LAUNCHER2);
    if (is_down())
      canvas.stretch(launcher2_bitmap);
    else {
      canvas.clear_white();
      canvas.stretch_transparent(launcher2_bitmap, Color::BLUE);
    }
  }

}