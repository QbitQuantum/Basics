//--------------------------------------------------------------
// create named color pen
const mgPen* mgGenSurface::createPen(
  double thick,
  const char* colorSpec)
{
  return createPen(thick, mgColor(colorSpec));
}