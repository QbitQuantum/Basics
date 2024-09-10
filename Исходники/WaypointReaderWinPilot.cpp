bool
WaypointReaderWinPilot::ParseLine(const TCHAR *line, Waypoints &waypoints)
{
  TCHAR ctemp[4096];
  const TCHAR *params[20];
  static constexpr unsigned int max_params = ARRAY_SIZE(params);
  size_t n_params;

  // If (end-of-file)
  if (line[0] == '\0')
    // -> return without error condition
    return true;

  // If comment
  if (line[0] == _T('*')) {
    if (first) {
      first = false;
      welt2000_format = (_tcsstr(line, _T("WRITTEN BY WELT2000")) != nullptr);
    }

    // -> return without error condition
    return true;
  }

  if (_tcslen(line) >= ARRAY_SIZE(ctemp))
    /* line too long for buffer */
    return false;

  GeoPoint location;

  // Get fields
  n_params = ExtractParameters(line, ctemp, params, max_params, true);
  if (n_params < 6)
    return false;

  // Latitude (e.g. 51:15.900N)
  if (!ParseAngle(params[1], location.latitude, true))
    return false;

  // Longitude (e.g. 00715.900W)
  if (!ParseAngle(params[2], location.longitude, false))
    return false;
  location.Normalize(); // ensure longitude is within -180:180

  Waypoint new_waypoint = factory.Create(location);

  // Name (e.g. KAMPLI)
  if (*params[5] == _T('\0'))
    return false;
  new_waypoint.name=params[5];

  // Altitude (e.g. 458M)
  /// @todo configurable behaviour
  if (!ParseAltitude(params[3], new_waypoint.elevation) &&
      !factory.FallbackElevation(new_waypoint))
    return false;

  if (n_params > 6) {
    // Description (e.g. 119.750 Airport)
    new_waypoint.comment=params[6];
    if (welt2000_format)
      ParseRunwayDirection(params[6], new_waypoint.runway);
  }

  // Waypoint Flags (e.g. AT)
  ParseFlags(params[4], new_waypoint);

  waypoints.Append(std::move(new_waypoint));
  return true;
}