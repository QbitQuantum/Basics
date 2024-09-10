 /**
  * The latitude resolution of a geohash.
  *
  * @param[in] len the length of the geohash.
  * @return the latitude resolution (degrees).
  *
  * Internally, \e len is first put in the range [0, 18].
  **********************************************************************/
 static Math::real LatitudeResolution(int len) {
   using std::ldexp;
   len = (std::max)(0, (std::min)(int(maxlen_), len));
   return ldexp(real(180), -(5 * len / 2));
 }