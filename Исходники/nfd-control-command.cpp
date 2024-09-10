void
RibRegisterCommand::applyDefaultsToRequest(ControlParameters& parameters) const
{
  if (!parameters.hasFaceId()) {
    parameters.setFaceId(0);
  }
  if (!parameters.hasOrigin()) {
    parameters.setOrigin(ROUTE_ORIGIN_APP);
  }
  if (!parameters.hasCost()) {
    parameters.setCost(0);
  }
  if (!parameters.hasFlags()) {
    parameters.setFlags(ROUTE_FLAG_CHILD_INHERIT);
  }
}