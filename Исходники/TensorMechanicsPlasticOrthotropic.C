Real
TensorMechanicsPlasticOrthotropic::yieldFunction(const RankTwoTensor & stress, Real intnl) const
{
  const RankTwoTensor j2prime = _l1 * stress;
  const RankTwoTensor j3prime = _l2 * stress;
  return _b * stress.trace() +
         std::pow(std::pow(-j2prime.generalSecondInvariant(), 3.0 / 2.0) - j3prime.det(),
                  1.0 / 3.0) -
         yieldStrength(intnl);
}