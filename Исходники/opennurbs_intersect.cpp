bool ON_Intersect( const ON_BoundingBox& bbox, 
                   const ON_Line& line, 
                   double tol,
                   ON_Interval* line_parameters)
{
  double a,b,d,mn,mx,s0,s1, t0, t1;
  const double M = 1.0e308;

  // i,j,k are indices of coordinates to trim.
  // trim the direction with the biggest line deltas first
  ON_3dVector v = line.Direction();
  const int i = v.MaximumCoordinateIndex();

  // gaurd against ON_UNSET_VALUE as input
  if ( !(tol >= 0.0) )
    tol = 0.0;

  // clip i-th coordinate
  a = line.from[i];
  b = line.to[i];
  mn = bbox.m_min[i];
  mx = bbox.m_max[i];
  if ( !(mn <= mx) )
    return false;
  mn -= (tol+a);
  mx += (tol-a);
  if ( !(mn <= mx) )
    return false;
  d = b-a;
  if ( 0.0 == d )
  {
    // happens when line.from == line.to
    if ( 0.0 < mn || 0.0 > mx )
    {
      // point is in box
      if ( line_parameters )
      {
        // setting parameters makes no sense - just use 0.0
        // so it's clear we have a point
        line_parameters->Set(0.0,0.0);
      }
      return true;
    }
    return false; // point is outside box
  }
  if ( fabs(d) < 1.0 && (fabs(mn) >= fabs(d)*M || fabs(mx) >= fabs(d)*M) )
  {
    // the value of mn/d or mx/d is too large for a realistic answer to be computed
    return false;
  }
  d = 1.0/d;
  t0 = mn*d;
  t1 = mx*d;

  // set "chord" = line segment that begins and ends on the
  // i-th coordinate box side planes.
  ON_Line chord(line.PointAt(t0),line.PointAt(t1));

  // test j-th coordinate direction
  const int j = (i + (fabs(v[(i+1)%3])>fabs(v[(i+2)%3])?1:2) ) % 3;
  a = chord.from[j];
  b = chord.to[j];
  mn = bbox.m_min[j];
  mx = bbox.m_max[j];
  if ( !(mn <= mx) )
    return false;
  mn -= (tol+a);
  mx += (tol-a);
  if ( !(mn <= mx) )
    return false;
  d = b-a;
  if ( (0.0 < mn && d < mn) || (0.0 > mx && d > mx) )
  {
    // chord lies outside the box
    return false;
  }

  while ( fabs(d) >= 1.0 || (fabs(mn) <= fabs(d)*M && fabs(mx) <= fabs(d)*M) )
  {
    // The chord is not (nearly) parallel to the j-th sides.
    // See if the chord needs to be trimmed by the j-th sides.
    d = 1.0/d;
    s0 = mn*d;
    s1 = mx*d;
    if ( s0 > 1.0 )
    {
      if ( s1 > 1.0 )
      {
        // unstable calculation happens when
        // fabs(d) is very tiny and chord is
        // on the j-th side.
        break;
      }
      s0 = 1.0;
    }
    else if ( s0 < 0.0 )
    {
      if (s1 < 0.0)
      {
        // unstable calculation happens when
        // fabs(d) is very tiny and chord is
        // on the j-th side.
        break;
      }
      s0 = 0.0;
    }
    if ( s1 < 0.0 ) s1 = 0.0; else if ( s1 > 1.0 ) s1 = 1.0;
    d = (1.0-s0)*t0 + s0*t1;
    t1 = (1.0-s1)*t0 + s1*t1;
    t0 = d;
    v = chord.PointAt(s0);
    chord.to = chord.PointAt(s1);
    chord.from = v;
    break;
  }
  
  // test k-th coordinate direction
  const int k = (i&&j) ? 0 : ((i!=1&&j!=1)?1:2);
  a = chord.from[k];
  b = chord.to[k];
  mn = bbox.m_min[k];
  mx = bbox.m_max[k];
  if ( !(mn <= mx) )
    return false;
  mn -= (tol+a);
  mx += (tol-a);
  if ( !(mn <= mx) )
    return false;
  d = b-a;
  if ( (0.0 < mn && d < mn) || (0.0 > mx && d > mx) )
  {
    // chord does not intersect the rectangle
    return false;
  }

  if ( line_parameters )
  {

    while ( fabs(d) >= 1.0 || (fabs(mn) <= fabs(d)*M && fabs(mx) <= fabs(d)*M) )
    {
      // The chord is not (nearly) parallel to the k-th sides.
      // See if the chord needs to be trimmed by the k-th sides.
      d = 1.0/d;
      s0 = mn*d;
      s1 = mx*d;
      if ( s0 > 1.0 )
      {
        if ( s1 > 1.0 )
        {
          // unstable calculation happens when
          // fabs(d) is very tiny and chord is
          // on the k-th side.
          break;
        }
        s0 = 1.0;
      }
      else if ( s0 < 0.0 )
      {
        if (s1 < 0.0)
        {
          // unstable calculation happens when
          // fabs(d) is very tiny and chord is
          // on the k-th side.
          break;
        }
        s0 = 0.0;
      }

      if ( s1 < 0.0 ) s1 = 0.0; else if ( s1 > 1.0 ) s1 = 1.0;
      d = (1.0-s0)*t0 + s0*t1;
      t1 = (1.0-s1)*t0 + s1*t1;
      t0 = d;
      break;
    }

    if (t0 > t1 )
    {
      line_parameters->Set(t1,t0);
    }
    else
    {
      line_parameters->Set(t0,t1);
    }
  }

  return true;
}