bool
PathSkia::ContainsPoint(const Point &aPoint, const Matrix &aTransform) const
{
  Matrix inverse = aTransform;
  inverse.Invert();
  Point transformed = inverse * aPoint;

  Rect bounds = GetBounds(aTransform);

  if (aPoint.x < bounds.x || aPoint.y < bounds.y ||
      aPoint.x > bounds.XMost() || aPoint.y > bounds.YMost()) {
    return false;
  }

  SkRegion pointRect;
  pointRect.setRect(SkFloatToScalar(transformed.x - 1), SkFloatToScalar(transformed.y - 1), 
                    SkFloatToScalar(transformed.x + 1), SkFloatToScalar(transformed.y + 1));

  SkRegion pathRegion;
  
  return pathRegion.setPath(mPath, pointRect);
}