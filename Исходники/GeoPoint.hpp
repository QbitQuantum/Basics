 /**
  * Subtracts a delta from a point
  *
  * @param delta Delta to subtract
  *
  * @return Modified point
  */
 gcc_pure
 GeoPoint operator- (const GeoPoint &delta) const {
     GeoPoint res = *this;
     res.longitude -= delta.longitude;
     res.latitude -= delta.latitude;
     return res.Normalize();
 };