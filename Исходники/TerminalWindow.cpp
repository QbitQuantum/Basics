void
TerminalWindow::OnPaint(Canvas &canvas, const PixelRect &p_dirty)
{
  canvas.SetBackgroundTransparent();
  canvas.SetTextColor(look.text_color);
  canvas.Select(look.font);

  const PixelRect cell_dirty = {
    p_dirty.left / cell_size.cx,
    p_dirty.top / cell_size.cy,
    std::min(PixelScalar(p_dirty.right / cell_size.cx + 1),
             PixelScalar(data.GetWidth())),
    std::min(PixelScalar(p_dirty.bottom / cell_size.cy + 1),
             PixelScalar(data.GetHeight())),
  };

  const PixelScalar x(cell_dirty.left * cell_size.cx);
  const size_t length = cell_dirty.right - cell_dirty.left;

  auto text = data.GetPointerAt(cell_dirty.left, cell_dirty.top);
  for (int cell_y = cell_dirty.top, p_y = cell_y * cell_size.cy;
       cell_y < cell_dirty.bottom;
       ++cell_y, p_y += cell_size.cy, text += data.GetWidth()) {
    canvas.DrawFilledRectangle(p_dirty.left, p_y,
                          p_dirty.right, p_y + cell_size.cy,
                          look.background_color);
    canvas.DrawText(x, p_y, text, length);
  }

  PixelScalar cell_bottom_y(cell_dirty.bottom * cell_size.cy);
  if (cell_bottom_y < p_dirty.bottom)
    canvas.DrawFilledRectangle(p_dirty.left, cell_bottom_y,
                          p_dirty.right, p_dirty.bottom,
                          look.background_color);
}