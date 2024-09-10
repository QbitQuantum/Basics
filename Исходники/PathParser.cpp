void
PathParser::line_to(const Edge& curve)
{
  if (curve.straight()) {
    lineTo(curve.ap);
  } else {
    curveTo(curve);
  }
}