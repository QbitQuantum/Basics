static void reinitialize_fft(MF2UI* ui, uint32_t fft_size) {
	pthread_mutex_lock (&ui->fft_lock);
	fftx_free(ui->fa);
	fftx_free(ui->fb);

	fft_size = MIN(8192, MAX(64, fft_size));
	fft_size--;
	fft_size |= 0x3f;
	fft_size |= fft_size >> 2;
	fft_size |= fft_size >> 4;
	fft_size |= fft_size >> 8;
	fft_size |= fft_size >> 16;
	fft_size++;
	fft_size = MIN(FFT_BINS_MAX, fft_size);
	ui->fft_bins = fft_size;

	ui->fa = (struct FFTAnalysis*) malloc(sizeof(struct FFTAnalysis));
	ui->fb = (struct FFTAnalysis*) malloc(sizeof(struct FFTAnalysis));
	fftx_init(ui->fa, ui->fft_bins * 2, ui->rate, 25);
	fftx_init(ui->fb, ui->fft_bins * 2, ui->rate, 25);
	ui->log_rate  = (1.0f - 10000.0f / ui->rate) / ((2000.0f / ui->rate) * (2000.0f / ui->rate));
	ui->log_base = log10f(1.0f + ui->log_rate);
	ui->update_grid = true;

	for (uint32_t i = 0; i < ui->fft_bins; i++) {
		ui->phase[i] = 0;
		ui->level[i] = -100;
	}

	int band = 0;
	uint32_t bin = 0;
	const double f_r = 1000;
	const double b = ui->fft_bins < 128 ? 6 : 12;
	const double f2f = pow(2,  1. / (2. * b));

	assert(ui->fa->freq_per_bin < f_r);
	const int b_l = floorf(b * logf(ui->fa->freq_per_bin / f_r) / logf(2));
	const int b_u = ceilf(b * logf(.5 * ui->rate / f_r) / logf(2));
	ui->freq_bins = b_u - b_l - 1;

	free(ui->freq_band);
	ui->freq_band = (uint32_t*) malloc(ui->freq_bins * sizeof(uint32_t));

	for (uint32_t i = 0; i < ui->fft_bins; i++) {
		double f_m = pow(2, (band + b_l) / b) * f_r;
		double f_2 = f_m * f2f;
		if (f_2 > i * ui->fa->freq_per_bin) {
			continue;
		}
		while (f_2 < i * ui->fa->freq_per_bin) {
			band++;
			f_m = pow(2, (band + b_l) / b) * f_r;
			f_2 = f_m * f2f;
		}
		ui->freq_band[bin++] = i;
	}
	ui->freq_band[bin++] = ui->fft_bins;
	ui->freq_bins = bin;

	pthread_mutex_unlock (&ui->fft_lock);
}