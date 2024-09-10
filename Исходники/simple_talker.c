void gensine32(int32_t * buf, unsigned count)
{
	long double interval = (2 * ((long double)M_PI)) / count;
	unsigned i;
	for (i = 0; i < count; ++i) {
		buf[i] =
		    (int32_t) (MAX_SAMPLE_VALUE * sinl(i * interval) * GAIN);
	}
}