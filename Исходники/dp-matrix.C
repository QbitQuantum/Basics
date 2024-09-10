void DPmatrixSimple::forward_cell(int i2,int j2) 
{
  assert(0 < i2 and i2 < size1());
  assert(0 < j2 and j2 < size2());

  prepare_cell(i2,j2);

  // determine initial scale for this cell
  scale(i2,j2) = max(scale(i2-1,j2), max( scale(i2-1,j2-1), scale(i2,j2-1) ) );

  double maximum = 0;

  // If we have silent states, then we have to process them in
  // the correct order: after all non-silent states and maybe
  // after some silent states.
  assert(not silent(order(nstates()-1)));

  for(int S2=0;S2<nstates();S2++) 
  {
    //--- Get (i1,j1) from (i2,j2) and S2
    int i1 = i2;
    if (di(S2)) i1--;

    int j1 = j2;
    if (dj(S2)) j1--;

    //--- Compute Arrival Probability ----
    double temp  = 0;
    for(int S1=0;S1<nstates();S1++)
      temp += (*this)(i1,j1,S1) * GQ(S1,S2);

    //--- Include Emission Probability----
    double sub;
    if (i1 != i2 and j1 != j2)
      sub = emitMM(i2,j2);
    else if (i1 != i2)
      sub = emitM_(i2,j2);
    else if (j1 != j2)
      sub = emit_M(i2,j2);
    else          // silent state - nothing emitted

      sub = emit__(i2,j2);

    temp *= sub;

    // rescale result to scale of this cell
    if (scale(i1,j1) != scale(i2,j2))
      temp *= pow2(scale(i1,j1)-scale(i2,j2));

    // record maximum
    if (temp > maximum) maximum = temp;

    // store the result
    (*this)(i2,j2,S2) = temp;
  }

  //------- if exponent is too low, rescale ------//
  if (maximum > 0 and maximum < fp_scale::cutoff) {
    int logs = -(int)log2(maximum);
    double scale_ = pow2(logs);
    for(int S2=0;S2<nstates();S2++) 
      (*this)(i2,j2,S2) *= scale_;
    scale(i2,j2) -= logs;
  }
} 