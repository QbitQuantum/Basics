Vector3 MassObj::getForce (const MassObj& mo) {
  // -Gm1m2/|r1-r2|^3.(r1-r2)
  Vector3 deltaP = position - mo.position;
  double deltaR = deltaP.getR();
  Vector3 f = Vector3(deltaP);
  f.invert();
  f.scale(mass*mo.mass/deltaR/deltaR/deltaR);
  return f;
}