void aubio_hist_do_notnull (aubio_hist_t *s, fvec_t *input) {
  uint_t j;
  sint_t tmp = 0;
  aubio_scale_do(s->scaler, input);
  /* reset data */
  fvec_zeros(s->hist);
  /* run accum */
  for (j=0;  j < input->length; j++) {
    if (input->data[j] != 0) {
      tmp = (sint_t)FLOOR(input->data[j]);
      if ((tmp >= 0) && (tmp < (sint_t)s->nelems))
        s->hist->data[tmp] += 1;
    }
  }
}