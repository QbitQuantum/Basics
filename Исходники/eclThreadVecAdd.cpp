void *addVector(void *ptr)
{
	float *a, *b;
	float **c = (float **)ptr;
	gmactime_t s, t;
	ecl::error ret;
	getTime(&s);
	// Alloc & init input data
	ret = ecl::malloc((void **)&a, vecSize * sizeof(float));
	assert(ret == eclSuccess);
	ret = ecl::malloc((void **)&b, vecSize * sizeof(float));
	assert(ret == eclSuccess);

	for(unsigned i = 0; i < vecSize; i++) {
		a[i] = 1.f * rand() / RAND_MAX;
		b[i] = 1.f * rand() / RAND_MAX;
	}

	// Alloc output data
	ret = ecl::malloc((void **)c, vecSize * sizeof(float));
	assert(ret == eclSuccess);
	getTime(&t);
	printTime(&s, &t, "Alloc: ", "\n");

	// Call the kernel
	getTime(&s);
	ecl::config localSize(blockSize);
	ecl::config globalSize(vecSize / blockSize);
	if(vecSize % blockSize) globalSize.x++;
	globalSize.x *= localSize.x;

	ecl::kernel kernel("vecAdd", ret);
	assert(ret == eclSuccess);
	ret = kernel.setArg(0, *c);
	assert(ret == eclSuccess);
	ret = kernel.setArg(1, a);
	assert(ret == eclSuccess);
	ret = kernel.setArg(2, b);
	assert(ret == eclSuccess);
	ret = kernel.setArg(3, vecSize);
	assert(ret == eclSuccess);

	ret = kernel.callNDRange(globalSize, localSize);
	assert(ret == eclSuccess);

	getTime(&t);
	printTime(&s, &t, "Run: ", "\n");

	getTime(&s);
	float error = 0;
	for(unsigned i = 0; i < vecSize; i++) {
		error += (*c)[i] - (a[i] + b[i]);
	}
	getTime(&t);
	printTime(&s, &t, "Check: ", "\n");
	fprintf(stdout, "Error: %.02f\n", error);

	ecl::free(a);
	ecl::free(b);
	ecl::free(*c);

	return NULL;
}