AirspaceInterceptSolution
AbstractAirspace::Intercept(const AircraftState &state,
                            const GeoPoint &end,
                            const FlatProjection &projection,
                            const AirspaceAircraftPerformance &perf) const
{
  AirspaceInterceptSolution solution = AirspaceInterceptSolution::Invalid();
  for (const auto &i : Intersects(state.location, end, projection)) {
    auto new_solution = Intercept(state, perf, i.first, i.second);
    if (new_solution.IsEarlierThan(solution))
      solution = new_solution;
  }

  return solution;
}