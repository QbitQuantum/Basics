void anchor_handle_renderer::draw_anchor (SkCanvas &canvas, const SkRect &rect, SkPaint &paint) const
{
  switch (m_node_type)
  {
    case handle_type::DIAMOND:
    {
      canvas.save ();
      canvas.translate (rect.centerX (), rect.centerY ());
      canvas.rotate (45);
      SkRect moved_rect = rect;
      moved_rect.offset (-rect.centerX (), -rect.centerY ());
      paint.setAntiAlias (true);
      canvas.drawRect (moved_rect, paint);
      canvas.restore ();
      break;
    }
    case handle_type::SQUARE:
      canvas.drawRect (rect, paint);
      break;
    case handle_type::CIRCLE:
      canvas.drawOval (rect, paint);
      break;
    case handle_type::DOUBLE_HEADED_ARROW:
    case handle_type::ROTATE_ARROW:
      SkPath path = qt2skia::path (*m_paths.at (m_node_type));
      SkMatrix trans;
      trans.setIdentity ();
      trans.postRotate (m_rotation_angle, 32, 32); // TODO: change all these to use info from path_storage (bounding box and center (possibly should be made 0))
      trans.postConcat (qt2skia::matrix (geom::rect2rect (QRectF (0, 0, 64, 64), qt2skia::rect (rect))));
      path.transform (trans);
      paint.setAntiAlias (true);
      canvas.drawPath (path, paint);
      break;
  }
}