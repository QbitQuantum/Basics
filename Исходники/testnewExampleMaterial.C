RankTwoTensor
testnewExampleMaterial::computeLp(const RankTwoTensor & fp_dot, const RankTwoTensor & fp) const
{
  return fp_dot*fp.inverse();
}