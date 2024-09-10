float
DistanceDegrees( CalQuaternion const & p1, CalQuaternion const & p2 )
{

  // To determine the angular distance between the oris, multiply one by the inverse
  // of the other, which should leave us with an identity ori if they are equal.  If
  // they are not equal, then the angular magnitude of the rotation in degrees is the
  // difference between the oris.
  CalQuaternion odist = p1;
  odist.invert();
  odist *= p2;
  float w = odist.w;
  if( w > 1 ) w = 1;
  if( w < -1 ) w = -1;
  float distrads = 2 * acos( w ); // Non-negative.
  float distdegrees = distrads * 180.0f / 3.141592654f; // Non-negative.
  if( distdegrees > 180.0 ) distdegrees -= 360.0;
  return fabsf( distdegrees );
}