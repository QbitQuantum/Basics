bool
TensorMechanicsPlasticJ2::returnMap(const RankTwoTensor & trial_stress,
                                    Real intnl_old,
                                    const RankFourTensor & E_ijkl,
                                    Real ep_plastic_tolerance,
                                    RankTwoTensor & returned_stress,
                                    Real & returned_intnl,
                                    std::vector<Real> & dpm,
                                    RankTwoTensor & delta_dp,
                                    std::vector<Real> & yf,
                                    bool & trial_stress_inadmissible) const
{
  if (!(_use_custom_returnMap))
    return TensorMechanicsPlasticModel::returnMap(trial_stress,
                                                  intnl_old,
                                                  E_ijkl,
                                                  ep_plastic_tolerance,
                                                  returned_stress,
                                                  returned_intnl,
                                                  dpm,
                                                  delta_dp,
                                                  yf,
                                                  trial_stress_inadmissible);

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
  Real mu = E_ijkl(0, 1, 0, 1);

  // Perform a Newton-Raphson to find dpm when
  // residual = 3*mu*dpm - trial_equivalent_stress + yieldStrength(intnl_old + dpm) = 0
  Real trial_equivalent_stress = yf_orig + yieldStrength(intnl_old);
  Real residual;
  Real jac;
  dpm[0] = 0;
  unsigned int iter = 0;
  do
  {
    residual = 3.0 * mu * dpm[0] - trial_equivalent_stress + yieldStrength(intnl_old + dpm[0]);
    jac = 3.0 * mu + dyieldStrength(intnl_old + dpm[0]);
    dpm[0] += -residual / jac;
    if (iter > _max_iters) // not converging
      return false;
    iter++;
  } while (residual * residual > _f_tol * _f_tol);

  // set the returned values
  yf[0] = 0;
  returned_intnl = intnl_old + dpm[0];
  RankTwoTensor nn = 1.5 * trial_stress.deviatoric() /
                     trial_equivalent_stress; // = dyieldFunction_dstress(trial_stress, intnl_old) =
                                              // the normal to the yield surface, at the trial
                                              // stress
  returned_stress = 2.0 / 3.0 * nn * yieldStrength(returned_intnl);
  returned_stress.addIa(1.0 / 3.0 * trial_stress.trace());
  delta_dp = nn * dpm[0];

  return true;
}