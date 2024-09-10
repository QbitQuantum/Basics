//----------------------------------------------------------------------------
double PrThreshold::weightedL2Norm()
//-----------------------------------------------------------------------------
{
  int jlast = t_->getFinestLevel();
  int powerOfTwo = 1 << jlast; // 2 to the power jlast.

  int npts = t_->getNumNodes(jlast);
  vector<int> nghbrs;

  int i,j,deg;
  double sum = 0.0;

  for(i=0; i< npts; i++)
  {
    t_->getNeighbours(i,jlast,nghbrs); 
    deg = (int)nghbrs.size();
    for(j=0; j<deg-1; j++)
    {
      if(i < nghbrs[j] && i < nghbrs[j+1])
      {
        sum += triangleNorm(i,nghbrs[j],nghbrs[j+1]);
      }
    }
    if(!t_->isBoundary(i))
    {
      if(i < nghbrs[deg-1] && i < nghbrs[0])
      {
        sum += triangleNorm(i,nghbrs[deg-1],nghbrs[0]);
      }
    }
  }

  return sqrt(sum / 6.0) / powerOfTwo;
}