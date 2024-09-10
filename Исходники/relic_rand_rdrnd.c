void rand_bytes(uint8_t *buf, int size) {
	int i = 0, j;
	unsigned long long r;

	while (i < size) {
#ifdef __RDRND__
		while (_rdrand64_step(&r) == 0);
#else
#error "RdRand not available, check your compiler settings."
#endif
		for (j = 0; i < size && j < sizeof(ull_t); i++, j++) {
			buf[i] = r & 0xFF;
		}
	}
}