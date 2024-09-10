//Obtain deviatoric stress tensor
RankTwoTensor
FiniteStrainPlasticMaterial::getSigDev(RankTwoTensor sig)
{

//  Real sig_eqv,sij;
  RankTwoTensor identity;
  RankTwoTensor sig_dev;

  for (int i=0; i<3; i++)
    identity(i,i)=1.0;

  sig_dev=sig-identity*sig.trace()/3.0;
  return sig_dev;


}