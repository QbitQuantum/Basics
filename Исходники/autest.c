void
enc_slinear_8(int fd, audio_encoding_t *enc, int chans, int rate)
{
	audio_info_t inf;
	struct ausrate rt;
	int8_t *samples = NULL, *p;
	int i, j;

	AUDIO_INITINFO(&inf);
	inf.play.precision = enc->precision;
	inf.play.encoding = enc->encoding;
	inf.play.channels = chans;
	inf.play.sample_rate = rate;; 

	if (ioctl(fd, AUDIO_SETINFO, &inf) == -1) {
		printf("[%s]", strerror(errno));
		goto out;
	}

	if (ioctl(fd, AUDIO_GETINFO, &inf) == -1) {
		printf("[getinfo: %s]", strerror(errno));
		goto out;
	}
	rt.r_rate = inf.play.sample_rate;
	rt.s_rate = inf.play.sample_rate;
	rt.bps = 1 * chans;
	rt.bytes = inf.play.sample_rate * chans * PLAYSECS;

	samples = (int8_t *)malloc(inf.play.sample_rate * chans);
	if (samples == NULL) {
		warn("malloc");
		goto out;
	}

	for (i = 0, p = samples; i < inf.play.sample_rate; i++) {
		float d;
		int8_t v;

		d = 127.0 * sinf(((float)i / (float)inf.play.sample_rate) *
		    (2 * M_PI * playfreq));
		d = rintf(d);
		v = d;

		for (j = 0; j < chans; j++) {
			*p = v;
			p++;
		}
	}

	mark_time(&rt.tv_begin);
	for (i = 0; i < PLAYSECS; i++)
		write(fd, samples, inf.play.sample_rate * chans);
	audio_wait(fd);
	mark_time(&rt.tv_end);
	check_srate(&rt);

out:
	if (samples != NULL)
		free(samples);
}