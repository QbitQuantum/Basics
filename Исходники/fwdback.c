static int 
backward_engine(int do_full, const ESL_DSQ *dsq, int L, const P7_OPROFILE *om, const P7_OMX *fwd, P7_OMX *bck, float *opt_sc)
{
  register __m128 mpv, ipv, dpv;      /* previous row values                                       */
  register __m128 mcv, dcv;           /* current row values                                        */
  register __m128 tmmv, timv, tdmv;   /* tmp vars for accessing rotated transition scores          */
  register __m128 xBv;		      /* collects B->Mk components of B(i)                         */
  register __m128 xEv;	              /* splatted E(i)                                             */
  __m128   zerov;		      /* splatted 0.0's in a vector                                */
  float    xN, xE, xB, xC, xJ;	      /* special states' scores                                    */
  int      i;			      /* counter over sequence positions 0,1..L                    */
  int      q;			      /* counter over quads 0..Q-1                                 */
  int      Q       = p7O_NQF(om->M);  /* segment length: # of vectors                              */
  int      j;			      /* DD segment iteration counter (4 = full serialization)     */
  __m128  *dpc;                       /* current DP row                                            */
  __m128  *dpp;			      /* next ("previous") DP row                                  */
  __m128  *rp;			      /* will point into om->rfv[x] for residue x[i+1]             */
  __m128  *tp;		              /* will point into (and step thru) om->tfv transition scores */

  /* initialize the L row. */
  bck->M = om->M;
  bck->L = L;
  bck->has_own_scales = FALSE;	/* backwards scale factors are *usually* given by <fwd> */
  dpc    = bck->dpf[L * do_full];
  xJ     = 0.0;
  xB     = 0.0;
  xN     = 0.0;
  xC     = om->xf[p7O_C][p7O_MOVE];      /* C<-T */
  xE     = xC * om->xf[p7O_E][p7O_MOVE]; /* E<-C, no tail */
  xEv    = _mm_set1_ps(xE); 
  zerov  = _mm_setzero_ps();  
  dcv    = zerov;		/* solely to silence a compiler warning */
  for (q = 0; q < Q; q++) MMO(dpc,q) = DMO(dpc,q) = xEv;
  for (q = 0; q < Q; q++) IMO(dpc,q) = zerov;

  /* init row L's DD paths, 1) first segment includes xE, from DMO(q) */
  tp  = om->tfv + 8*Q - 1;	                        /* <*tp> now the [4 8 12 x] TDD quad         */
  dpv = _mm_move_ss(DMO(dpc,Q-1), zerov);               /* start leftshift: [1 5 9 13] -> [x 5 9 13] */
  dpv = _mm_shuffle_ps(dpv, dpv, _MM_SHUFFLE(0,3,2,1)); /* finish leftshift:[x 5 9 13] -> [5 9 13 x] */
  for (q = Q-1; q >= 0; q--)
    {
      dcv        = _mm_mul_ps(dpv, *tp);      tp--;
      DMO(dpc,q) = _mm_add_ps(DMO(dpc,q), dcv);
      dpv        = DMO(dpc,q);
    }
  /* 2) three more passes, only extending DD component (dcv only; no xE contrib from DMO(q)) */
  for (j = 1; j < 4; j++)
    {
      tp  = om->tfv + 8*Q - 1;	                            /* <*tp> now the [4 8 12 x] TDD quad         */
      dcv = _mm_move_ss(dcv, zerov);                        /* start leftshift: [1 5 9 13] -> [x 5 9 13] */
      dcv = _mm_shuffle_ps(dcv, dcv, _MM_SHUFFLE(0,3,2,1)); /* finish leftshift:[x 5 9 13] -> [5 9 13 x] */
      for (q = Q-1; q >= 0; q--)
	{
	  dcv        = _mm_mul_ps(dcv, *tp); tp--;
	  DMO(dpc,q) = _mm_add_ps(DMO(dpc,q), dcv);
	}
    }
  /* now MD init */
  tp  = om->tfv + 7*Q - 3;	                        /* <*tp> now the [4 8 12 x] Mk->Dk+1 quad    */
  dcv = _mm_move_ss(DMO(dpc,0), zerov);                 /* start leftshift: [1 5 9 13] -> [x 5 9 13] */
  dcv = _mm_shuffle_ps(dcv, dcv, _MM_SHUFFLE(0,3,2,1)); /* finish leftshift:[x 5 9 13] -> [5 9 13 x] */
  for (q = Q-1; q >= 0; q--)
    {
      MMO(dpc,q) = _mm_add_ps(MMO(dpc,q), _mm_mul_ps(dcv, *tp)); tp -= 7;
      dcv        = DMO(dpc,q);
    }

  /* Sparse rescaling: same scale factors as fwd matrix */
  if (fwd->xmx[L*p7X_NXCELLS+p7X_SCALE] > 1.0)
    {
      xE  = xE / fwd->xmx[L*p7X_NXCELLS+p7X_SCALE];
      xN  = xN / fwd->xmx[L*p7X_NXCELLS+p7X_SCALE];
      xC  = xC / fwd->xmx[L*p7X_NXCELLS+p7X_SCALE];
      xJ  = xJ / fwd->xmx[L*p7X_NXCELLS+p7X_SCALE];
      xB  = xB / fwd->xmx[L*p7X_NXCELLS+p7X_SCALE];
      xEv = _mm_set1_ps(1.0 / fwd->xmx[L*p7X_NXCELLS+p7X_SCALE]);
      for (q = 0; q < Q; q++) {
	MMO(dpc,q) = _mm_mul_ps(MMO(dpc,q), xEv);
	DMO(dpc,q) = _mm_mul_ps(DMO(dpc,q), xEv);
	IMO(dpc,q) = _mm_mul_ps(IMO(dpc,q), xEv);
      }
    }
  bck->xmx[L*p7X_NXCELLS+p7X_SCALE] = fwd->xmx[L*p7X_NXCELLS+p7X_SCALE];
  bck->totscale                     = log(bck->xmx[L*p7X_NXCELLS+p7X_SCALE]);

  /* Stores */
  bck->xmx[L*p7X_NXCELLS+p7X_E] = xE;
  bck->xmx[L*p7X_NXCELLS+p7X_N] = xN;
  bck->xmx[L*p7X_NXCELLS+p7X_J] = xJ;
  bck->xmx[L*p7X_NXCELLS+p7X_B] = xB;
  bck->xmx[L*p7X_NXCELLS+p7X_C] = xC;

#if p7_DEBUGGING
  if (bck->debugging) p7_omx_DumpFBRow(bck, TRUE, L, 9, 4, xE, xN, xJ, xB, xC);	/* logify=TRUE, <rowi>=L, width=9, precision=4*/
#endif

  /* main recursion */
  for (i = L-1; i >= 1; i--)	/* backwards stride */
    {
      /* phase 1. B(i) collected. Old row destroyed, new row contains
       *    complete I(i,k), partial {MD}(i,k) w/ no {MD}->{DE} paths yet.
       */
      dpc = bck->dpf[i     * do_full];
      dpp = bck->dpf[(i+1) * do_full];
      rp  = om->rfv[dsq[i+1]] + Q-1; /* <*rp> is now the [4 8 12 x] match emission quad */
      tp  = om->tfv + 7*Q - 1;	     /* <*tp> is now the [4 8 12 x] TII transition quad  */

      /* leftshift the first transition quads */
      tmmv = _mm_move_ss(om->tfv[1], zerov); tmmv = _mm_shuffle_ps(tmmv, tmmv, _MM_SHUFFLE(0,3,2,1));
      timv = _mm_move_ss(om->tfv[2], zerov); timv = _mm_shuffle_ps(timv, timv, _MM_SHUFFLE(0,3,2,1));
      tdmv = _mm_move_ss(om->tfv[3], zerov); tdmv = _mm_shuffle_ps(tdmv, tdmv, _MM_SHUFFLE(0,3,2,1));

      mpv = _mm_mul_ps(MMO(dpp,0), om->rfv[dsq[i+1]][0]); /* precalc M(i+1,k+1) * e(M_k+1, x_{i+1}) */
      mpv = _mm_move_ss(mpv, zerov);
      mpv = _mm_shuffle_ps(mpv, mpv, _MM_SHUFFLE(0,3,2,1));

      xBv = zerov;
      for (q = Q-1; q >= 0; q--)     /* backwards stride */
	{
	  ipv = IMO(dpp,q); /* assumes emission odds ratio of 1.0; i+1's IMO(q) now free */
	  IMO(dpc,q) = _mm_add_ps(_mm_mul_ps(ipv, *tp), _mm_mul_ps(mpv, timv));   tp--;
	  DMO(dpc,q) =                                  _mm_mul_ps(mpv, tdmv); 
	  mcv        = _mm_add_ps(_mm_mul_ps(ipv, *tp), _mm_mul_ps(mpv, tmmv));   tp-= 2;
	  
	  mpv        = _mm_mul_ps(MMO(dpp,q), *rp);  rp--;  /* obtain mpv for next q. i+1's MMO(q) is freed  */
	  MMO(dpc,q) = mcv;

	  tdmv = *tp;   tp--;
	  timv = *tp;   tp--;
	  tmmv = *tp;   tp--;

	  xBv = _mm_add_ps(xBv, _mm_mul_ps(mpv, *tp)); tp--;
	}

      /* phase 2: now that we have accumulated the B->Mk transitions in xBv, we can do the specials */
      /* this incantation is a horiz sum of xBv elements: (_mm_hadd_ps() would require SSE3) */
      xBv = _mm_add_ps(xBv, _mm_shuffle_ps(xBv, xBv, _MM_SHUFFLE(0, 3, 2, 1)));
      xBv = _mm_add_ps(xBv, _mm_shuffle_ps(xBv, xBv, _MM_SHUFFLE(1, 0, 3, 2)));
      _mm_store_ss(&xB, xBv);

      xC =  xC * om->xf[p7O_C][p7O_LOOP];
      xJ = (xB * om->xf[p7O_J][p7O_MOVE]) + (xJ * om->xf[p7O_J][p7O_LOOP]); /* must come after xB */
      xN = (xB * om->xf[p7O_N][p7O_MOVE]) + (xN * om->xf[p7O_N][p7O_LOOP]); /* must come after xB */
      xE = (xC * om->xf[p7O_E][p7O_MOVE]) + (xJ * om->xf[p7O_E][p7O_LOOP]); /* must come after xJ, xC */
      xEv = _mm_set1_ps(xE);	/* splat */


      /* phase 3: {MD}->E paths and one step of the D->D paths */
      tp  = om->tfv + 8*Q - 1;	/* <*tp> now the [4 8 12 x] TDD quad */
      dpv = _mm_add_ps(DMO(dpc,0), xEv);
      dpv = _mm_move_ss(dpv, zerov);
      dpv = _mm_shuffle_ps(dpv, dpv, _MM_SHUFFLE(0,3,2,1));
      for (q = Q-1; q >= 0; q--)
	{
	  dcv        = _mm_mul_ps(dpv, *tp); tp--;
	  DMO(dpc,q) = _mm_add_ps(DMO(dpc,q), _mm_add_ps(dcv, xEv));
	  dpv        = DMO(dpc,q);
	  MMO(dpc,q) = _mm_add_ps(MMO(dpc,q), xEv);
	}
      
      /* phase 4: finish extending the DD paths */
      /* fully serialized for now */
      for (j = 1; j < 4; j++)	/* three passes: we've already done 1 segment, we need 4 total */
	{
	  dcv = _mm_move_ss(dcv, zerov);
	  dcv = _mm_shuffle_ps(dcv, dcv, _MM_SHUFFLE(0,3,2,1));
	  tp  = om->tfv + 8*Q - 1;	/* <*tp> now the [4 8 12 x] TDD quad */
	  for (q = Q-1; q >= 0; q--)
	    {
	      dcv        = _mm_mul_ps(dcv, *tp); tp--;
	      DMO(dpc,q) = _mm_add_ps(DMO(dpc,q), dcv);
	    }
	}

      /* phase 5: add M->D paths */
      dcv = _mm_move_ss(DMO(dpc,0), zerov);
      dcv = _mm_shuffle_ps(dcv, dcv, _MM_SHUFFLE(0,3,2,1));
      tp  = om->tfv + 7*Q - 3;	/* <*tp> is now the [4 8 12 x] Mk->Dk+1 quad */
      for (q = Q-1; q >= 0; q--)
	{
	  MMO(dpc,q) = _mm_add_ps(MMO(dpc,q), _mm_mul_ps(dcv, *tp)); tp -= 7;
	  dcv        = DMO(dpc,q);
	}

      /* Sparse rescaling  */

      /* In rare cases [J3/119] scale factors from <fwd> are
       * insufficient and backwards will overflow. In this case, we
       * switch on the fly to using our own scale factors, different
       * from those in <fwd>. This will complicate subsequent
       * posterior decoding routines.
       */
      if (xB > 1.0e16) bck->has_own_scales = TRUE;

      if      (bck->has_own_scales)  bck->xmx[i*p7X_NXCELLS+p7X_SCALE] = (xB > 1.0e4) ? xB : 1.0;
      else                           bck->xmx[i*p7X_NXCELLS+p7X_SCALE] = fwd->xmx[i*p7X_NXCELLS+p7X_SCALE];

      if (bck->xmx[i*p7X_NXCELLS+p7X_SCALE] > 1.0)
	{
	  xE /= bck->xmx[i*p7X_NXCELLS+p7X_SCALE];
	  xN /= bck->xmx[i*p7X_NXCELLS+p7X_SCALE];
	  xJ /= bck->xmx[i*p7X_NXCELLS+p7X_SCALE];
	  xB /= bck->xmx[i*p7X_NXCELLS+p7X_SCALE];
	  xC /= bck->xmx[i*p7X_NXCELLS+p7X_SCALE];
	  xBv = _mm_set1_ps(1.0 / bck->xmx[i*p7X_NXCELLS+p7X_SCALE]);
	  for (q = 0; q < Q; q++) {
	    MMO(dpc,q) = _mm_mul_ps(MMO(dpc,q), xBv);
	    DMO(dpc,q) = _mm_mul_ps(DMO(dpc,q), xBv);
	    IMO(dpc,q) = _mm_mul_ps(IMO(dpc,q), xBv);
	  }
	  bck->totscale += log(bck->xmx[i*p7X_NXCELLS+p7X_SCALE]);
	}

      /* Stores are separate only for pedagogical reasons: easy to
       * turn this into a more memory efficient version just by
       * deleting the stores.
       */
      bck->xmx[i*p7X_NXCELLS+p7X_E] = xE;
      bck->xmx[i*p7X_NXCELLS+p7X_N] = xN;
      bck->xmx[i*p7X_NXCELLS+p7X_J] = xJ;
      bck->xmx[i*p7X_NXCELLS+p7X_B] = xB;
      bck->xmx[i*p7X_NXCELLS+p7X_C] = xC;

#if p7_DEBUGGING
      if (bck->debugging) p7_omx_DumpFBRow(bck, TRUE, i, 9, 4, xE, xN, xJ, xB, xC);	/* logify=TRUE, <rowi>=i, width=9, precision=4*/
#endif
    } /* thus ends the loop over sequence positions i */

  /* Termination at i=0, where we can only reach N,B states. */
  dpp = bck->dpf[1 * do_full];
  tp  = om->tfv;          /* <*tp> is now the [1 5 9 13] TBMk transition quad  */
  rp  = om->rfv[dsq[1]];  /* <*rp> is now the [1 5 9 13] match emission quad   */
  xBv = zerov;
  for (q = 0; q < Q; q++)
    {
      mpv = _mm_mul_ps(MMO(dpp,q), *rp);  rp++;
      mpv = _mm_mul_ps(mpv,        *tp);  tp += 7;
      xBv = _mm_add_ps(xBv,        mpv);
    }
  /* horizontal sum of xBv */
  xBv = _mm_add_ps(xBv, _mm_shuffle_ps(xBv, xBv, _MM_SHUFFLE(0, 3, 2, 1)));
  xBv = _mm_add_ps(xBv, _mm_shuffle_ps(xBv, xBv, _MM_SHUFFLE(1, 0, 3, 2)));
  _mm_store_ss(&xB, xBv);
 
  xN = (xB * om->xf[p7O_N][p7O_MOVE]) + (xN * om->xf[p7O_N][p7O_LOOP]);  

  bck->xmx[p7X_B]     = xB;
  bck->xmx[p7X_C]     = 0.0;
  bck->xmx[p7X_J]     = 0.0;
  bck->xmx[p7X_N]     = xN;
  bck->xmx[p7X_E]     = 0.0;
  bck->xmx[p7X_SCALE] = 1.0;

#if p7_DEBUGGING
  dpc = bck->dpf[0];
  for (q = 0; q < Q; q++) /* Not strictly necessary, but if someone's looking at DP matrices, this is nice to do: */
    MMO(dpc,q) = DMO(dpc,q) = IMO(dpc,q) = zerov;
  if (bck->debugging) p7_omx_DumpFBRow(bck, TRUE, 0, 9, 4, bck->xmx[p7X_E], bck->xmx[p7X_N],  bck->xmx[p7X_J], bck->xmx[p7X_B],  bck->xmx[p7X_C]);	/* logify=TRUE, <rowi>=0, width=9, precision=4*/
#endif

  if       (isnan(xN))        ESL_EXCEPTION(eslERANGE, "backward score is NaN");
  else if  (L>0 && xN == 0.0) ESL_EXCEPTION(eslERANGE, "backward score underflow (is 0.0)");    /* if L==0, xN *should* be 0.0 [J5/118]*/
  else if  (isinf(xN) == 1)   ESL_EXCEPTION(eslERANGE, "backward score overflow (is infinity)");

  if (opt_sc != NULL) *opt_sc = bck->totscale + log(xN);
  return eslOK;
}