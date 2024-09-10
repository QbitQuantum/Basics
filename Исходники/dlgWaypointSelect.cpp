void
dlgWaypointSelectAddToLastUsed(const Waypoint &waypoint)
{
  last_used_waypoint_ids.remove(waypoint.id);
  last_used_waypoint_ids.push_back(waypoint.id);
}