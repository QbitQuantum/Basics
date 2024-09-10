 /**
  * @return \e a1 the arc length (degrees) between the northward equatorial
  *   crossing and point 1.
  *
  * The result lies in (&minus;180&deg;, 180&deg;].
  **********************************************************************/
 Math::real EquatorialArc() const {
   using std::atan2;
   return Init() ? atan2(_ssig1, _csig1) / Math::degree() : Math::NaN();
 }