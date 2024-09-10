double notinwall(Cartesian r) {
  const double z = r.dot(Cartesian(0,0,1));
  if (fabs(z) > cavitysize/2) {
    return 0;
  } else {
    return 1;
  }
}