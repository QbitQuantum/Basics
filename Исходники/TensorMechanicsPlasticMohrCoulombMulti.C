bool
TensorMechanicsPlasticMohrCoulombMulti::doReturnMap(const RankTwoTensor & trial_stress, Real intnl_old, const RankFourTensor & E_ijkl,
                                                    Real ep_plastic_tolerance, RankTwoTensor & returned_stress, Real & returned_intnl,
                                                    std::vector<Real> & dpm, RankTwoTensor & delta_dp, std::vector<Real> & yf,
                                                    bool & trial_stress_inadmissible) const
{
  mooseAssert(dpm.size() == 6, "TensorMechanicsPlasticMohrCoulombMulti size of dpm should be 6 but it is " << dpm.size());

  std::vector<Real> eigvals;
  RankTwoTensor eigvecs;
  trial_stress.symmetricEigenvaluesEigenvectors(eigvals, eigvecs);
  eigvals[0] += _shift;
  eigvals[2] -= _shift;

  Real sinphi = std::sin(phi(intnl_old));
  Real cosphi = std::cos(phi(intnl_old));
  Real coh = cohesion(intnl_old);
  Real cohcos = coh*cosphi;

  yieldFunctionEigvals(eigvals[0], eigvals[1], eigvals[2], sinphi, cohcos, yf);

  if (yf[0] <= _f_tol && yf[1] <= _f_tol && yf[2] <= _f_tol && yf[3] <= _f_tol && yf[4] <= _f_tol && yf[5] <= _f_tol)
  {
    // purely elastic (trial_stress, intnl_old)
    trial_stress_inadmissible = false;
    return true;
  }

  trial_stress_inadmissible = true;
  delta_dp.zero();
  returned_stress = RankTwoTensor();

  // these are the normals to the 6 yield surfaces, which are const because of the assumption of no psi hardening
  std::vector<RealVectorValue> norm(6);
  const Real sinpsi = std::sin(psi(intnl_old));
  const Real oneminus = 0.5*(1 - sinpsi);
  const Real oneplus = 0.5*(1 + sinpsi);
  norm[0](0) = oneplus; norm[0](1) = -oneminus; norm[0](2) = 0;
  norm[1](0) = -oneminus; norm[1](1) = oneplus; norm[1](2) = 0;
  norm[2](0) = oneplus; norm[2](1) = 0; norm[2](2) = -oneminus;
  norm[3](0) = -oneminus; norm[3](1) = 0; norm[3](2) = oneplus;
  norm[4](0) = 0; norm[4](1) = oneplus; norm[4](2) = -oneminus;
  norm[5](0) = 0; norm[5](1) = -oneminus; norm[5](2) = oneplus;

  // the flow directions are these norm multiplied by Eijkl.
  // I call the flow directions "n".
  // In the following I assume that the Eijkl is
  // for an isotropic situation.  Then I don't have to
  // rotate to the principal-stress frame, and i don't
  // have to worry about strange off-diagonal things
  std::vector<RealVectorValue> n(6);
  for (unsigned ys = 0; ys < 6; ++ys)
    for (unsigned i = 0; i < 3; ++i)
      for (unsigned j = 0; j < 3; ++j)
        n[ys](i) += E_ijkl(i,i,j,j)*norm[ys](j);
  const Real mag_E = E_ijkl(0, 0, 0, 0);

  // With non-zero Poisson's ratio and hardening
  // it is not computationally cheap to know whether
  // the trial stress will return to the tip, edge,
  // or plane.  The following at least
  // gives a not-completely-stupid guess
  // trial_order[0] = type of return to try first
  // trial_order[1] = type of return to try second
  // trial_order[2] = type of return to try third
  // trial_order[3] = type of return to try fourth
  // trial_order[4] = type of return to try fifth
  // In the following the "binary" stuff indicates the
  // deactive (0) and active (1) surfaces, eg
  // 110100 means that surfaces 0, 1 and 3 are active
  // and 2, 4 and 5 are deactive
  const unsigned int number_of_return_paths = 5;
  std::vector<int> trial_order(number_of_return_paths);
  if (yf[1] > _f_tol && yf[3] > _f_tol && yf[5] > _f_tol)
  {
    trial_order[0] = tip110100;
    trial_order[1] = edge010100;
    trial_order[2] = plane000100;
    trial_order[3] = edge000101;
    trial_order[4] = tip010101;
  }
  else if (yf[1] <= _f_tol && yf[3] > _f_tol && yf[5] > _f_tol)
  {
    trial_order[0] = edge000101;
    trial_order[1] = plane000100;
    trial_order[2] = tip110100;
    trial_order[3] = tip010101;
    trial_order[4] = edge010100;
  }
  else if (yf[1] <= _f_tol && yf[3] > _f_tol && yf[5] <= _f_tol)
  {
    trial_order[0] = plane000100;
    trial_order[1] = edge000101;
    trial_order[2] = edge010100;
    trial_order[3] = tip110100;
    trial_order[4] = tip010101;
  }
  else
  {
    trial_order[0] = edge010100;
    trial_order[1] = plane000100;
    trial_order[2] = edge000101;
    trial_order[3] = tip110100;
    trial_order[4] = tip010101;
  }

  unsigned trial;
  bool nr_converged = false;
  bool kt_success = false;
  std::vector<RealVectorValue> ntip(3);
  std::vector<Real> dpmtip(3);

  for (trial = 0; trial < number_of_return_paths; ++trial)
  {
    switch (trial_order[trial])
    {
      case tip110100:
        for (unsigned int i = 0; i < 3; ++i)
        {
          ntip[0](i) = n[0](i);
          ntip[1](i) = n[1](i);
          ntip[2](i) = n[3](i);
        }
        kt_success = returnTip(eigvals, ntip, dpmtip, returned_stress, intnl_old, sinphi, cohcos, 0, nr_converged, ep_plastic_tolerance, yf);
        if (nr_converged && kt_success)
        {
          dpm[0] = dpmtip[0];
          dpm[1] = dpmtip[1];
          dpm[3] = dpmtip[2];
          dpm[2] = dpm[4] = dpm[5] = 0;
        }
        break;

      case tip010101:
        for (unsigned int i = 0; i < 3; ++i)
        {
          ntip[0](i) = n[1](i);
          ntip[1](i) = n[3](i);
          ntip[2](i) = n[5](i);
        }
        kt_success = returnTip(eigvals, ntip, dpmtip, returned_stress, intnl_old, sinphi, cohcos, 0, nr_converged, ep_plastic_tolerance, yf);
        if (nr_converged && kt_success)
        {
          dpm[1] = dpmtip[0];
          dpm[3] = dpmtip[1];
          dpm[5] = dpmtip[2];
          dpm[0] = dpm[2] = dpm[4] = 0;
        }
        break;

      case edge000101:
        kt_success = returnEdge000101(eigvals, n, dpm, returned_stress, intnl_old, sinphi, cohcos, 0, mag_E, nr_converged, ep_plastic_tolerance, yf);
        break;

      case edge010100:
        kt_success = returnEdge010100(eigvals, n, dpm, returned_stress, intnl_old, sinphi, cohcos, 0, mag_E, nr_converged, ep_plastic_tolerance, yf);
        break;

      case plane000100:
        kt_success = returnPlane(eigvals, n, dpm, returned_stress, intnl_old, sinphi, cohcos, 0, nr_converged, ep_plastic_tolerance, yf);
        break;
    }

    if (nr_converged && kt_success)
      break;
  }

  if (trial == number_of_return_paths)
  {
    sinphi = std::sin(phi(intnl_old));
    cosphi = std::cos(phi(intnl_old));
    coh = cohesion(intnl_old);
    cohcos = coh*cosphi;
    yieldFunctionEigvals(eigvals[0], eigvals[1], eigvals[2], sinphi, cohcos, yf);
    Moose::err << "Trial stress = \n";
    trial_stress.print(Moose::err);
    Moose::err << "which has eigenvalues = " << eigvals[0] << " " << eigvals[1] << " " << eigvals[2] << "\n";
    Moose::err << "and yield functions = " << yf[0] << " " << yf[1] << " " << yf[2] << " " << yf[3] << " " << yf[4] << " " << yf[5] << "\n";
    Moose::err << "Internal parameter = " << intnl_old << "\n";
    mooseError("TensorMechanicsPlasticMohrCoulombMulti: FAILURE!  You probably need to implement a line search if your hardening is too severe, or you need to tune your tolerances (eg, yield_function_tolerance should be a little smaller than (young modulus)*ep_plastic_tolerance).\n");
    return false;
  }

  // success

  returned_intnl = intnl_old;
  for (unsigned i = 0; i < 6; ++i)
    returned_intnl += dpm[i];
  for (unsigned i = 0; i < 6; ++i)
    for (unsigned j = 0; j < 3; ++j)
      delta_dp(j, j) += dpm[i]*norm[i](j);
  returned_stress = eigvecs*returned_stress*(eigvecs.transpose());
  delta_dp = eigvecs*delta_dp*(eigvecs.transpose());
  return true;
}