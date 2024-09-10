void *idct_thread(void *args)
{
	gmactime_t s, t;

	barrier_wait(&barrierInit);

	getTime(&s);
	gmac_sem_post(&s_idct.free, 1);
	ecl::deviceSendReceive(s_dct.id);
	nextStage(&s_idct, NULL);
	getTime(&t);
	printTime(&s, &t, "IDCT:SendRecv: ", "\n");

	getTime(&s);
	gmac_sem_post(&s_idct.free, 1);
	ecl::deviceSendReceive(s_dct.id);
	getTime(&t);
	nextStage(&s_idct, NULL);
	getTime(&t);
	printTime(&s, &t, "IDCT:SendRecv: ", "\n");

	ecl::config localSize(blockSize, blockSize);
	ecl::config globalSize(width, height);
	if(width  % blockSize) globalSize.x += blockSize;
	if(height % blockSize) globalSize.y += blockSize;
	ecl::error err;
	ecl::kernel k("idct", err);
	assert(err == eclSuccess);

	assert(k.setArg(2, width)   == eclSuccess);
	assert(k.setArg(3, height)  == eclSuccess);

	for(unsigned i = 0; i < frames; i++) {
		getTime(&s);
		assert(k.setArg(0, s_idct.in)  == eclSuccess);
		assert(k.setArg(1, s_idct.out) == eclSuccess);
		assert(k.callNDRange(globalSize, localSize) == eclSuccess);
		getTime(&t);
		printTime(&s, &t, "IDCT:Run: ", "\n");

		getTime(&s);
		assert(ecl::free(s_idct.in) == eclSuccess);
		assert(ecl::free(s_idct.out) == eclSuccess);
		getTime(&t);
		printTime(&s, &t, "IDCT:Free: ", "\n");

		getTime(&s);
		ecl::deviceSendReceive(s_dct.id);
		nextStage(&s_idct, NULL);
		getTime(&t);
		printTime(&s, &t, "IDCT:SendRecv: ", "\n");
	}

	getTime(&s);
	ecl::free(s_idct.in);
	ecl::free(s_idct.out);
	getTime(&t);
	printTime(&s, &t, "IDCT:Free: ", "\n");

	return NULL;
}