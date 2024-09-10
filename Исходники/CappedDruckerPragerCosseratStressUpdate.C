void
CappedDruckerPragerCosseratStressUpdate::consistentTangentOperator(
    const RankTwoTensor & /*stress_trial*/,
    Real /*p_trial*/,
    Real /*q_trial*/,
    const RankTwoTensor & stress,
    Real /*p*/,
    Real q,
    Real gaE,
    const yieldAndFlow & smoothed_q,
    const RankFourTensor & Eijkl,
    bool compute_full_tangent_operator,
    RankFourTensor & cto) const
{
  if (!compute_full_tangent_operator)
  {
    cto = Eijkl;
    return;
  }

  RankFourTensor EAijkl;
  for (unsigned i = 0; i < _tensor_dimensionality; ++i)
    for (unsigned j = 0; j < _tensor_dimensionality; ++j)
      for (unsigned k = 0; k < _tensor_dimensionality; ++k)
        for (unsigned l = 0; l < _tensor_dimensionality; ++l)
        {
          cto(i, j, k, l) = 0.5 * (Eijkl(i, j, k, l) + Eijkl(j, i, k, l));
          EAijkl(i, j, k, l) = 0.5 * (Eijkl(i, j, k, l) - Eijkl(j, i, k, l));
        }

  const RankTwoTensor s_over_q =
      (q == 0.0 ? RankTwoTensor()
                : (0.5 * (stress + stress.transpose()) -
                   stress.trace() * RankTwoTensor(RankTwoTensor::initIdentity) / 3.0) /
                      q);
  const RankTwoTensor E_s_over_q = Eijkl.innerProductTranspose(s_over_q); // not symmetric in kl
  const RankTwoTensor Ekl =
      RankTwoTensor(RankTwoTensor::initIdentity).initialContraction(Eijkl); // symmetric in kl

  for (unsigned i = 0; i < _tensor_dimensionality; ++i)
    for (unsigned j = 0; j < _tensor_dimensionality; ++j)
      for (unsigned k = 0; k < _tensor_dimensionality; ++k)
        for (unsigned l = 0; l < _tensor_dimensionality; ++l)
        {
          cto(i, j, k, l) -= (i == j) * (1.0 / 3.0) *
                             (Ekl(k, l) * (1.0 - _dp_dpt) + 0.5 * E_s_over_q(k, l) * (-_dp_dqt));
          cto(i, j, k, l) -=
              s_over_q(i, j) * (Ekl(k, l) * (-_dq_dpt) + 0.5 * E_s_over_q(k, l) * (1.0 - _dq_dqt));
        }

  if (smoothed_q.dg[1] != 0.0)
  {
    const RankFourTensor Tijab = _Ehost * (gaE / _Epp) * smoothed_q.dg[1] * d2qdstress2(stress);
    RankFourTensor inv = RankFourTensor(RankFourTensor::initIdentitySymmetricFour) + Tijab;
    try
    {
      inv = inv.transposeMajor().invSymm();
    }
    catch (const MooseException & e)
    {
      // Cannot form the inverse, so probably at some degenerate place in stress space.
      // Just return with the "best estimate" of the cto.
      mooseWarning("CappedDruckerPragerCosseratStressUpdate: Cannot invert 1+T in consistent "
                   "tangent operator computation at quadpoint ",
                   _qp,
                   " of element ",
                   _current_elem->id());
      return;
    }
    cto = (cto.transposeMajor() * inv).transposeMajor();
  }
  cto += EAijkl;
}