void BluesteinFFT(zz_pX& x, long n, const zz_p& root,
		  const zz_pX& powers, const Vec<mulmod_precon_t>& powers_aux, 
                  const fftRep& Rb)
{
  // FHE_TIMER_START;

  if (IsZero(x)) return;
  if (n<=0) {
    clear(x);
    return;
  }

  long p = zz_p::modulus();

  long dx = deg(x);
  for (long i=0; i<=dx; i++) {
    x[i].LoopHole() = MulModPrecon(rep(x[i]), rep(powers[i]), p, powers_aux[i]);
  }
  x.normalize();

  long k = NextPowerOfTwo(2*n-1);
  fftRep& Ra = Cmodulus::getScratch_fftRep(k);
  TofftRep(Ra, x, k);

  mul(Ra,Ra,Rb);           // multiply in FFT representation

  FromfftRep(x, Ra, n-1, 2*(n-1)); // then convert back
  dx = deg(x); 
  for (long i=0; i<=dx; i++) {
	  x[i].LoopHole() = MulModPrecon(rep(x[i]), rep(powers[i]), p, powers_aux[i]);
  }
  x.normalize();
}