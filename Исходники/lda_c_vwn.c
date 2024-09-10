/* initialization */
static void
init_vwn_constants(vwn_consts_type *X)
{
  int i;

  X->A[2] = -1.0/(6.0*M_PI*M_PI);
  for(i=0; i<3; i++){
    X->Q[i] = SQRT(4.0*X->c[i] - X->b[i]*X->b[i]);
  }
  X->fpp = 4.0/(9.0*(CBRT(2.0) - 1));
}