/* 
 * The version of BIZUNK that I implemented first.  
 */
SampleOnceRet_t SampleOnceBIZUNK1(StochasticLib2 &sto, int k, double pstar, double delta, double theta[], double sigma[], double logElimThresh, int n0, int batchsize) {
  int x; // generic counter

  assert(delta>0);
  assert(k>0);
  for (x=0; x<k; x++)
    assert(sigma[x]>=0);
  assert(k==1 || 1-exp(logElimThresh) >= pow(pstar,1.0/(k-1)));
  assert(batchsize>=1);

  SampleOnceRet_t ret;
  ret.nSamplesPerAlt = 0;
  ret.nSamples = 0;
  ret.nStages = 0;

  // If this condition is not met, then the randomized policy that does no
  // measurement is acceptable.  We do not treat this case because it isn't
  // particularly interesting.
  assert(pstar > (double)1/k);

  // Create five vectors.  
  // n[x] contains the number of samples taken from alternative x.  
  // mean[x] contains the mean of all the observations from alternative x.  
  // M2[x] contains the sum of the square differences from the current sample mean.
  // M2[x] = \sum_{i=1}^n (y_i - \ybar_n)^2, where y_i are the samples from alternative x.
  // The algorithm for updating the mean and M2 came from Wikipedia,
  // http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance 
  // who cites Knuth, and Knuth in turn apparently cites Welford.
  // The sample variance is given by M2[x] / n[x];
  // logq[x] is the log of q_{tx}(A).  
  // If logq[x] is -INFINITY then this indicates that the alternative has been eliminated.
  // prev_var[x] contains the previous value of the variance.  
  unsigned int n[k];
  double mean[k], M2[k], logq[k], prev_var[k];
  for (x=0; x<k; x++) {
    n[x] = 0;
    mean[x] = 0;
    M2[x] = 0;
    prev_var[x] = 0;
    logq[x] = 0;
  }

  double logpstar = log(pstar); // Precompute the log of pstar.

  // Take n0 samples from each alternative and update our statistics.
  for (x=0; x<k; x++) {
    while (n[x] < n0) {
      n[x]++;
      ret.nSamples++; 
      double y = theta[x] + sto.Normal(0,sigma[x]);
      double tmp = y - mean[x];
      mean[x] += tmp / n[x];
      M2[x] += tmp*(y - mean[x]);
      // prev_var and logq are initialized below.
    }
  }


  int extra = 0; // On the first pass through, don't add extra samples.  See first use of the extra variable below.
  while(1) {
    // At this point, we have the following arrays:
    // mean, M2, n, prev_var, logq.
    // prev_var and logq are not initialized.

    ret.nStages++;

    // Update n[x] for each x and take these additional samples.  
    //
    // If we are on our first pass through (i.e, all the n[x] are equal to n0),
    // we only do enough to bring everything on par.  If we are beyond this, we
    // do enough to add at least one sample.  This is implemented with the
    // variable "extra".
    //
    // First, we calculate prev_var[x] and m = \max_x n[x] / prev_var[x];
    double m = -1;
    for (x=0; x<k; x++) {
      if (logq[x] == -INFINITY) // if x has been eliminated
	continue;
      prev_var[x] = M2[x] / n[x]; // this is the variance before we take the new samples below.
      if (m == -1 || m < (n[x] + extra) / prev_var[x])
	m = (n[x] + extra) / prev_var[x];
    }
    // Now calculate n[x], take the samples, and calculate logq[x].
    for (x=0; x<k; x++) {
      if (logq[x] == -INFINITY) // if x has been eliminated
	continue;
      unsigned int new_n = ceil(prev_var[x] * m);  // This is n_{t+1,x}.
      while (n[x] < new_n) {
	n[x]++;
	ret.nSamples++;
	double y = theta[x] + sto.Normal(0,sigma[x]);
	double tmp = y - mean[x];
	mean[x] += tmp / n[x];
	M2[x] += tmp*(y - mean[x]);
      }
      // We do not update prev_var[x].  It is still using the previous value of the variance.
      logq[x] = delta * n[x] * mean[x] / prev_var[x];
      // PF: this should be more careful about numerical precision.  If the
      // mean of many of the alternatives is large, we could get an overflow.
      // This should subtract from logq the maximum value of logq across all x's.
    }
    extra = batchsize; // the next time we come through, add batchsize instead of 0.
    
    // Sum up the q's into sumq and find the worst alternative, putting results
    // in worst_x and worst_logq.
    double sumq = 0;
    int worst_x = -1;
    double worst_logq = 0;
    for (x=0; x<k; x++) {
      if (logq[x]==-INFINITY) // if x has been eliminated
	continue;
      if (worst_x == -1 || logq[x] < worst_logq) {
	worst_x = x;
	worst_logq = logq[x];
      }
      sumq += exp(logq[x]);
    }

#ifdef DEBUG
      printf("n = [");
      for (x=0; x<k; x++)
	printf("%d ", n[x]);
      printf("]\n");
      printf("q = [");
      for (x=0; x<k; x++)
	printf("%.3f ", logq[x] == -INFINITY ? 0 : exp(logq[x])/sumq);
      printf("]\n");
      printf("prev_var = [");
      for (x=0; x<k; x++)
	printf("%.3f ", prev_var[x]);
      printf("]\n");

#endif

    // The following loop eliminates one alternative on each pass through
    // It assumes that sumq, worst_x, and worst_logq have all been computed at the beginning.
    // Here, worst_logq = logq[worst_x], and sumq is the sum of exp(logq[x]) over all alternatives in contention.
    // Thus, worst_logq - logq(sumq) is the log of the normalized q for the worst alternative.
    
    while(worst_logq - log(sumq) <= logElimThresh) { // if this is true, eliminate the worst alternative

      // Eliminate the worst alternative and recompute sumq and logpstar
      logq[worst_x] = -INFINITY; // eliminate alternative argmin
      double worstq = exp(worst_logq) / sumq; // this is the normalized q of the worst alternative
#ifdef DEBUG
      printf("Elimination: argmin=%d q[argmin]=%.3f, ElimThresh=%.3f, current pstar=%.3f\n", worst_x, worstq, exp(logElimThresh), exp(logpstar));
#endif
      sumq -= exp(worst_logq); // maintain sumq as the sum of exp(logq[x]) over all x in contention.
      assert(sumq > 0);
      // The new target probability pstar increases by a factor of 1/(1-worstq), where worstq is the
      // probability of the alternative just eliminated, so the log of pstar becomes 
      // logpstar - log(1-worstq) = logpstar - log1p(-worstq)
      logpstar -= log1p(-worstq);
      assert(logpstar<0);

      // Update worst_x and worst_logq
      worst_x = -1;
      worst_logq = 0;
      for (x=0; x<k; x++) {
	if (logq[x]==-INFINITY) // if x has been eliminated
	  continue;
	if (worst_x ==-1 || logq[x]<worst_logq) {
	  worst_x  = x;
	  worst_logq = logq[x];
	}
      }

    } // End elimination while loop

    // Figure out the argmax over non-eliminated alternatives.
    int argmax = -1;
    double best_logq = 0;
    for (x=0; x<k; x++) {
      if (logq[x]==-INFINITY) // x has been eliminated
	continue;
      if (argmax==-1 || logq[x]>best_logq) {
	argmax = x;
	best_logq = logq[x];
      }
    }

    // Check whether we have exceeded the threshold and can stop.
    if (best_logq - log(sumq) >= logpstar) {
      // we choose alternative x. This is correct if x is 0, and incorrect
      // otherwise.
      // ret.correctSelection = (argmax == 0);
      ret.correctSelection = CorrectSelection(argmax,k,theta,delta);
      ret.nSamplesPerAlt = ret.nSamples / k;
#ifdef DEBUG
      if (ret.correctSelection) printf("correct selection\n");
      else printf("incorrect selection\n");
#endif
      return ret;
    }
  }
}