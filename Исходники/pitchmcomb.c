void
aubio_pitchmcomb_do (aubio_pitchmcomb_t * p, cvec_t * fftgrain, fvec_t * output)
{
  uint_t j;
  smpl_t instfreq;
  fvec_t *newmag = (fvec_t *) p->newmag;
  //smpl_t hfc; //fe=instfreq(theta1,theta,ops); //theta1=theta;
  /* copy incoming grain to newmag */
  for (j = 0; j < newmag->length; j++)
    newmag->data[j] = fftgrain->norm[j];
  /* detect only if local energy > 10. */
  //if (aubio_level_lin (newmag) * newmag->length > 10.) {
  //hfc = fvec_local_hfc(newmag); //not used
  aubio_pitchmcomb_spectral_pp (p, newmag);
  aubio_pitchmcomb_combdet (p, newmag);
  //aubio_pitchmcomb_sort_cand_freq(p->candidates,p->ncand);
  //return p->candidates[p->goodcandidate]->ebin;
  j = (uint_t) FLOOR (p->candidates[p->goodcandidate]->ebin + .5);
  instfreq = aubio_unwrap2pi (fftgrain->phas[j]
      - p->theta->data[j] - j * p->phasediff);
  instfreq *= p->phasefreq;
  /* store phase for next run */
  for (j = 0; j < p->theta->length; j++) {
    p->theta->data[j] = fftgrain->phas[j];
  }
  //return p->candidates[p->goodcandidate]->ebin;
  output->data[0] =
      FLOOR (p->candidates[p->goodcandidate]->ebin + .5) + instfreq;
  /*} else {
     return -1.;
     } */
}