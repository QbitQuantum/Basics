double lrchisq(const double *par)
{
  // chisq from likelihood ratio
  // for more information see Baker and Cousins pg. 439 and Appendix
  double yi=0.;        // model
  double ni=0.;        // experiment
  double lrchisq = 0.; // likelihood ratio chisq
  int i=0;

  for (i=startCh[spCurrent]; i<=endCh[spCurrent]; i++)
    {
      // events in ith bin
      ni = expCurrent[i]; 
      
      // calculate model in the ith bin
      yi = par[0]*simCurrent[i] + par[1] + par[2]*erfc(((double)i-sfc[spCurrent])/sfw[spCurrent]);
      
      // evaluate chisq given input parameters
      if(ni > 0.)
	lrchisq += ( yi - ni + ni*log(ni/yi) );
      else
	lrchisq += yi; // the log(0) case
    }
  lrchisq *= 2.;
  return lrchisq;
}