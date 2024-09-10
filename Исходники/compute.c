int idct_process (Channel * c[2]) {
#ifdef DEADLOCK
  printf("Thread compute 0x%.8x has been created\n", (unsigned int)pthread_self());
#endif

	uint8_t * Idct_YCbCr;
	int32_t * block_YCbCr;
	uint32_t flit_size = 0;

	channelRead (c[0], (uint8_t *) & flit_size, sizeof (uint32_t));
	VPRINTF("Flit size = %lu\r\n", flit_size);

	Idct_YCbCr = (uint8_t *) malloc (flit_size * 64 * sizeof (uint8_t));
	if (Idct_YCbCr == NULL) printf ("%s,%d: malloc failed\n", __FILE__, __LINE__);

	block_YCbCr = (int32_t *) malloc (flit_size * 64 * sizeof (int32_t));
	if (block_YCbCr == NULL) printf ("%s,%d: malloc failed\n", __FILE__, __LINE__);

	while (1) {
		channelRead (c[0], (unsigned char *) block_YCbCr, flit_size * 64 * sizeof (int32_t));

		for (uint32_t i = 0; i < flit_size; i++) IDCT(& block_YCbCr[i * 64], & Idct_YCbCr[i * 64]);

		channelWrite (c[1], (unsigned char *) Idct_YCbCr, flit_size * 64 * sizeof (uint8_t));
	}

	return 0;
}