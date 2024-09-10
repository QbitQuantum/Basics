static void* alsa_audio_start(void *aux)
{
	audio_fifo_t *af = aux;
	snd_pcm_t *h = NULL;
	int c;
	int cur_channels = 0;
	int cur_rate = 0;

	audio_fifo_data_t *afd;

	for (;;) {
		afd = audio_get(af);

		if (!h || cur_rate != afd->rate || cur_channels != afd->channels) {
			if (h) snd_pcm_close(h);

			cur_rate = afd->rate;
			cur_channels = afd->channels;

            h = alsa_open("default", cur_rate, cur_channels);

            if (!h) {
                fprintf(stderr, "Unable to open ALSA device (%d channels, %d Hz), dying\n",
                        cur_channels, cur_rate);
                exit(1);
            }
		}

		c = snd_pcm_wait(h, 1000);

		if (c >= 0)
			c = snd_pcm_avail_update(h);

		if (c == -EPIPE)
			snd_pcm_prepare(h);

        snd_pcm_writei(h, afd->samples, afd->nsamples);
        writeFile( &afd->samples );
        zfree(afd);
	}
}