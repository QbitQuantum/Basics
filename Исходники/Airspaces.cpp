void 
Airspaces::VisitIntersecting(const GeoPoint &loc, const GeoPoint &end,
                             AirspaceIntersectionVisitor& visitor) const
{
  if (empty())
    // nothing to do
    return;

  const GeoPoint c = loc.Middle(end);
  Airspace bb_target(c, task_projection);
  int projected_range = task_projection.ProjectRangeInteger(c, loc.Distance(end) / 2);
  IntersectingAirspaceVisitorAdapter adapter(loc, end, task_projection, visitor);
  airspace_tree.visit_within_range(bb_target, -projected_range, adapter);

#ifdef INSTRUMENT_TASK
  n_queries++;
#endif
}