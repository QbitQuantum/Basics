/**
 * \brief Apply synthesis filter with zero input to x. The overall filter gain
 * is 1.0.
 * \param a LPC filter coefficients.
 * \param length length of the input/output data vector x.
 * \param x input/output vector, where the synthesis filter is applied in place.
 */
static void Syn_filt_zero(const FIXP_LPC a[], const INT a_exp, INT length,
                          FIXP_DBL x[]) {
  int i, j;
  FIXP_DBL L_tmp;

  for (i = 0; i < length; i++) {
    L_tmp = (FIXP_DBL)0;

    for (j = 0; j < fMin(i, M_LP_FILTER_ORDER); j++) {
      L_tmp -= fMultDiv2(a[j], x[i - (j + 1)]) >> (LP_FILTER_SCALE - 1);
    }

    L_tmp = scaleValue(L_tmp, a_exp + LP_FILTER_SCALE);
    x[i] = fAddSaturate(x[i], L_tmp);
  }
}