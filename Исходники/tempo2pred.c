int T2Predictor_GetPlan_Ext(char *filename,
			long double mjd_start,
			long double mjd_end,
			long double step, // seconds
			long double freq, // MHz
			// remaining arguments are returned
			char *psrname, char *sitename,
			long double *phase0,
			int *nsegments,
			long double *pulse_frequencies)
{
  int iseg, ret;
  long double lastphase, phase, mjd, lastmjd;
  T2Predictor pred;

  if ((ret=T2Predictor_Read(&pred, filename)))
    return ret;
  if (psrname)
    strcpy(psrname, T2Predictor_GetPSRName(&pred));
  if (sitename)
    strcpy(sitename, T2Predictor_GetSiteName(&pred));

  *nsegments = (int)ceill((mjd_end-mjd_start)*86400.0L/step);
  *phase0 = lastphase = T2Predictor_GetPhase(&pred, mjd_start, freq);
  lastmjd = mjd_start;
  printf("SILLY UPDATE IN POLYCO: REMOVE\n");
  printf("lastmjd = %.20Lf\n",mjd_start);

  for (iseg=0; iseg < *nsegments; iseg++)
  {
    mjd = mjd_start +(iseg+1)*step/86400.0L;
    if (mjd > mjd_end)
      mjd = mjd_end;
    phase = T2Predictor_GetPhase(&pred, mjd, freq);
    pulse_frequencies[iseg] = (phase-lastphase)/(mjd-lastmjd)/86400.0L;
    lastphase = phase;
    lastmjd = mjd;
  }

  T2Predictor_Destroy(&pred);

  return 0;
}