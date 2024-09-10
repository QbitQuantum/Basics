/* ---------------------------------------------------------------------------- */
COMPLEX
Cr2p(COMPLEX z) {
  return Cmplx((REAL) hypot(z.re, z.im),
	       (REAL) ATAN2(z.im, z.re));
}