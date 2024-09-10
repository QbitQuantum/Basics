bool
WaypointReaderZander::ParseLine(const TCHAR* line, const unsigned linenum,
                              Waypoints &way_points)
{
  // If (end-of-file or comment)
  if (line[0] == '\0' || line[0] == 0x1a ||
      _tcsstr(line, _T("**")) == line ||
      _tcsstr(line, _T("*")) == line)
    // -> return without error condition
    return true;

  // Determine the length of the line
  size_t len = _tcslen(line);
  // If less then 34 characters -> something is wrong -> cancel
  if (len < 34)
    return false;

  GeoPoint location;

  // Latitude (Characters 13-20 // DDMMSS(N/S))
  if (!ParseAngle(line + 13, location.latitude, true))
    return false;

  // Longitude (Characters 21-29 // DDDMMSS(E/W))
  if (!ParseAngle(line + 21, location.longitude, false))
    return false;

  location.Normalize(); // ensure longitude is within -180:180

  Waypoint new_waypoint(location);
  new_waypoint.file_num = file_num;
  new_waypoint.original_id = 0;

  // Name (Characters 0-12)
  if (!ParseString(line, new_waypoint.name, 12))
    return false;

  // Altitude (Characters 30-34 // e.g. 1561 (in meters))
  /// @todo configurable behaviour
  if (!ParseAltitude(line + 30, new_waypoint.elevation) &&
      !CheckAltitude(new_waypoint))
    return false;

  // Description (Characters 35-44)
  if (len > 35)
    ParseString(line + 35, new_waypoint.comment, 9);

  // Flags (Characters 45-49)
  if (len < 46 || !ParseFlags(line + 45, new_waypoint))
    if (len < 36 || !ParseFlagsFromDescription(line + 35, new_waypoint))
      new_waypoint.flags.turn_point = true;

  way_points.Append(new_waypoint);
  return true;
}