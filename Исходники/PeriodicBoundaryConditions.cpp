void PeriodicBoundaryConditions::set(const Vector3D &e1, const Vector3D &e2,
                                     const Vector3D &e3,
                                     const Vector3D &origin) {
  myE1 = e1;
  myE2 = e2;
  myE3 = e3;
  myOrigin = origin;

  myV = fabs((e1.cross(e2)).dot(e3));
  if (myV < Constant::EPSILON)
    report << error <<
    "[PeriodicBoundaryConditions::set] No volume, aborting." << endr;
  if (myV >= Constant::REAL_INFINITY)
    report << error <<
    "[PeriodicBoundaryConditions::set] Infinite volume, aborting." << endr;

  myOrthogonal =
    !(e1.c[1] != 0.0 || e1.c[2] != 0.0 || e2.c[0] != 0.0 || e2.c[2] != 0.0 || e3.c[0] !=
      0.0 ||
      e3.c[1] != 0.0);

  Vector3D a1(e2.cross(e3));
  myE1r = a1 / e1.dot(a1);
  Vector3D a2(e3.cross(e1));
  myE2r = a2 / e2.dot(a2);
  Vector3D a3(e1.cross(e2));
  myE3r = a3 / e3.dot(a3);

  Vector3D a(origin - (e1 + e2 + e3) * 0.5);
  Vector3D b(origin + (e1 + e2 + e3) * 0.5);
  myMin.c[0] = min(a.c[0], b.c[0]);
  myMin.c[1] = min(a.c[1], b.c[1]);
  myMin.c[2] = min(a.c[2], b.c[2]);
  myMax.c[0] = max(a.c[0], b.c[0]);
  myMax.c[1] = max(a.c[1], b.c[1]);
  myMax.c[2] = max(a.c[2], b.c[2]);

  myDX = power<2>(e1.c[0] * 0.5);
  myDY = power<2>(e2.c[1] * 0.5);
  myDZ = power<2>(e3.c[2] * 0.5);
  myD = min(myDX, min(myDY, myDZ));
  myH = myMax - myMin;
  myH2 = myH * 0.5;
  report << debug(2) <<
  "[PeriodicBoundaryConditions] maximal safe distance=" << myD << endr;
}