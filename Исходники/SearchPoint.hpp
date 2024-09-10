 /**
  * Calculate flat earth distance between two points
  *
  * @param sp Point to measure distance from
  *
  * @return Distance in projected units
  */
 gcc_pure
 unsigned FlatDistanceTo(const SearchPoint &sp) const {
   return flat_location.Distance(sp.flat_location);
 }