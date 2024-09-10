//Add energy
inline double ewaldgpu_coulomb_pair_energy(double chgfac, double *d,double dist2,double dist)
{
  if (dist < ewaldgpu_params.rcut)
  {
     return coulomb.prefactor*chgfac*erfc(ewaldgpu_params.alpha*dist)/dist;
  }
  return 0.0;
}