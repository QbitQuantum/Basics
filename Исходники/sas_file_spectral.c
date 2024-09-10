sas_frame_t
sas_file_spectral_get_frame (sas_file_spectral_t sp, sas_frame_t dest, int n)
{
  int length;
  int harmonics;
  double fundamental;
  double amplitudes[MAX_NUMBER_OF_PARTIALS];
  double frequencies[MAX_NUMBER_OF_PARTIALS];
  int coefficients[MAX_NUMBER_OF_PARTIALS];

  length = sp->t_max - sp->t_min;
  assert (n < length);

  /* Find out fundamental and number of harmonics. */
  {
    int t;
    sas_file_partial_t p;
    double f_min, f_max;
    double fp, ip;
    int i;

    t = sp->t_min + n;

    f_min = SAS_MAX_AUDIBLE_FREQUENCY;
    f_max = 0;

    for (i = 0; i < sp->used; i++)
      {
	p = sp->tracks[i];

	if ((p->start <= t) && (t < (p->start + p->length)))
	  {
	    if (p->frequency[t - p->start] < f_min)
	      f_min = p->frequency[t - p->start];

	    if (p->frequency[t - p->start] > f_max)
	      f_max = p->frequency[t - p->start];
	  }
      }

    assert (f_min > 0);

    fp = modf (f_max / f_min, &ip);
    if (fp >= 0.5)
      {
	ip += 1;
	fp -= 1;
      }

    harmonics = (int) ip;
    fundamental = f_min;
  }

  /* Adjust number of harmonics. */
  if (harmonics > MAX_NUMBER_OF_PARTIALS)
    {
      fprintf
	(stderr,
	 "sas_file_spectral_get_frame: %s: too much harmonics in frame %d\n",
	 sp->filename, n);
      harmonics = MAX_NUMBER_OF_PARTIALS;
      /* return NULL; */
    }

  /* Compute amplitudes. */
  {
    int t;
    sas_file_partial_t p;
    REAL frequency, coefficient;
    int i;

    frequency = 0;
    coefficient = 0;

    t = sp->t_min + n;

    /* Zero arrays. */
    for (i = 0; i < harmonics; i++)
      {
	amplitudes[i] = 0.0;
	frequencies[i] = 0.0;
	coefficients[i] = 0;
      }

    /* Scan partials. */
    for (i = 0; i < sp->used; i++)
      {
	p = sp->tracks[i];

	if ((p->start <= t) && (t < (p->start + p->length)))
	  {
	    double fp, ip;
	    int h;

	    fp = modf (p->frequency[t - p->start] / fundamental, &ip);
	    if (fp >= 0.5)
	      {
		ip += 1;
		fp -= 1;
	      }

	    h = (int) ip - 1;

	    assert (h < harmonics);

	    /* On harmonic conflict, keep the highest amplitude partial. */
	    if (amplitudes[h] < p->amplitude[t - p->start])
	      {
		amplitudes[h] = p->amplitude[t - p->start];
		frequency -= frequencies[h];
		coefficient -= coefficients[h];
		frequencies[h] = p->frequency[t - p->start];
		coefficients[h] = ip;
		frequency += frequencies[h];
		coefficient += coefficients[h];
	      }
	  }
      }

    frequency /= coefficient;

    fundamental = frequency;
  }

  /* We may have a new fundamental; should we recompute the amplitudes
     of harmonics?. */

  /* Fill frame. */
  {
    sas_envelope_t C;
    double A;
    int i;

    /* SM idea: use the following formula to determine properly
       perceived amplitude.  Not implemented.

       A = (1/sqrt(2)) * sqrt(sum(a_i^2)) */

    /* A */
    A = 0.0;
    for (i = 0; i < harmonics; i++)
      A += amplitudes[i];
    if (A > 1.0)
      A = 1.0;
    sas_frame_set_amplitude (dest, A);

    /* F */
    sas_frame_set_frequency (dest, fundamental);

    /* C */
    C = sas_envelope_make (fundamental, harmonics, amplitudes);
    sas_envelope_adjust_for_color (C);
    sas_frame_set_color (dest, C);

    /* W */
    /* Keep identity mapping. */
  }

  return dest;
}