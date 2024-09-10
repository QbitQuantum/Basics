// TODO TB: find explanations/links for this and following
Angle
SunEphemeris::GetHourAngle(Angle lat, Angle declin)
{
  Angle dfo = Angle::degrees(SUN_DIAMETER / 2 + AIR_REFRACTION);

  // Correction: different sign at southern hemisphere
  if (negative(lat.value_degrees()))
    dfo.flip();

  fixed fo = (declin + dfo).tan() * lat.tan();
  fo = asin(fo) + fixed_half_pi;

  return Angle::radians(fo);
}