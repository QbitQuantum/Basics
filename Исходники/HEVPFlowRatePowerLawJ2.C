RankTwoTensor
HEVPFlowRatePowerLawJ2::computePK2Deviatoric(const RankTwoTensor & pk2,
                                             const RankTwoTensor & ce) const
{
  return pk2 - (pk2.doubleContraction(ce) * ce.inverse()) / 3.0;
}