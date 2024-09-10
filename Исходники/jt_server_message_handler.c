inline static void calc_whoosh_error(struct iface_stats *stats)
{
	long double variance;
	double max = 0;
	uint64_t sum = 0;
	uint64_t sum_squares = 0;

	for (int i = 0; i < SAMPLES_PER_FRAME; i++) {
		struct sample s = stats->samples[i];
		max = (s.whoosh_error_ns > max) ? s.whoosh_error_ns : max;
		sum += s.whoosh_error_ns;
		sum_squares += (s.whoosh_error_ns * s.whoosh_error_ns);
	}
	stats->whoosh_err_max = max;
	stats->whoosh_err_mean = sum / SAMPLES_PER_FRAME;
	variance = (long double)sum_squares / (double)SAMPLES_PER_FRAME;
	stats->whoosh_err_sd = (uint64_t)ceill(sqrtl(variance));

	if ((max >= 500 * SAMPLE_PERIOD_US) ||
	    (stats->whoosh_err_sd >= 200 * SAMPLE_PERIOD_US)) {
		fprintf(stderr, "sampling jitter! mean: %10" PRId64
		                " max: %10" PRId64 " sd: %10" PRId64 "\n",
		        stats->whoosh_err_mean, stats->whoosh_err_max,
		        stats->whoosh_err_sd);
	}
}