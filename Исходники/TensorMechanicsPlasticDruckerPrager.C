Real
TensorMechanicsPlasticDruckerPrager::dyieldFunction_dintnl(const RankTwoTensor & stress,
                                                           Real intnl) const
{
  Real daaa;
  Real dbbb;
  dbothAB(intnl, daaa, dbbb);
  return stress.trace() * dbbb - daaa;
}