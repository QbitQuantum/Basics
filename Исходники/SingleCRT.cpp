void SingleCRT::toPoly(ZZX& poly, const IndexSet& s) const
{
  IndexSet s1 = map.getIndexSet() & s;

  if (card(s1) == 0) {
    clear(poly);
    return;
  }

  ZZ p = to_ZZ(context.ithPrime(s1.first()));  // the first modulus

  poly = map[s1.first()];  // Get poly modulo the first prime

  vec_ZZ& vp = poly.rep;

  // ensure that coeficient vector is of size phi(m) with entries in [-p/2,p/2]
  long phim = context.zMstar.phiM();
  long vpLength = vp.length();
  if (vpLength<phim) { // just in case of leading zeros in poly
    vp.SetLength(phim);
    for (long j=vpLength; j<phim; j++) vp[j]=0;
  }
  ZZ p_over_2 = p/2;
  for (long j=0; j<phim; j++) if (vp[j] > p_over_2) vp[j] -= p;

  // do incremental integer CRT for other levels  
  for (long i = s1.next(s1.first()); i <= s1.last(); i = s1.next(i)) {
    long q = context.ithPrime(i);       // the next modulus

    // CRT the coefficient vectors of poly and current
    intVecCRT(vp, p, map[i].rep, q);    // defined in the module NumbTh
    p *= q;     // update the modulus
  }
  poly.normalize(); // need to call this after we work on the coeffs
}