Point2 Exact_adaptive_kernel::offcenter( Point2 const& a, Point2 const& b, Point2 const& c, double offconstant )
{
  Point2 ba = b - a;
  Point2 ca = c - a;
  Point2 bc = b - c;
  double abdist = distance_squared( a, b );
  double acdist = distance_squared( a, c );
  double bcdist = distance_squared( b, c );
  double denominator = 0.25 / signed_area( b, c, a );
  BOOST_ASSERT( denominator > 0.0 );
  double dx = ( ca(1) * abdist - ba(1) * acdist ) * denominator;
  double dy = ( ba(0) * acdist - ca(0) * abdist ) * denominator;
  double dxoff, dyoff;

  if ( ( abdist < acdist ) && ( abdist < bcdist ) )
  {
    dxoff = 0.5 * ba(0) - offconstant * ba(1);
    dyoff = 0.5 * ba(1) + offconstant * ba(0);

    if ( dxoff * dxoff + dyoff * dyoff < dx * dx + dy * dy )
    {
      dx = dxoff;
      dy = dyoff;
    }
  }
  else if ( acdist < bcdist )
  {
    dxoff = 0.5 * ca(0) + offconstant * ca(1);
    dyoff = 0.5 * ca(1) - offconstant * ca(0);

    if ( dxoff * dxoff + dyoff * dyoff < dx * dx + dy * dy )
    {
      dx = dxoff;
      dy = dyoff;
    }
  }
  else
  {
    dxoff = 0.5 * bc(0) - offconstant * bc(1);
    dyoff = 0.5 * bc(1) + offconstant * bc(0);

    if ( dxoff * dxoff + dyoff * dyoff < ( dx - ba(0) ) * ( dx - ba(0) ) + ( dy - ba(1) ) * ( dy - ba(1) ) )
    {
      dx = ba(0) + dxoff;
      dy = ba(1) + dyoff;
    }
  }

  return Point2( a(0) + dx, a(1) + dy );
}