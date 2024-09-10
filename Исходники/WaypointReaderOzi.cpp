bool
WaypointReaderOzi::ParseLine(const TCHAR *line, Waypoints &way_points)
{
  if (line[0] == '\0')
    return true;

  // Ignore first four header lines
  if (ignore_lines > 0) {
    --ignore_lines;
    return true;
  }

  TCHAR ctemp[255];
  const TCHAR *params[20];
  static constexpr unsigned int max_params = ARRAY_SIZE(params);
  size_t n_params;

  if (_tcslen(line) >= ARRAY_SIZE(ctemp))
    /* line too long for buffer */
    return false;

  // Get fields
  n_params = ExtractParameters(line, ctemp, params, max_params, true, _T('"'));

  // Check if the basic fields are provided
  if (n_params < 15)
    return false;

  GeoPoint location;
  // Latitude (e.g. 5115.900N)
  if (!ParseAngle(params[2], location.latitude))
    return false;

  // Longitude (e.g. 00715.900W)
  if (!ParseAngle(params[3], location.longitude))
    return false;

  location.Normalize(); // ensure longitude is within -180:180

  Waypoint new_waypoint = factory.Create(location);

  long value;
  new_waypoint.original_id = (ParseNumber(params[0], value) ? value : 0);

  if (!ParseString(params[1], new_waypoint.name))
    return false;

  if (ParseNumber(params[14], value) && value != -777)
    new_waypoint.elevation = Units::ToSysUnit(value, Unit::FEET);
  else if (!factory.FallbackElevation(new_waypoint))
    return false;

  // Description (Characters 35-44)
  ParseString(params[11], new_waypoint.comment);

  way_points.Append(std::move(new_waypoint));
  return true;
}