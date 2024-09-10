void kdSmbhSoft(KD kd, int nSplitting)
{
  
  int i;
  double max_mass;
  
  // smbh particles are ones with the largest mass
  max_mass = kd->pInit[0].fMass;
  for (i=0;i<kd->nParticles;i++) {
    if (max_mass < kd->pInit[i].fMass) {
      max_mass = kd->pInit[i].fMass;
    }
  }
  
  fprintf(stderr, "MAX MASS = %f\n", max_mass);
  for (i=0;i<kd->nParticles;i++) 
    if(kd->pInit[i].fMass == max_mass) 
      kd->pInit[i].fSoft = kd->pInit[i].fSoft/cbrt((double)nSplitting);
    
}