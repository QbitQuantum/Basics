void
AircraftSim::integrate(const Angle& heading, const fixed timestep)
{
  GeoPoint v = endpoint(heading, timestep);
  state.track = state.location.bearing(v);
  state.ground_speed = v.distance(state.location)/timestep;
  state.location = v;
  state.altitude += state.vario*timestep;
  state.time += timestep;
}