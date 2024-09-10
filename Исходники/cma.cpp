void CMA::GenCandidate()
{
  myRandMVN.Factor(Cov);
  Az=myRandMVN.Rand();
  for (int i=0;i<dim;i++)
  {
     NewState.x[i]=Reflect(BestState->x[i]+sigma*Az[i],pFunc->xmin[i],pFunc->xmax[i]);
  }
}