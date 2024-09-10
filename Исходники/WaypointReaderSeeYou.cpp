bool
WaypointReaderSeeYou::ParseLine(const TCHAR* line, const unsigned linenum,
                              Waypoints &waypoints)
{
  TCHAR ctemp[4096];
  const TCHAR *params[20];
  static const unsigned int max_params = ARRAY_SIZE(params);
  size_t n_params;

  const unsigned iName = 0;
  const unsigned iLatitude = 3, iLongitude = 4, iElevation = 5;
  const unsigned iStyle = 6, iRWDir = 7, iRWLen = 8;
  const unsigned iFrequency = 9, iDescription = 10;

  static bool ignore_following;
  if (linenum == 0)
    ignore_following = false;

  // If (end-of-file or comment)
  if (line[0] == '\0' || line[0] == 0x1a ||
      _tcsstr(line, _T("**")) == line ||
      _tcsstr(line, _T("*")) == line)
    // -> return without error condition
    return true;

  if (_tcslen(line) >= ARRAY_SIZE(ctemp))
    /* line too long for buffer */
    return false;

  // Skip first line if it doesn't begin with a quotation character
  // (usually the field order line)
  if (linenum == 0 && line[0] != _T('\"'))
    return true;

  // If task marker is reached ignore all following lines
  if (_tcsstr(line, _T("-----Related Tasks-----")) == line)
    ignore_following = true;
  if (ignore_following)
    return true;

  // Get fields
  n_params = ExtractParameters(line, ctemp, params, max_params, true, _T('"'));

  // Check if the basic fields are provided
  if (iName >= n_params)
    return false;
  if (iLatitude >= n_params)
    return false;
  if (iLongitude >= n_params)
    return false;

  GeoPoint location;

  // Latitude (e.g. 5115.900N)
  if (!ParseAngle(params[iLatitude], location.latitude, true))
    return false;

  // Longitude (e.g. 00715.900W)
  if (!ParseAngle(params[iLongitude], location.longitude, false))
    return false;

  location.Normalize(); // ensure longitude is within -180:180

  Waypoint new_waypoint(location);
  new_waypoint.file_num = file_num;
  new_waypoint.original_id = 0;

  // Name (e.g. "Some Turnpoint")
  if (*params[iName] == _T('\0'))
    return false;
  new_waypoint.name = params[iName];

  // Elevation (e.g. 458.0m)
  /// @todo configurable behaviour
  if ((iElevation >= n_params ||
      !ParseAltitude(params[iElevation], new_waypoint.elevation)) &&
      !CheckAltitude(new_waypoint))
    return false;

  // Style (e.g. 5)
  /// @todo include peaks with peak symbols etc.
  if (iStyle < n_params)
    ParseStyle(params[iStyle], new_waypoint);

  // Frequency & runway direction/length (for airports and landables)
  // and description (e.g. "Some Description")
  if (new_waypoint.IsLandable()) {
    if (iFrequency < n_params)
      new_waypoint.radio_frequency = RadioFrequency::Parse(params[iFrequency]);

    // Runway length (e.g. 546.0m)
    fixed rwlen = fixed_minus_one;
    if (iRWLen < n_params && ParseDistance(params[iRWLen], rwlen) &&
        positive(rwlen))
      new_waypoint.runway.SetLength(uround(rwlen));

    if (iRWDir < n_params && *params[iRWDir]) {
      TCHAR *end;
      int direction =_tcstol(params[iRWDir], &end, 10);
      if (end == params[iRWDir] || direction < 0 || direction > 360 ||
          (direction == 0 && !positive(rwlen)))
        direction = -1;
      else if (direction == 360)
        direction = 0;
      if (direction >= 0)
        new_waypoint.runway.SetDirectionDegrees(direction);
    }
  }

  if (iDescription < n_params)
    new_waypoint.comment = params[iDescription];

  waypoints.Append(new_waypoint);
  return true;
}