bool
AirspaceFilterData::Match(const GeoPoint &location,
                          const FlatProjection &projection,
                          const AbstractAirspace &as) const
{
  if (cls != AirspaceClass::AIRSPACECLASSCOUNT && as.GetType() != cls)
    return false;

  if (name_prefix != nullptr && !as.MatchNamePrefix(name_prefix))
    return false;

  if (!direction.IsNegative()) {
    const auto closest = as.ClosestPoint(location, projection);
    const auto bearing = location.Bearing(closest);
    auto direction_error = (bearing - direction).AsDelta().AbsoluteDegrees();
    if (direction_error > fixed(18))
      return false;
  }

  if (!negative(distance)) {
    const auto closest = as.ClosestPoint(location, projection);
    const auto distance = location.Distance(closest);
    if (distance > distance)
      return false;
  }

  return true;
}