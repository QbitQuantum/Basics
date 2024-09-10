float MixtureMemo::Generate ( float _A, PoissonCDFApproxMemo *my_math )
{
  max_dim = my_math->max_dim;
  max_dim_minus_one = max_dim-1;
  max_entry = max_dim-1;
  inv_scale = 1/my_math->scale;
  _inv_scale = _mm_set_ss( inv_scale );
  scale = my_math->scale;

  int ileft, iright;
  float idelta, ifrac;

  A = _A;
  if ( A!=A )
    A=0.0001f; // safety check
  if ( A<0.0001f )
    A = 0.0001f; // safety
  // initialize diffusion/reaction simulation for this flow
  int maxA = LAST_POISSON_TABLE_COL; // largest value computed in the table
  if ( A>maxA )
    A = maxA;
  ileft = ( int ) A;
  idelta = A-ileft;
  iright = ileft+1;
  ifrac = 1-idelta;
  ileft--;
  iright--;

  occ_l = ifrac; // lower mixture
  occ_r = idelta; // upper mixture

  // special case # 1
  if ( ileft<0 ) // A between 0 and 1
  {
    ileft = 0;
    occ_l = 0.0f;
  }

  if ( iright==maxA ) // A at upper limit
  {
    // swap so only have one test when executing
    iright=ileft;
    occ_r = occ_l; // 1.0
    occ_l = 0.0f;
  }
  load_occ_vec( occ_r, occ_l );

  my_mixL = my_math->poiss_cdf[ileft];
  my_mixR = my_math->poiss_cdf[iright];

  if( ileft == 0 && iright == 0 )
      mixLUT = my_math->poissLUT[0]; //special case for the packed case for 0 < A < 1
  else
      mixLUT = my_math->poissLUT[ileft+1]; //layout: poiss_cdf[ei][i], poiss_cdf[ei+1][i], poiss_cdf[ei][i+1], poiss_cdf[ei+1][i+1]

  my_deltaL = my_math->dpoiss_cdf[ileft];
  my_deltaR = my_math->dpoiss_cdf[iright];
  my_totalL = my_math->ipoiss_cdf[ileft];
  my_totalR = my_math->ipoiss_cdf[iright];

  // could combine these two here, but as they're likely longer than the accesses, keep separate for now.

  total_live = occ_l + occ_r;
  left = right = 0;

  return ( A ); // if hit maximum
}