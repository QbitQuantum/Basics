void
aubio_pitchyinfft_do (aubio_pitchyinfft_t * p, fvec_t * input, fvec_t * output)
{
  uint_t tau, l;
  uint_t halfperiod;
  smpl_t tmp, sum;
  cvec_t *res = (cvec_t *) p->res;
  fvec_t *yin = (fvec_t *) p->yinfft;
  l = 0;
  tmp = 0.;
  sum = 0.;
  for (l = 0; l < input->length; l++) {
    p->winput->data[l] = p->win->data[l] * input->data[l];
  }
  aubio_fft_do (p->fft, p->winput, p->fftout);
  for (l = 0; l < p->fftout->length; l++) {
    p->sqrmag->data[l] = SQR (p->fftout->norm[l]);
    p->sqrmag->data[l] *= p->weight->data[l];
  }
  for (l = 1; l < p->fftout->length; l++) {
    p->sqrmag->data[(p->fftout->length - 1) * 2 - l] =
        SQR (p->fftout->norm[l]);
    p->sqrmag->data[(p->fftout->length - 1) * 2 - l] *=
        p->weight->data[l];
  }
  for (l = 0; l < p->sqrmag->length / 2 + 1; l++) {
    sum += p->sqrmag->data[l];
  }
  sum *= 2.;
  aubio_fft_do (p->fft, p->sqrmag, res);
  yin->data[0] = 1.;
  for (tau = 1; tau < yin->length; tau++) {
    yin->data[tau] = sum - res->norm[tau] * COS (res->phas[tau]);
    tmp += yin->data[tau];
    yin->data[tau] *= tau / tmp;
  }
  tau = fvec_min_elem (yin);
  if (yin->data[tau] < p->tol) {
    /* no interpolation */
    //return tau;
    /* 3 point quadratic interpolation */
    //return fvec_quadint_min(yin,tau,1);
    /* additional check for (unlikely) octave doubling in higher frequencies */
    if (tau > 35) {
      output->data[0] = fvec_quadint (yin, tau);
    } else {
      /* should compare the minimum value of each interpolated peaks */
      halfperiod = FLOOR (tau / 2 + .5);
      if (yin->data[halfperiod] < p->tol)
        output->data[0] = fvec_quadint (yin, halfperiod);
      else
        output->data[0] = fvec_quadint (yin, tau);
    }
  } else {
    output->data[0] = 0.;
  }
}