void Cmodulus::iFFT(zz_pX &x, const vec_long& y)const
{
  FHE_TIMER_START;
  zz_pBak bak; bak.save();
  context.restore();

  if (zMStar->getPow2()) {
    // special case when m is a power of 2

    long k = zMStar->getPow2();
    long phim = (1L << (k-1));
    long p = zz_p::modulus();

    const zz_p *ipowers_p = (*ipowers).rep.elts();
    const mulmod_precon_t *ipowers_aux_p = ipowers_aux.elts();

    const long *yp = y.elts();

    vec_long& tmp = Cmodulus::getScratch_vec_long();
    tmp.SetLength(phim);
    long *tmp_p = tmp.elts();

#ifdef FHE_OPENCL
    AltFFTRev1(tmp_p, yp, k-1, *altFFTInfo);
#else
    FFTRev1(tmp_p, yp, k-1, *zz_pInfo->p_info);
#endif

    x.rep.SetLength(phim);
    zz_p *xp = x.rep.elts();

    for (long i = 0; i < phim; i++)
      xp[i].LoopHole() = MulModPrecon(tmp_p[i], rep(ipowers_p[i]), p, ipowers_aux_p[i]);


    x.normalize();

    return;
  }



  zz_p rt;
  long m = getM();

  // convert input to zpx format, initializing only the coeffs i s.t. (i,m)=1
  x.rep.SetLength(m);
  long i,j;
  for (i=j=0; i<m; i++)
    if (zMStar->inZmStar(i)) x.rep[i].LoopHole() = y[j++]; // DIRT: y[j] already reduced
  x.normalize();
  conv(rt, rInv);  // convert rInv to zp format

  BluesteinFFT(x, m, rt, *ipowers, ipowers_aux, *iRb); // call the FFT routine

  // reduce the result mod (Phi_m(X),q) and copy to the output polynomial x
  { FHE_NTIMER_START(iFFT_division);
    rem(x, x, *phimx); // out %= (Phi_m(X),q)
  }

  // normalize
  zz_p mm_inv;
  conv(mm_inv, m_inv);
  x *= mm_inv; 
}