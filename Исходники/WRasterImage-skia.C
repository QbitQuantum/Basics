void WRasterImage::Impl::drawPlainPath(SkPath &p, const WPainterPath& path)
{
  const std::vector<WPainterPath::Segment>& segments = path.segments();

  if (segments.size() > 0
      && segments[0].type() != WPainterPath::Segment::MoveTo)
    p.moveTo(SkDoubleToScalar(0), SkDoubleToScalar(0));

  for (unsigned i = 0; i < segments.size(); ++i) {
    const WPainterPath::Segment s = segments[i];

    switch (s.type()) {
    case WPainterPath::Segment::MoveTo:
      p.moveTo(SkDoubleToScalar(s.x()), SkDoubleToScalar(s.y()));
      break;
    case WPainterPath::Segment::LineTo:
      p.lineTo(SkDoubleToScalar(s.x()), SkDoubleToScalar(s.y()));
      break;
    case WPainterPath::Segment::CubicC1: {
      const double x1 = s.x();
      const double y1 = s.y();
      const double x2 = segments[i+1].x();
      const double y2 = segments[i+1].y();
      const double x3 = segments[i+2].x();
      const double y3 = segments[i+2].y();
      p.cubicTo(SkDoubleToScalar(x1), SkDoubleToScalar(y1),
                SkDoubleToScalar(x2), SkDoubleToScalar(y2),
                SkDoubleToScalar(x3), SkDoubleToScalar(y3));
      i += 2;
      break;
    }
    case WPainterPath::Segment::CubicC2:
    case WPainterPath::Segment::CubicEnd:
      assert(false);
    case WPainterPath::Segment::ArcC: {
      const double x = s.x();
      const double y = s.y();
      const double width = segments[i+1].x();
      const double height = segments[i+1].y();
      const double startAngle = segments[i+2].x();
      const double sweepAngle = segments[i+2].y();
      SkRect rect = SkRect::MakeXYWH(SkDoubleToScalar(x - width),
				     SkDoubleToScalar(y - height),
				     SkDoubleToScalar(width * 2.0),
				     SkDoubleToScalar(height * 2.0));
      if (sweepAngle != 360) 
	p.arcTo(rect,
		SkDoubleToScalar(-startAngle), SkDoubleToScalar(-sweepAngle),
		false);
      else
	p.addOval(rect, SkPath::kCCW_Direction);

      i += 2;
      break;
    }
    case WPainterPath::Segment::ArcR:
    case WPainterPath::Segment::ArcAngleSweep:
      assert(false);
    case WPainterPath::Segment::QuadC: {
      const double x1 = s.x();
      const double y1 = s.y();
      const double x2 = segments[i+1].x();
      const double y2 = segments[i+1].y();
      
      p.quadTo(SkDoubleToScalar(x1), SkDoubleToScalar(y1),
              SkDoubleToScalar(x2), SkDoubleToScalar(y2));

      i += 1;

      break;
    }
    case WPainterPath::Segment::QuadEnd:
      assert(false);
    }
  }
}