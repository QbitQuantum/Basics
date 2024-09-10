void
AATPoint::get_target_range_radial(fixed &range, fixed &radial) const
{
  const fixed oldrange = range;

  const GeoPoint fprev = get_previous()->get_location_remaining();
  const GeoPoint floc = get_location();
  const Angle radialraw = (floc.bearing(get_location_target()) -
      fprev.bearing(floc)).as_bearing();

  const fixed d = floc.distance(get_location_target());
  const fixed radius = floc.distance(get_location_min());
  const fixed rangeraw = min(fixed_one, d / radius);

  radial = radialraw.as_delta().value_degrees();
  const fixed rangesign = (fabs(radial) > fixed(90)) ?
      fixed_minus_one : fixed_one;
  range = rangeraw * rangesign;

  if ((oldrange == fixed_zero) && (range == fixed_zero))
    radial = fixed_zero;
}