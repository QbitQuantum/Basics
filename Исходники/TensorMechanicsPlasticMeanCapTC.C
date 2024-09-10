bool
TensorMechanicsPlasticMeanCapTC::returnMap(const RankTwoTensor & trial_stress, Real intnl_old, const RankFourTensor & E_ijkl,
                                    Real ep_plastic_tolerance, RankTwoTensor & returned_stress, Real & returned_intnl,
                                    std::vector<Real> & dpm, RankTwoTensor & delta_dp, std::vector<Real> & yf,
                                    bool & trial_stress_inadmissible) const
{
  if (!(_use_custom_returnMap))
    return TensorMechanicsPlasticModel::returnMap(trial_stress, intnl_old, E_ijkl, ep_plastic_tolerance, returned_stress, returned_intnl, dpm, delta_dp, yf, trial_stress_inadmissible);

  yf.resize(1);

  Real yf_orig = yieldFunction(trial_stress, intnl_old);

  yf[0] = yf_orig;

  if (yf_orig < _f_tol)
  {
    // the trial_stress is admissible
    trial_stress_inadmissible = false;
    return true;
  }

  trial_stress_inadmissible = true;

  // In the following we want to solve
  // trial_stress - stress = E_ijkl * dpm * r   ...... (1)
  // and either
  // stress.trace() = tensile_strength(intnl)  ...... (2a)
  // intnl = intnl_old + dpm                   ...... (3a)
  // or
  // stress.trace() = compressive_strength(intnl) ... (2b)
  // intnl = intnl_old - dpm                   ...... (3b)
  // The former (2a and 3a) are chosen if
  // trial_stress.trace() > tensile_strength(intnl_old)
  // while the latter (2b and 3b) are chosen if
  // trial_stress.trace() < compressive_strength(intnl_old)
  // The variables we want to solve for are stress, dpm
  // and intnl.  We do this using a Newton approach, starting
  // with stress=trial_stress and intnl=intnl_old and dpm=0
  const bool tensile_failure = (trial_stress.trace() >= tensile_strength(intnl_old));
  const Real dirn = (tensile_failure ? 1.0 : -1.0);

  RankTwoTensor n; // flow direction, which is E_ijkl * r
  for (unsigned i = 0; i < 3; ++i)
    for (unsigned j = 0; j < 3; ++j)
      for (unsigned k = 0; k < 3; ++k)
             n(i, j) += dirn * E_ijkl(i, j, k, k);
  const Real n_trace = n.trace();

  // Perform a Newton-Raphson to find dpm when
  // residual = trial_stress.trace() - tensile_strength(intnl) - dpm * n.trace()  [for tensile_failure=true]
  // or
  // residual = trial_stress.trace() - compressive_strength(intnl) - dpm * n.trace()  [for tensile_failure=false]
  Real trial_trace = trial_stress.trace();
  Real residual;
  Real jac;
  dpm[0] = 0;
  unsigned int iter = 0;
  do {
    if (tensile_failure)
    {
      residual = trial_trace - tensile_strength(intnl_old + dpm[0]) - dpm[0] * n_trace;
      jac = -dtensile_strength(intnl_old + dpm[0]) - n_trace;
    }
    else
    {
      residual = trial_trace - compressive_strength(intnl_old - dpm[0]) - dpm[0] * n_trace;
      jac = -dcompressive_strength(intnl_old - dpm[0]) - n_trace;
    }
    dpm[0] += -residual/jac;
    if (iter > _max_iters) // not converging
      return false;
    iter++;
  } while (residual*residual > _f_tol*_f_tol);

  // set the returned values
  yf[0] = 0;
  returned_intnl = intnl_old + dirn * dpm[0];
  returned_stress = trial_stress - dpm[0] * n;
  delta_dp = dpm[0] * dirn * returned_stress.dtrace();

  return true;
}