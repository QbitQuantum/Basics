void
TensorMechanicsPlasticTensileMulti::activeConstraints(const std::vector<Real> & f, const RankTwoTensor & stress, const Real & intnl, const RankFourTensor & Eijkl, std::vector<bool> & act, RankTwoTensor & returned_stress) const
{
  act.assign(3, false);

  if (f[0] <= _f_tol && f[1] <= _f_tol && f[2] <= _f_tol)
  {
    returned_stress = stress;
    return;
  }

  returned_stress = RankTwoTensor();

  std::vector<Real> eigvals;
  RankTwoTensor eigvecs;
  stress.symmetricEigenvaluesEigenvectors(eigvals, eigvecs);
  eigvals[0] += _shift;
  eigvals[2] -= _shift;

  Real str = tensile_strength(intnl);
  std::vector<Real> v(3);
  v[0] = eigvals[0] - str;
  v[1] = eigvals[1] - str;
  v[2] = eigvals[2] - str;

  // these are the normals to the 3 yield surfaces
  std::vector<std::vector<Real> > n(3);
  n[0].resize(3);
  n[0][0] = 1 ; n[0][1] = 0 ; n[0][2] = 0;
  n[1].resize(3);
  n[1][0] = 0 ; n[1][1] = 1 ; n[1][2] = 0;
  n[2].resize(3);
  n[2][0] = 0 ; n[2][1] = 0 ; n[2][2] = 1;

  // the flow directions are these n multiplied by Eijkl.
  // I re-use the name "n" for the flow directions
  // In the following I assume that the Eijkl is
  // for an isotropic situation.  This is the most
  // common when using TensileMulti, and remember
  // that the returned_stress need not be perfect
  // anyway.
  // I divide by E(0,0,0,0) so the n remain of order 1
  Real ratio = Eijkl(1,1,0,0)/Eijkl(0,0,0,0);
  n[0][1] = n[0][2] = ratio;
  n[1][0] = n[1][2] = ratio;
  n[2][0] = n[2][1] = ratio;


  // 111 (tip)
  // For tip-return to satisfy Kuhn-Tucker, we need
  // v = alpha*n[0] + beta*n[1] * gamma*n[2]
  // with alpha, beta, and gamma all being non-negative (they are
  // the plasticity multipliers)
  Real denom = triple(n[0], n[1], n[2]);
  if (triple(v, n[0], n[1])/denom >= 0 && triple(v, n[1], n[2])/denom >= 0 && triple(v, n[2], n[0])/denom >= 0)
  {
    act[0] = act[1] = act[2] = true;
    returned_stress(0, 0) = returned_stress(1, 1) = returned_stress(2, 2) = str;
    returned_stress = eigvecs*returned_stress*(eigvecs.transpose());
    return;
  }

  // 011 (edge)
  std::vector<Real> n1xn2(3);
  n1xn2[0] = n[1][1]*n[2][2] - n[1][2]*n[2][1];
  n1xn2[1] = n[1][2]*n[2][0] - n[1][0]*n[2][2];
  n1xn2[2] = n[1][0]*n[2][1] - n[1][1]*n[2][0];
  // work out the point to which we would return, "a".  It is defined by
  // f1 = 0 = f2, and that (p - a).(n1 x n2) = 0, where "p" is the
  // starting position (p = eigvals).
  // In the following a = (a0, str, str)
  Real pdotn1xn2 = dot(eigvals, n1xn2);
  Real a0 = (-str*n1xn2[1] - str*n1xn2[2] + pdotn1xn2)/n1xn2[0];
  // we need p - a = alpha*n1 + beta*n2, where alpha and beta are non-negative
  // for Kuhn-Tucker to be satisfied
  std::vector<Real> pminusa(3);
  pminusa[0] = eigvals[0] - a0;
  pminusa[1] = v[1];
  pminusa[2] = v[2];
  if ((pminusa[2] - pminusa[0])/(1.0 - ratio) >= 0 && (pminusa[1] - pminusa[0])/(1.0 - ratio) >= 0)
  {
    returned_stress(0, 0) = a0;
    returned_stress(1, 1) = str;
    returned_stress(2, 2) = str;
    returned_stress = eigvecs*returned_stress*(eigvecs.transpose());
    act[1] = act[2] = true;
    return;
  }

  // 001 (plane)
  // the returned point, "a", is defined by f2=0 and
  // a = p - alpha*n2
  Real alpha = (eigvals[2] - str)/n[2][2];
  act[2] = true;
  returned_stress(0, 0) = eigvals[0] - alpha*n[2][0];
  returned_stress(1, 1) = eigvals[1] - alpha*n[2][1];
  returned_stress(2, 2) = str;
  returned_stress = eigvecs*returned_stress*(eigvecs.transpose());
  return;
}