void
TopographyFileRenderer::PaintLabels(Canvas &canvas,
                                    const WindowProjection &projection,
                                    LabelBlock &label_block)
{
  if (file.IsEmpty())
    return;

  fixed map_scale = projection.GetMapScale();
  if (!file.IsVisible(map_scale) || !file.IsLabelVisible(map_scale))
    return;

  UpdateVisibleShapes(projection);

  if (visible_labels.empty())
    return;

  // TODO code: only draw inside screen!
  // this will save time with rendering pixmaps especially
  // we already do an outer visibility test, but may need a test
  // in screen coords

  canvas.Select(file.IsLabelImportant(map_scale) ?
                Fonts::map_label_important : Fonts::map_label);
  canvas.SetTextColor(Color(0x20, 0x20, 0x20));
  canvas.SetBackgroundTransparent();

  // get drawing info

  int iskip = file.GetSkipSteps(map_scale);

#ifdef ENABLE_OPENGL
  Matrix2D m1;
  m1.Translate(projection.GetScreenOrigin());
  m1.Rotate(projection.GetScreenAngle());
  m1.Scale(projection.GetScale());
#endif

  // Iterate over all shapes in the file
  for (auto it = visible_labels.begin(), end = visible_labels.end();
       it != end; ++it) {
    const XShape &shape = **it;

    if (!projection.GetScreenBounds().Overlaps(shape.get_bounds()))
      continue;

    // Skip shapes without a label
    const TCHAR *label = shape.get_label();
    if (label == NULL)
      continue;

    const unsigned short *lines = shape.get_lines();
    const unsigned short *end_lines = lines + shape.get_number_of_lines();
#ifdef ENABLE_OPENGL
    const ShapePoint *points = shape.get_points();

    Matrix2D m2(m1);
    m2.Translatex(shape.shape_translation(projection.GetGeoLocation()));
#else
    const GeoPoint *points = shape.get_points();
#endif

    for (; lines < end_lines; ++lines) {
      int minx = canvas.get_width();
      int miny = canvas.get_height();

#ifdef ENABLE_OPENGL
      const ShapePoint *end = points + *lines;
#else
      const GeoPoint *end = points + *lines;
#endif
      for (; points < end; points += iskip) {
#ifdef ENABLE_OPENGL
        RasterPoint pt = m2.Apply(*points);
#else
        RasterPoint pt = projection.GeoToScreen(*points);
#endif

        if (pt.x <= minx) {
          minx = pt.x;
          miny = pt.y;
        }
      }

      points = end;

      minx += 2;
      miny += 2;

      PixelSize tsize = canvas.CalcTextSize(label);
      PixelRect brect;
      brect.left = minx;
      brect.right = brect.left + tsize.cx;
      brect.top = miny;
      brect.bottom = brect.top + tsize.cy;

      if (!label_block.check(brect))
        continue;

      canvas.text(minx, miny, label);
    }
  }
}