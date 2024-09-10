Vector2F GEORasterProjection::project(const Geodetic2D* position) const {
  const Vector2D uvCoordinates = _sector.getUVCoordinates(*position);

  double v;
  if (_mercator) {
    const double linearV = uvCoordinates._y;
    const Angle latitude = _sector.getInnerPointLatitude(linearV);
    const double mercatorGlobalV = MercatorUtils::getMercatorV(latitude);
    const double mercatorLocalV  = (mercatorGlobalV - _mercatorUpperGlobalV) / _mercatorDeltaGlobalV;
    v = mercatorLocalV;
  }
  else {
    v = uvCoordinates._y;
  }

  return Vector2F((float) (uvCoordinates._x * _imageWidth),
                  (float) (v * _imageHeight));
  
}