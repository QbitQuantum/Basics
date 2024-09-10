void
MapWindow::OnPaint(Canvas &canvas)
{
#ifdef ENABLE_OPENGL
  DoubleBufferWindow::OnPaint(canvas);
#else /* !ENABLE_OPENGL */
  if (buffer_generation == ui_generation)
    DoubleBufferWindow::OnPaint(canvas);
  else if (scale_buffer > 0) {
    /* while zooming/panning, project the current buffer into the
       Canvas */

    --scale_buffer;

    /* do the projection */

    const UPixelScalar buffer_width = buffer_projection.GetScreenWidth();
    const UPixelScalar buffer_height = buffer_projection.GetScreenHeight();

    const RasterPoint top_left =
      visible_projection.GeoToScreen(buffer_projection.ScreenToGeo(0, 0));
    RasterPoint bottom_right =
      visible_projection.GeoToScreen(buffer_projection.ScreenToGeo(buffer_width,
                                                                   buffer_height));

    /* compensate for rounding errors in destination area */

    if (abs(buffer_width - (bottom_right.x - top_left.x)) < 5)
      bottom_right.x = top_left.x + buffer_width;

    if (abs(buffer_height - (bottom_right.y - top_left.y)) < 5)
      bottom_right.y = top_left.y + buffer_height;

    /* clear the areas around the buffer */

    canvas.SelectNullPen();
    canvas.SelectWhiteBrush();

    if (top_left.x > 0)
      canvas.Rectangle(0, 0, top_left.x, canvas.get_height());

    if (bottom_right.x < (int)canvas.get_width())
      canvas.Rectangle(bottom_right.x, 0,
                       canvas.get_width(), canvas.get_height());

    if (top_left.y > 0)
      canvas.Rectangle(top_left.x, 0, bottom_right.x, top_left.y);

    if (bottom_right.y < (int)canvas.get_height())
      canvas.Rectangle(top_left.x, bottom_right.y,
                       bottom_right.x, canvas.get_height());

    /* now stretch the buffer into the window Canvas */

    ScopeLock protect(DoubleBufferWindow::mutex);
    const Canvas &src = get_visible_canvas();
    canvas.stretch(top_left.x, top_left.y,
                   bottom_right.x - top_left.x, bottom_right.y - top_left.y,
                   src, 0, 0, buffer_width, buffer_height);
  } else
    /* the UI has changed since the last DrawThread iteration has
       started: the buffer has invalid data, paint a white window
       instead */
    canvas.ClearWhite();
#endif /* !ENABLE_OPENGL */
}