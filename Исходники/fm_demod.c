/* ---------------------------------------------------------------------------- */
PRIVATE void
pll(FMD fm, COMPLEX sig) {
  COMPLEX z = Cmplx((REAL) cos(fm->pll.phs), (IMAG) sin(fm->pll.phs));
  REAL diff;

  fm->pll.delay.re = z.re * sig.re + z.im * sig.im;
  fm->pll.delay.im = -z.im * sig.re + z.re * sig.im;
  diff = ATAN2(fm->pll.delay.im, fm->pll.delay.re);

  fm->pll.freq.f += fm->pll.beta * diff;

  if (fm->pll.freq.f < fm->pll.freq.l)
    fm->pll.freq.f = fm->pll.freq.l;
  if (fm->pll.freq.f > fm->pll.freq.h)
    fm->pll.freq.f = fm->pll.freq.h;

  fm->pll.phs += fm->pll.freq.f + fm->pll.alpha * diff;

  while (fm->pll.phs >= TWOPI)
    fm->pll.phs -= (REAL) TWOPI;
  while (fm->pll.phs < 0)
    fm->pll.phs += (REAL) TWOPI;
}