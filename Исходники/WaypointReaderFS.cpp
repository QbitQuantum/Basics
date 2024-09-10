static bool
ParseLocation(const TCHAR *src, GeoPoint &p)
{
  Angle lon, lat;

  if (!ParseAngle(src, lat))
    return false;

  if (!ParseAngle(src + 17, lon))
    return false;

  p.longitude = lon;
  p.latitude = lat;

  // ensure longitude is within -180:180
  p.Normalize();

  return true;
}