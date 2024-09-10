    NearWaypoint(const Waypoint &_waypoint, const GeoPoint& _location,
		 const NearWaypoint& previous):
      waypoint(_waypoint), location(_location) {
      range = location.Distance(waypoint.location);
      update_leg(previous);
    }