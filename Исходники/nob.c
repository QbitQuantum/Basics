PORT
ANB create_anb	(
	int run,
	int buffsize,
	float* in,
	float* out,
	float samplerate,
	float tau,
	float hangtime,
	float advtime,
	float backtau,
	float threshold
				)
{
	ANB a;
	a = (ANB) malloc0 (sizeof(anb));
	a->run = run;
	a->buffsize = buffsize;
	a->in = in;
	a->out = out;
	a->samplerate = samplerate;
	a->tau = tau;
	a->hangtime = hangtime;
	a->advtime = advtime;
	a->backtau = backtau;
	a->threshold = threshold;
	a->wave = (float *) malloc0 (((int)(MAX_SAMPLERATE * MAX_TAU) + 1) * sizeof(float));
	a->dline_size = (int)((MAX_TAU + MAX_ADVTIME) * MAX_SAMPLERATE) + 1;
	a->dline = (float *) malloc0 (a->dline_size * sizeof(complex));
	InitializeCriticalSectionAndSpinCount (&a->cs_update, 2500);
	initBlanker(a);
	a->legacy = (float *) malloc0 (2048 * sizeof (complex));														/////////////// legacy interface - remove
	return a;
}