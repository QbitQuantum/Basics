    m2::RectF const BaseTexture::mapRect(m2::RectF const & r) const
    {
      m2::PointF pt1(r.minX(), r.minY());
      m2::PointF pt2(r.maxX(), r.maxY());

      pt1 = mapPixel(pt1);
      pt2 = mapPixel(pt2);

      return m2::RectF(pt1.x, pt1.y, pt2.x, pt2.y);
    }