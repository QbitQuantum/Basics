static bool
ParseLocationUTM(const TCHAR *&src, GeoPoint &p)
{
  // 31T 318570 4657569

  TCHAR *endptr;

  // Parse zone number
  long zone_number = _tcstol(src, &endptr, 10);
  if (endptr == src)
    return false;

  src = endptr;
  char zone_letter = src[0];

  src++;
  long easting = _tcstol(src, &endptr, 10);
  if (endptr == src || *endptr != _T(' '))
    return false;

  src = endptr;
  long northing = _tcstol(src, &endptr, 10);
  if (endptr == src || *endptr != _T(' '))
    return false;

  UTM u(zone_number, zone_letter, fixed(easting), fixed(northing));
  p = u.ToGeoPoint();

  // ensure longitude is within -180:180
  p.Normalize();

  src = endptr;

  return true;
}