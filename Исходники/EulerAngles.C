void
EulerAngles::random(MooseRandom & random)
{
  phi1 = random.rand(0) * 360.0;
  Phi = std::acos(1.0 - 2.0 * random.rand(0)) / libMesh::pi * 180.0;
  phi2 = random.rand(0) * 360;
}