static void print_hz (char *t, float hz) {
	//printf("%f ", hz);
	hz = 5 * rintf(hz / 5.f);
	if (hz >= 990) {
		int dec = ((int)rintf (hz / 100.f)) % 10;
		if (dec != 0) {
			snprintf(t, 8, "%.0fK%d", floor(hz / 1000.f), dec);
		} else {
			snprintf(t, 8, "%.0fK", hz / 1000.f);
		}
	} else {
		snprintf(t, 8, "%.0f", hz);
	}
	//printf("-> %f -> %s\n", hz, t);
}