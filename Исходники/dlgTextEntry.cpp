static void
OnTextPaint(gcc_unused WndOwnerDrawFrame *Sender, Canvas &canvas)
{
  const PixelRect rc = Sender->get_client_rect();

  canvas.clear(Color(0x40, 0x40, 0x00));

  // Do the actual painting of the text
  canvas.select(Fonts::Map);

  PixelSize tsize = canvas.text_size(edittext);
  PixelSize tsizec = canvas.text_size(edittext, cursor);
  PixelSize tsizea = canvas.text_size(edittext, cursor + 1);

  RasterPoint p[5];
  p[0].x = 10;
  p[0].y = (rc.bottom - rc.top - tsize.cy - 5) / 2;

  p[2].x = p[0].x + tsizec.cx;
  p[2].y = p[0].y + tsize.cy + 5;

  p[3].x = p[0].x + tsizea.cx;
  p[3].y = p[0].y + tsize.cy + 5;

  p[1].x = p[2].x;
  p[1].y = p[2].y - 2;

  p[4].x = p[3].x;
  p[4].y = p[3].y - 2;

  canvas.white_pen();
  canvas.polyline(p + 1, 4);

  canvas.background_transparent();
  canvas.set_text_color(COLOR_WHITE);
  canvas.text(p[0].x, p[0].y, edittext);
}