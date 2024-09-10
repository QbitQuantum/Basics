 bool operator()(const Waypoint &waypoint) {
   return location.Distance(waypoint.location) < distance;
 }