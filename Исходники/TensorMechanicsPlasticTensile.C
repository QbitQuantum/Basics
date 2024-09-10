RankFourTensor
TensorMechanicsPlasticTensile::dflowPotential_dstress(const RankTwoTensor & stress,
                                                      Real /*intnl*/) const
{
  Real mean_stress = stress.trace() / 3.0;
  RankTwoTensor dmean_stress = stress.dtrace() / 3.0;
  Real sin3Lode = stress.sin3Lode(_lode_cutoff, 0);
  if (sin3Lode <= _sin3tt)
  {
    // the non-edge-smoothed version
    std::vector<Real> eigvals;
    std::vector<RankTwoTensor> deigvals;
    std::vector<RankFourTensor> d2eigvals;
    stress.dsymmetricEigenvalues(eigvals, deigvals);
    stress.d2symmetricEigenvalues(d2eigvals);

    Real denom = std::sqrt(smooth(stress) + Utility::pow<2>(eigvals[2] - mean_stress));
    Real denom3 = Utility::pow<3>(denom);
    RankTwoTensor numer_part = deigvals[2] - dmean_stress;
    RankTwoTensor numer_full =
        0.5 * dsmooth(stress) * dmean_stress + (eigvals[2] - mean_stress) * numer_part;
    Real d2smooth_over_denom = d2smooth(stress) / denom;

    RankFourTensor dr_dstress = (eigvals[2] - mean_stress) * d2eigvals[2] / denom;
    for (unsigned i = 0; i < 3; ++i)
      for (unsigned j = 0; j < 3; ++j)
        for (unsigned k = 0; k < 3; ++k)
          for (unsigned l = 0; l < 3; ++l)
          {
            dr_dstress(i, j, k, l) +=
                0.5 * d2smooth_over_denom * dmean_stress(i, j) * dmean_stress(k, l);
            dr_dstress(i, j, k, l) += numer_part(i, j) * numer_part(k, l) / denom;
            dr_dstress(i, j, k, l) -= numer_full(i, j) * numer_full(k, l) / denom3;
          }
    return dr_dstress;
  }
  else
  {
    // the edge-smoothed version
    RankTwoTensor dsin3Lode = stress.dsin3Lode(_lode_cutoff);
    Real kk = _aaa + _bbb * sin3Lode + _ccc * Utility::pow<2>(sin3Lode);
    RankTwoTensor dkk = (_bbb + 2.0 * _ccc * sin3Lode) * dsin3Lode;
    RankFourTensor d2kk = (_bbb + 2.0 * _ccc * sin3Lode) * stress.d2sin3Lode(_lode_cutoff);
    for (unsigned i = 0; i < 3; ++i)
      for (unsigned j = 0; j < 3; ++j)
        for (unsigned k = 0; k < 3; ++k)
          for (unsigned l = 0; l < 3; ++l)
            d2kk(i, j, k, l) += 2.0 * _ccc * dsin3Lode(i, j) * dsin3Lode(k, l);

    Real sibar2 = stress.secondInvariant();
    RankTwoTensor dsibar2 = stress.dsecondInvariant();
    RankFourTensor d2sibar2 = stress.d2secondInvariant();

    Real denom = std::sqrt(smooth(stress) + sibar2 * Utility::pow<2>(kk));
    Real denom3 = Utility::pow<3>(denom);
    Real d2smooth_over_denom = d2smooth(stress) / denom;
    RankTwoTensor numer_full =
        0.5 * dsmooth(stress) * dmean_stress + 0.5 * dsibar2 * kk * kk + sibar2 * kk * dkk;

    RankFourTensor dr_dstress = (0.5 * d2sibar2 * Utility::pow<2>(kk) + sibar2 * kk * d2kk) / denom;
    for (unsigned i = 0; i < 3; ++i)
      for (unsigned j = 0; j < 3; ++j)
        for (unsigned k = 0; k < 3; ++k)
          for (unsigned l = 0; l < 3; ++l)
          {
            dr_dstress(i, j, k, l) +=
                0.5 * d2smooth_over_denom * dmean_stress(i, j) * dmean_stress(k, l);
            dr_dstress(i, j, k, l) +=
                (dsibar2(i, j) * dkk(k, l) * kk + dkk(i, j) * dsibar2(k, l) * kk +
                 sibar2 * dkk(i, j) * dkk(k, l)) /
                denom;
            dr_dstress(i, j, k, l) -= numer_full(i, j) * numer_full(k, l) / denom3;
          }
    return dr_dstress;
  }
}