 /**
  * Set the GeoPoint that relates to the ScreenOrigin
  * @param g The new GeoPoint
  */
 void SetGeoLocation(GeoPoint g) {
   geo_location = g;
   geo_location.Normalize();
 }