static bool
ReadCoords(const TCHAR *buffer, GeoPoint &point)
{
  // Format: 53:20:41 N 010:24:41 E
  // Alternative Format: 53:20.68 N 010:24.68 E

  TCHAR *endptr;

  // ToDo, add more error checking and making it more tolerant/robust

  double deg = ParseDouble(buffer, &endptr);
  if ((buffer == endptr) || (*endptr == '\0'))
    return false;

  if (*endptr == ':') {
    endptr++;

    double min = ParseDouble(endptr, &endptr);
    if (*endptr == '\0')
      return false;

    deg += min / 60;

    if (*endptr == ':') {
      endptr++;

      double sec = ParseDouble(endptr, &endptr);
      if (*endptr == '\0')
        return false;

      deg += sec / 3600;
    }
  }

  point.latitude = Angle::Degrees(deg);

  if (*endptr == ' ')
    endptr++;

  if (*endptr == '\0')
    return false;

  if ((*endptr == 'S') || (*endptr == 's'))
    point.latitude.Flip();

  endptr++;
  if (*endptr == '\0')
    return false;

  deg = ParseDouble(endptr, &endptr);
  if ((buffer == endptr) || (*endptr == '\0'))
    return false;

  if (*endptr == ':') {
    endptr++;

    double min = ParseDouble(endptr, &endptr);
    if (*endptr == '\0')
      return false;

    deg += min / 60;

    if (*endptr == ':') {
      endptr++;

      double sec = ParseDouble(endptr, &endptr);
      if (*endptr == '\0')
        return false;

      deg += sec / 3600;
    }
  }

  point.longitude = Angle::Degrees(deg);

  if (*endptr == ' ')
    endptr++;

  if (*endptr == '\0')
    return false;

  if ((*endptr == 'W') || (*endptr == 'w'))
    point.longitude.Flip();

  point.Normalize(); // ensure longitude is within -180:180
  return true;
}