void
ButtonWindow::on_paint(Canvas &canvas)
{
  canvas.draw_button(get_client_rect(), down);

  canvas.select(font);
  SIZE size = canvas.text_size(text);
  canvas.text((get_width() - size.cx) / 2 + down,
              (get_height() - size.cy) / 2 + down, text);
}