static void xscalbln (xcomplex *z, int e) {
  __real__(*z) = scalbln(__real__(*z), e);
  __imag__(*z) = scalbln(__imag__(*z), e);
}