/* Function:  p7_Null2_ByTrace()
 * Synopsis:  Assign null2 scores to an envelope by the sampling method.
 * Incept:    SRE, Mon Aug 18 10:22:49 2008 [Janelia]
 *
 * Purpose:   Identical to <p7_GNull2_ByTrace()> except that
 *            <om>, <wrk> are SSE optimized versions of the profile
 *            and the residue posterior probability matrix. See 
 *            <p7_GNull2_ByTrace()>  documentation.
 */
int
p7_Null2_ByTrace(const P7_OPROFILE *om, const P7_TRACE *tr, int zstart, int zend, P7_OMX *wrk, float *null2)
{
  union { __m128 v; float p[4]; } u;
  int    Q  = p7O_NQF(om->M);
  int    Ld = 0;
  float *xmx = wrk->xmx;	/* enables use of XMXo macro */
  float  norm;
  float  xfactor;
  __m128 sv;
  __m128 *rp;
  int    q, r, s;
  int    x;
  int    z;

  /* We'll use the i=0 row in wrk for working space: dp[0][] and xmx[][0]. */
  for (q = 0; q < Q; q++)
    {
      wrk->dpf[0][q*3 + p7X_M] = _mm_setzero_ps();
      wrk->dpf[0][q*3 + p7X_I] = _mm_setzero_ps();
    }
  XMXo(0,p7X_N) =  0.0;
  XMXo(0,p7X_C) =  0.0;
  XMXo(0,p7X_J) =  0.0;

  /* Calculate emitting state usage in this particular trace segment */
  for (z = zstart; z <= zend; z++)
    {
      if (tr->i[z] == 0) continue; /* quick test for whether this trace elem emitted or not */
      Ld++;
      if (tr->k[z] > 0)	/* must be an M or I */
	{ /* surely there's an easier way? but our workspace is striped, interleaved quads... */
	  s = ( (tr->st[z] == p7T_M) ?  p7X_M : p7X_I);
	  q = p7X_NSCELLS * ( (tr->k[z] - 1) % Q) + p7X_M;
	  r = (tr->k[z] - 1) / Q;
	  u.v            = wrk->dpf[0][q];
	  u.p[r]        += 1.0;	/* all this to increment a count by one! */
	  wrk->dpf[0][q] = u.v;

	}
      else /* emitted an x_i with no k; must be an N,C,J */
	{
	  switch (tr->st[z]) {
	  case p7T_N: XMXo(0,p7X_N) += 1.0; break;
	  case p7T_C: XMXo(0,p7X_C) += 1.0; break;
	  case p7T_J: XMXo(0,p7X_J) += 1.0; break;
	  }
	}
    }
  norm = 1.0 / (float) Ld;
  sv = _mm_set1_ps(norm);
  for (q = 0; q < Q; q++)
    {
      wrk->dpf[0][q*3 + p7X_M] = _mm_mul_ps(wrk->dpf[0][q*3 + p7X_M], sv);
      wrk->dpf[0][q*3 + p7X_I] = _mm_mul_ps(wrk->dpf[0][q*3 + p7X_I], sv);
    }
  XMXo(0,p7X_N) *= norm;
  XMXo(0,p7X_C) *= norm;
  XMXo(0,p7X_J) *= norm;

  /* Calculate null2's emission odds, by taking posterior weighted sum
   * over all emission vectors used in paths explaining the domain.
   */
  xfactor =  XMXo(0,p7X_N) + XMXo(0,p7X_C) + XMXo(0,p7X_J);
  for (x = 0; x < om->abc->K; x++)
    {
      sv = _mm_setzero_ps();
      rp = om->rfv[x];
      for (q = 0; q < Q; q++)
	{
	  sv = _mm_add_ps(sv, _mm_mul_ps(wrk->dpf[0][q*3 + p7X_M], *rp)); rp++;
	  sv = _mm_add_ps(sv,            wrk->dpf[0][q*3 + p7X_I]); /* insert emission odds implicitly 1.0 */
	  //	  sv = _mm_add_ps(sv, _mm_mul_ps(wrk->dpf[0][q*3 + p7X_I], *rp)); rp++;
	}
      esl_sse_hsum_ps(sv, &(null2[x]));
      null2[x] += xfactor;
    }
  /* now null2[x] = \frac{f_d(x)}{f_0(x)} for all x in alphabet,
   * 0..K-1, where f_d(x) are the ad hoc "null2" residue frequencies
   * for this envelope.
   */

  /* make valid scores for all degeneracies, by averaging the odds ratios. */
  esl_abc_FAvgScVec(om->abc, null2);
  null2[om->abc->K]    = 1.0;        /* gap character    */
  null2[om->abc->Kp-2] = 1.0;	     /* nonresidue "*"   */
  null2[om->abc->Kp-1] = 1.0;	     /* missing data "~" */

  return eslOK;
}