bool
FlowRateModel::computeDflowrateDstress(RankTwoTensor & dflowrate_dstress,
                                       const RankTwoTensor & pk2,
                                       const RankTwoTensor & ce,
                                       const std::vector<Real> & internal_var,
                                       const unsigned int start_index,
                                       const unsigned int /*size*/) const
{
  RankTwoTensor pk2_dev = computePK2Deviatoric(pk2, ce);
  Real eqv_stress = computeEqvStress(pk2_dev, ce);

  Real sigy = _flow_stress_uo.value(internal_var[start_index]);
  Real dflowrate_dseqv = _ref_flow_rate * _flow_rate_exponent * std::pow(eqv_stress/sigy,_flow_rate_exponent-1) * 1/sigy;

  if (dflowrate_dseqv > _flow_rate_tol)
  {
#ifdef DEBUG
    mooseWarning("dflowrate_dseqv greater than " << _flow_rate_tol << " " << dflowrate_dseqv << " " << eqv_stress << " " << sigy );
#endif
    return false;
  }

  RankTwoTensor tau = pk2_dev * ce;
  RankTwoTensor dseqv_dpk2dev;
  dseqv_dpk2dev.zero();
  if (eqv_stress > 0)
    dseqv_dpk2dev = 3/(2 * eqv_stress) * tau * ce;

  RankTwoTensor ce_inv = ce.inverse();

  RankFourTensor dpk2dev_dpk2;
  for (unsigned int i = 0; i < LIBMESH_DIM; ++i)
    for (unsigned int j = 0; j < LIBMESH_DIM; ++j)
      for (unsigned int k = 0; k < LIBMESH_DIM; ++k)
        for (unsigned int l = 0; l < LIBMESH_DIM; ++l)
        {
          dpk2dev_dpk2(i, j, k, l) = 0.0;
          if (i==k && j==l)
            dpk2dev_dpk2(i, j, k, l) = 1.0;
          dpk2dev_dpk2(i, j, k, l) -= ce_inv(i, j) * ce(k, l)/3.0;
        }

  dflowrate_dstress = dflowrate_dseqv * dpk2dev_dpk2.transposeMajor() * dseqv_dpk2dev;
  return true;
}